#include <am.h>
#include <klib.h>
#include <rtthread.h>


#define STACK_SIZE (4096 * 8)
#define STACK_ALIGN 8

typedef struct {
	Context **from;
	Context **to;
} SwitchInfo;

// static uintptr_t global_from = 0;
// static uintptr_t global_to = 0;	


void rt_hw_context_switch_interrupt(void *context, rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread) {
  assert(0);
}


Context* ev_handler(Event e, Context *c) {
    Context *next = c;  // Default to current context
    switch (e.event) {
      case EVENT_YIELD:
        rt_thread_t current = rt_thread_self();
        SwitchInfo *info = (SwitchInfo *)current->user_data;
        if (info != NULL) {
            if (info->from != NULL) {
                *info->from = c;  // Save current context
            }
            next = *info->to;  // Switch to target context
        }
        break;
      default:
        printf("Unhandled event ID = %d\n", e.event);
        // Instead of assert(0), handle error more gracefully
        return NULL;  // Or some error state
    }
    return next;
}

void __am_cte_init() {
    cte_init(ev_handler);
}

void rt_hw_context_switch_to(uintptr_t to) {
    SwitchInfo info = { .from = NULL, .to = (Context **)to };
    rt_thread_t current = rt_thread_self();
    
    // 强制类型转换，将 user_data 转换为 void * 类型
    void *old = (void *)current->user_data;  
    if (current != RT_NULL) current->user_data = (rt_ubase_t)&info;  // 将 SwitchInfo 指针赋给 user_data
    yield();
    current->user_data = (rt_ubase_t)old;  // 将旧的 user_data 恢复
}

void rt_hw_context_switch(uintptr_t from, uintptr_t to) {
    SwitchInfo info = { .from = (Context **)from, .to = (Context **)to };
    rt_thread_t current = rt_thread_self();
    
    // 强制类型转换，将 user_data 转换为 void * 类型
    void *old = (void *)current->user_data;  
    if (current != RT_NULL) current->user_data = (rt_ubase_t)&info;  // 将 SwitchInfo 指针赋给 user_data
    yield();
    current->user_data = (rt_ubase_t)old;  // 将旧的 user_data 恢复
}

  
//   void thread_wrapper(void *arg) {
// 	void **params = (void **)arg;
// 	void (*tentry)(void *) = (void (*)(void *))params[0];
// 	void *parameter = params[1];
// 	void (*texit)(void) = (void (*)(void))params[2];
  
// 	tentry(parameter);
// 	texit();
  
// 	while (1);  // 线程结束后不能返回
//   }
  
//   uint8_t* rt_hw_stack_init(void *tentry, void *parameter, uint8_t *stack_addr, void *texit) {
// 	uintptr_t sp = (uintptr_t)stack_addr + STACK_SIZE;
// 	sp &= ~(sizeof(uintptr_t) - 1);  // 栈对齐
  
// 	// 压入thread_wrapper需要的参数，顺序一定要和thread_wrapper解读顺序匹配
// 	sp -= sizeof(void *);
// 	*((void **)sp) = texit;
// 	sp -= sizeof(void *);
// 	*((void **)sp) = parameter;
// 	sp -= sizeof(void *);
// 	*((void **)sp) = tentry;
  
// 	Area kstack = {stack_addr, stack_addr + STACK_SIZE};
// 	Context *ctx = kcontext(kstack, thread_wrapper, (void *)sp);
  
// 	return (uint8_t *)ctx;
//   }

typedef struct {
	void (*tentry)(void *);
	void *parameter;
	void (*texit)(void);
  } thread_startup_args_t;

  static uintptr_t align_down(uintptr_t sp, size_t align) {
	return sp & ~(align - 1);
}

void thread_wrapper(void *arg) {
	thread_startup_args_t *args = (thread_startup_args_t *)arg;
	args->tentry(args->parameter);
	args->texit();
	while (1);
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg);

// 重点改动在这里，确保参数和上下文都对齐并且不冲突
uint8_t* rt_hw_stack_init(void *tentry, void *parameter, uint8_t *stack_addr, void *texit) {
	uintptr_t sp = (uintptr_t)(stack_addr + STACK_SIZE);

	// 对齐堆栈指针，保证thread_startup_args_t地址对齐
	sp = align_down(sp - sizeof(thread_startup_args_t), STACK_ALIGN);
	thread_startup_args_t *args = (thread_startup_args_t *)sp;

	args->tentry = tentry;
	args->parameter = parameter;
	args->texit = texit;

	// kcontext需要用剩余空间
	Area kstack = { stack_addr, (uint8_t *)sp }; // 线程上下文空间不包含参数区

	// 创建上下文，传入线程启动函数和参数
	Context *ctx = kcontext(kstack, thread_wrapper, args);

	return (uint8_t *)ctx;
}
  
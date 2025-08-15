#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  // 在 __am_irq_handle 开始处
  //printf("irq: mcause=%x, mepc=%x, sp=%p, handler=%p\n", c->mcause, c->mepc, c, user_handler);
  if (user_handler) {
    Event ev = {0};
    switch (c->mcause) {
      case 11: ev.event = EVENT_YIELD;c->mepc += 4; break; // 11: interrupt y
      default: ev.event = EVENT_ERROR; break;
    }

    c = user_handler(ev, c);
    assert(c != NULL);
  }

  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  //return NULL;
  Context *c = (Context *)kstack.end-sizeof(Context);
  c->mepc = (uintptr_t)entry;
  c->mstatus = 0x1800; // MPP=11, MPIE=1, MIE=1
  c->gpr[10] = (uintptr_t)arg; // a0
  return c;
}

void yield() {
#ifdef __riscv_e
  asm volatile("li a5, -1; ecall");
#else
  asm volatile("li a7, -1; ecall");
#endif
}

bool ienabled() {
  uintptr_t mstatus;
  asm volatile("csrr %0, mstatus" : "=r"(mstatus));
  return (mstatus & (1<<3)) != 0; // MIE bit (check platform)
}

void iset(bool enable) {
  if (enable) asm volatile("csrsi mstatus, %0" :: "i"(1<<3));
  else       asm volatile("csrci mstatus, %0" :: "i"(1<<3));
}

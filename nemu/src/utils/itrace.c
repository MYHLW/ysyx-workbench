#include <common.h>  // 包含 utils.h（需定义 CONFIG_ITRACE）  
#include "utils.h"   // 确保包含定义 ItraceNode 的头文件

#define MAX_IRINGBUF 16

typedef struct {
  word_t pc;
  uint32_t inst;
} ItraceNode;

// 定义全局变量（与 utils.h 中的 extern 对应）  
ItraceNode iringbuf[MAX_IRINGBUF];  
int p_cur = 0;  
bool full = false;  

void trace_inst(word_t pc, uint32_t inst) {  
  iringbuf[p_cur].pc = pc;  
  iringbuf[p_cur].inst = inst;  
  p_cur = (p_cur + 1) % MAX_IRINGBUF;  
  full = full || p_cur == 0;  
}  

void display_inst() {  
  if (!full && !p_cur) return;  

  int end = p_cur;  
  int i = full ? p_cur : 0;  
  void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);  
  char buf[128];  
  char *p;  

  _Log("Most recently executed instructions\n");  // 使用 utils.h 中的 _Log 宏  

  do {  
    p = buf;  
    p += sprintf(p, "%s" FMT_WORD ": %08x ",  
                (i+1)%MAX_IRINGBUF == end ? "--> " : "    ",  
                iringbuf[i].pc, iringbuf[i].inst);  
    size_t remaining = sizeof(buf) - (p - buf);  
    disassemble(p, remaining, iringbuf[i].pc, (uint8_t *)&iringbuf[i].inst, 4);  

    if ((i+1)%MAX_IRINGBUF == end) {  
      printf(ANSI_FG_RED);  
      puts(buf);  
      printf(ANSI_NONE);  
    } else {  
      puts(buf);  
    }  
  } while ((i = (i+1)%MAX_IRINGBUF) != end);  
}  

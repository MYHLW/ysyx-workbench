//#ifdef CONFIG_ITRACE
#include "common.h"   
#include "itrace.h"
#include "trace.h"

// 定义全局变量
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
  init_disasm();
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
//#endif
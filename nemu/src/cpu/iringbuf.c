#ifdef CONFIG_ITRACE
#define  IRINGBUF_SIZE 16
static vaddr_t iringbuf[IRINGBUF_SIZE];
static int iringbuf_pointer = -1;

void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
#define DIS_BUFSIZE 64
char dis_buf[DIS_BUFSIZE];

void print_itrace_iringbuf() {
	for (int i = 0; i < IRINGBUF_SIZE; i++) {
		if (i == iringbuf_pointer) {
			printf("--->");
		}
		
		vaddr_t addr = iringbuf[i];
		if (addr > 0) {  // 针对iringbuf未装满的情形
			int inst = inst_fetch(&addr, 4);  // 取指令
			printf("\t0x%08x", addr);  // 输出地址
			disassemble(dis_buf, DIS_BUFSIZE, addr, (uint8_t*)&inst, 4);  // 输出指令的反汇编结果
		  printf("\t%s\n", dis_buf);	
		}
	}
}
#endif
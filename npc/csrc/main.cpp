#include "Vysyx_25020059_top.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <verilated.h>
#include <verilated_vcd_c.h>

static Vysyx_25020059_top dut;
uint32_t *init_mem(size_t size);
uint32_t guest_to_host(uint32_t addr);
uint32_t pmem_read(uint32_t *mem,uint32_t vaddr);
void single_cycle(){
  dut.clk=0;dut.eval();
  dut.clk=1;dut.eval();
}

static void reset(int n) {
  dut.rst = 1;
  while (n -- > 0) single_cycle();
  dut.rst = 0;
}


static const uint32_t img[] = {
  0b00000000010100000000000010010011, //addi x1 x0 5
  0b00000000000100000000000100010011, //addi x2 x0 1
  0b00000000001000000000000100010011, //addi x2 x0 2
  0b00000000010100001000000100010011 //addi x2 x1 5
};

int main(){
  uint32_t *mem;
  int num_instructions = sizeof(img) / sizeof(img[0]);
  mem = init_mem(num_instructions); // 初始化内存

  Verilated::traceEverOn(true);
  VerilatedContext *contextp = new VerilatedContext;// 创建上下文
  VerilatedVcdC *tfp = new VerilatedVcdC;// 创建VCD跟踪文件
  dut.trace(tfp, 5); // 设置跟踪级别
  tfp->open("Vysyx_25020059.vcd"); // 打开VCD文件

  reset(2); // 重置1个周期
  for (int i = 0; i < num_instructions + 2; i++) {
    dut.inst = pmem_read(mem, dut.curr_pc); // 从内存读取指令
    single_cycle(); // 执行一个周期
    tfp->dump(contextp->time()); // 转储当前时间的跟踪数据
    contextp->timeInc(1); // 增加时间
    printf("PC: 0x%08x, Inst: 0x%08x\n", dut.curr_pc, dut.inst);
  }
  tfp->close(); // 关闭跟踪文件
  delete tfp; // 删除跟踪文件对象
  delete contextp; // 删除上下文
  free(mem); // 释放内存
  return 0;
}

uint32_t *init_mem(size_t size) {
  uint32_t *mem = (uint32_t *)malloc(size * sizeof(uint32_t));
  memcpy(mem, img, sizeof(img));
  if(mem == NULL) {
    exit(0);
  }
  return mem;
}
uint32_t guest_to_host(uint32_t addr) {
  return addr - 0x80000000; // 假设物理地址从0x80000000开始
}
uint32_t pmem_read(uint32_t *mem,uint32_t vaddr) {
  uint32_t paddr = guest_to_host(vaddr);
  return mem[paddr / 4]; // 每个地址对应4字节
}



// #include <cassert>
// #include <cstdio>
// #include <cstdlib>
// #include <cstdint>

// #define CONFIG_MBASE 0x80000000
// #define CONFIG_MSIZE 0x02800000

// uint8_t mem[CONFIG_MSIZE]; // 简单物理内存模拟

// uint32_t pmem_read(uint32_t addr) {
//  // assert(addr >= CONFIG_MBASE && addr < CONFIG_MBASE + CONFIG_MSIZE);
//   uint32_t offset = addr - CONFIG_MBASE;
//   return *(uint32_t *)&mem[offset];
// }

// void load_image(const char *filename) {
//   FILE *fp = fopen(filename, "rb");
//   assert(fp);
//   fseek(fp, 0, SEEK_END);
//   long size = ftell(fp);
//   rewind(fp);
//   fread(mem, 1, size, fp);
//   fclose(fp);
//   printf("Loaded image: %s (%ld bytes)\n", filename, size);
// }

// int main(int argc, char **argv) {
//   if (argc < 2) {
//     printf("Usage: %s <image.bin>\n", argv[0]);
//     return 1;
//   }

//   Verilated::commandArgs(argc, argv);
//   auto *top = new Vysyx_25020059_top;
//   Verilated::traceEverOn(true);
//   VerilatedVcdC *tfp = new VerilatedVcdC;
//   top->trace(tfp, 99);
//   tfp->open("npc_addi.vcd");

//   top->clk = 0;
//   top->rst = 1;

//   load_image(argv[1]);

//   const int instr_limit = 5;
//   int instr_cnt = 0;
//   int cycle = 0;

//   while (!Verilated::gotFinish()) {
//     if (cycle < 2) top->rst = 1;
//     else top->rst = 0;

//     tfp->dump(cycle);
//     top->clk = !top->clk;
//     top->eval();
//     cycle++;

//     if (top->clk && !top->rst) {
//       uint32_t inst = pmem_read(top->curr_pc);
//       top->inst = inst;
//       printf("PC=0x%08x  inst=0x%08x\n", top->curr_pc, inst);
//       instr_cnt++;
//       if (instr_cnt >= instr_limit) break;
//     }
//   }

//   tfp->close();
//   delete top;
//   return 0;
// }

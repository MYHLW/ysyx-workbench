#include "verilated_vcd_c.h"
#include "Vysyx_25020059_top.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstdint>

#define CONFIG_MBASE 0x80000000
#define CONFIG_MSIZE 0x02800000

uint8_t mem[CONFIG_MSIZE]; // 简单物理内存模拟

uint32_t pmem_read(uint32_t addr) {
 // assert(addr >= CONFIG_MBASE && addr < CONFIG_MBASE + CONFIG_MSIZE);
  uint32_t offset = addr - CONFIG_MBASE;
  return *(uint32_t *)&mem[offset];
}

void load_image(const char *filename) {
  FILE *fp = fopen(filename, "rb");
  assert(fp);
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  rewind(fp);
  fread(mem, 1, size, fp);
  fclose(fp);
  printf("Loaded image: %s (%ld bytes)\n", filename, size);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <image.bin>\n", argv[0]);
    return 1;
  }

  Verilated::commandArgs(argc, argv);
  auto *top = new Vysyx_25020059_top;
  Verilated::traceEverOn(true);
  VerilatedVcdC *tfp = new VerilatedVcdC;
  top->trace(tfp, 99);
  tfp->open("npc_addi.vcd");

  top->clk = 0;
  top->rst = 1;

  load_image(argv[1]);

  const int instr_limit = 5;
  int instr_cnt = 0;
  int cycle = 0;

  while (!Verilated::gotFinish()) {
    if (cycle < 2) top->rst = 1;
    else top->rst = 0;

    tfp->dump(cycle);
    top->clk = !top->clk;
    top->eval();
    cycle++;

    if (top->clk && !top->rst) {
      uint32_t inst = pmem_read(top->curr_pc);
      top->inst = inst;
      printf("PC=0x%08x  inst=0x%08x\n", top->curr_pc, inst);
      instr_cnt++;
      if (instr_cnt >= instr_limit) break;
    }
  }

  tfp->close();
  delete top;
  return 0;
}

// test.cpp
#include "verilated_vcd_c.h"
#include "Vysyx_25020059_top.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstdint>

#define CONFIG_MBASE 0x80000000
#define CONFIG_MSIZE 0x02800000  // 40 MB

typedef uint32_t paddr_t;
typedef uint64_t word_t;

// 模拟物理内存
static uint8_t *pimem = nullptr;

// 动态申请内存
void init_imem() {
  pimem = (uint8_t *)malloc(CONFIG_MSIZE);
  assert(pimem && "Failed to allocate instruction memory");
}

// 物理地址到主机地址映射
uint8_t* guest_to_host(paddr_t paddr) {
  assert(paddr >= CONFIG_MBASE && paddr < CONFIG_MBASE + CONFIG_MSIZE);
  return pimem + (paddr - CONFIG_MBASE);
}

// 从模拟内存读取 len 字节 (1/2/4/8)
static inline word_t host_read(void *addr, int len) {
  switch (len) {
    case 1: return *(uint8_t  *)addr;
    case 2: return *(uint16_t *)addr;
    case 4: return *(uint32_t *)addr;
    case 8: return *(uint64_t *)addr;
    default: assert(false && "Unsupported read length"); return 0;
  }
}
static word_t pmem_read(paddr_t addr, int len) {
  return host_read(guest_to_host(addr), len);
}

// 加载二进制镜像到 pimem 起始处
static long load_img(const char *img_file) {
  if (!img_file) {
    fprintf(stderr, "Error: no image file specified\n");
    exit(1);
  }
  FILE *fp = fopen(img_file, "rb");
  assert(fp && "Failed to open image file");
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  size_t ret = fread(guest_to_host(CONFIG_MBASE), 1, size, fp);
  assert(ret == (size_t)size && "Failed to read entire image");
  fclose(fp);
  printf("Loaded image '%s', size = %ld bytes\n", img_file, size);
  return size;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <image.bin>\n", argv[0]);
    return 1;
  }

  // 初始化 Verilator 顶层
  Verilated::commandArgs(argc, argv);
  auto *top = new Vysyx_25020059_top;

  // 打开 VCD 波形
  Verilated::traceEverOn(true);
  auto *tfp = new VerilatedVcdC;
  top->trace(tfp, 99);
  tfp->open("npc_addi.vcd");

  // 初始化时钟和复位
  top->clk = 0;
  top->rst = 1;

  // 初始化模拟内存并加载镜像
  init_imem();
  load_img(argv[1]);

  const int INSTR_LIMIT = 5;   // 最多执行 5 条 addi
  int instr_cnt = 0;
  int cycle = 0;

  // 模拟循环
  while (!Verilated::gotFinish()) {
    // 复位前两个时钟周期
    if (cycle < 2) {
      top->rst = 1;
    } else {
      top->rst = 0;
    }

    // 时钟翻转
    tfp->dump(cycle);
    top->clk = !top->clk;
    top->eval();
    cycle++;

    // 在上升沿后采样
    if (top->clk && !top->rst) {
      // 取指：4 字节
      uint32_t inst = (uint32_t)pmem_read(top->curr_pc, 4);
      top->inst = inst;

      // 打印调试信息
      printf("Instr %02d: PC=0x%08x  inst=0x%08x\n",
             instr_cnt, (uint32_t)top->curr_pc, inst);

      instr_cnt++;
      if (instr_cnt >= INSTR_LIMIT) {
        printf("Reached instruction limit (%d), finishing simulation.\n", INSTR_LIMIT);
        break;
      }
    }
  }

  // 结束并保存波形
  tfp->close();
  delete top;
  return 0;
}

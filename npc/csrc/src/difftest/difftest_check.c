#include "difftest/difftest-def.h"
#include "cpu_state.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>

extern CPU_state cpu;

const char *ref_regname[] = {
    "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5"
} ;

static void print_diff_table(CPU_state *dut, CPU_state *ref_r, vaddr_t pc, int reg_count) {
  printf("\n[DIFFTEST] PC = 0x%08x\n", pc);
  printf("---------------------------------------------------------------\n");
  printf("| %-3s |    DUT (NPC)   |    REF (NEMU)   | Status  |\n", "Reg");
  printf("---------------------------------------------------------------\n");

  for (int i = 0; i < reg_count; i++) {
    bool diff = (dut->gpr[i] != ref_r->gpr[i]);
    printf("| %-3s | 0x%08x     | 0x%08x     | %s%-7s\033[0m |\n",
           ref_regname[i],
           dut->gpr[i],
           ref_r->gpr[i],
           diff ? "\033[1;31m" : "\033[1;32m",
           diff ? "DIFF" : "OK");
  }

  // 打印 PC
  bool pc_diff = (dut->pc != ref_r->pc);
  printf("---------------------------------------------------------------\n");
  printf("| %-3s | 0x%08x     | 0x%08x     | %s%-7s\033[0m |\n",
         "pc",
         dut->pc,
         ref_r->pc,
         pc_diff ? "\033[1;31m" : "\033[1;32m",
         pc_diff ? "DIFF" : "OK");
  printf("---------------------------------------------------------------\n\n");
}

// 检查寄存器和 PC 是否一致
bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  bool same = true;
  int reg_count = 16;  // 只比较前16个寄存器，可修改为32

  // 先判断是否存在差异
  bool has_diff = false;
  for (int i = 0; i < reg_count; i++) {
    if (cpu.gpr[i] != ref_r->gpr[i]) {
      has_diff = true;
      break;
    }
  }
  if (cpu.pc != ref_r->pc) has_diff = true;

  if (!has_diff) return true;

  // 有差异才打印表格
  print_diff_table(&cpu, ref_r, pc, reg_count);

  // 再判断 same
  for (int i = 0; i < reg_count; i++)
    if (cpu.gpr[i] != ref_r->gpr[i]) same = false;
  if (cpu.pc != ref_r->pc) same = false;

  return same;
}
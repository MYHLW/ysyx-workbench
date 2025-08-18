#include <difftest/difftest_check.h>
#include <cpu/cpu_state.h>
#include <stdio.h>
#include <stdbool.h>

/* 只打印前16个通用寄存器的名字数组 */
static const char *regs[] = {
    "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5"
};

/* 比较寄存器并返回是否完全相同（不做任何打印） */
bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  /* 比较通用寄存器 */
  for (int i = 0; i < 32; i++) {
    if (cpu.gpr[i] != ref_r->gpr[i]) return false;
  }

  /* 比较 PC */
  if (cpu.pc != ref_r->pc) return false;

  /* 比较常用 CSR（若你的 CPU_state 包含这些字段） */
  if (cpu.mstatus != ref_r->mstatus) return false;
  if (cpu.mcause  != ref_r->mcause)  return false;
  if (cpu.mepc    != ref_r->mepc)    return false;
  if (cpu.mtvec   != ref_r->mtvec)   return false;

  return true;
}

void isa_difftest_attach() {
}

/* 打印差异表格（在比较失败时调用） */
void isa_difftest_print_diff(CPU_state *ref_r, vaddr_t pc) {
  printf("\n[DIFFTEST] PC = 0x%08x\n", (unsigned)pc);
  printf("-------------------------------------------------------------------\n");
  printf("| %-3s |      DUT (NEMU)     |      REF (Other)    | Status  |\n", "Reg");
  printf("-------------------------------------------------------------------\n");

  /* 只打印前16个通用寄存器 */
  for (int i = 0; i < 16; i++) {
    bool diff = (cpu.gpr[i] != ref_r->gpr[i]);

    printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
           regs[i],
           (unsigned)cpu.gpr[i],
           (unsigned)ref_r->gpr[i],
           diff ? "\033[1;31m" : "\033[1;32m",
           diff ? "DIFF" : "OK");
  }

  /* PC 行 */
  bool pc_diff = (cpu.pc != ref_r->pc);
  printf("-------------------------------------------------------------------\n");
  printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
         "pc",
         (unsigned)cpu.pc,
         (unsigned)ref_r->pc,
         pc_diff ? "\033[1;31m" : "\033[1;32m",
         pc_diff ? "DIFF" : "OK");

  /* CSR 行：mstatus, mcause, mepc, mtvec */
  bool mstatus_diff = (cpu.mstatus != ref_r->mstatus);
  printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
         "mst",
         (unsigned)cpu.mstatus,
         (unsigned)ref_r->mstatus,
         mstatus_diff ? "\033[1;31m" : "\033[1;32m",
         mstatus_diff ? "DIFF" : "OK");

  bool mcause_diff = (cpu.mcause != ref_r->mcause);
  printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
         "mca",
         (unsigned)cpu.mcause,
         (unsigned)ref_r->mcause,
         mcause_diff ? "\033[1;31m" : "\033[1;32m",
         mcause_diff ? "DIFF" : "OK");

  bool mepc_diff = (cpu.mepc != ref_r->mepc);
  printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
         "mep",
         (unsigned)cpu.mepc,
         (unsigned)ref_r->mepc,
         mepc_diff ? "\033[1;31m" : "\033[1;32m",
         mepc_diff ? "DIFF" : "OK");

  bool mtvec_diff = (cpu.mtvec != ref_r->mtvec);
  printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
         "mtv",
         (unsigned)cpu.mtvec,
         (unsigned)ref_r->mtvec,
         mtvec_diff ? "\033[1;31m" : "\033[1;32m",
         mtvec_diff ? "DIFF" : "OK");

  printf("-------------------------------------------------------------------\n\n");
}

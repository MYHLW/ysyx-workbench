#include <isa.h>
#include <cpu/cpu.h>
#include <difftest-def.h>
#include <memory/paddr.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

__EXPORT void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction) {
  if (direction == DIFFTEST_TO_REF) {
    memcpy(guest_to_host(addr), buf, n);
  } else {
    memcpy(buf, guest_to_host(addr), n);
  }
}

/* 
 * difftest_regcpy: copy register file and CSRs between DUT buffer and REF cpu.
 *
 * We expect the buffer pointed to by 'dut' to have the layout:
 * typedef struct {
 *   uint32_t gpr[32];
 *   uint32_t pc;
 *   word_t mepc;  
 *   word_t mcause;
 *   word_t mtvec;
 *   word_t mstatus;
 * } CPU_state;
 *
 * direction == DIFFTEST_TO_REF : copy from DUT -> REF (cpu)
 * direction == DIFFTEST_TO_DUT : copy from REF (cpu) -> DUT (buffer)
 */
__EXPORT void difftest_regcpy(void *dut, bool direction) {
  if (direction == DIFFTEST_TO_REF) {
    /* copy from DUT buffer into reference cpu state */
    CPU_state *d = (CPU_state *)dut;

    /* general purpose registers */
    memcpy(cpu.gpr, d->gpr, sizeof(cpu.gpr));

    /* program counter */
    cpu.pc = d->pc;

    /* CSRs */
    cpu.mepc   = d->mepc;
    cpu.mcause = d->mcause;
    cpu.mtvec  = d->mtvec;
    cpu.mstatus= d->mstatus;

    /* If DIFFTEST_REG_SIZE is used elsewhere to sanity-check, it should
       match sizeof(CPU_state). We intentionally copy fields explicitly
       to avoid any layout mismatch issues. */

  } else {
    /* copy from reference cpu state into DUT buffer */
    CPU_state *d = (CPU_state *)dut;

    /* general purpose registers */
    memcpy(d->gpr, cpu.gpr, sizeof(cpu.gpr));

    /* program counter */
    d->pc = cpu.pc;

    /* CSRs */
    d->mepc    = cpu.mepc;
    d->mcause  = cpu.mcause;
    d->mtvec   = cpu.mtvec;
    d->mstatus = cpu.mstatus;
  }
}

__EXPORT void difftest_exec(uint64_t n) {
  cpu_exec(n);
}

__EXPORT void difftest_raise_intr(word_t NO) {
  assert(0);
}

__EXPORT void difftest_init(int port) {
  void init_mem();
  init_mem();
  /* Perform ISA dependent initialization. */
  init_isa();
#ifdef CONFIG_ITRACE
  extern void init_disasm(void);
  init_disasm();
#endif
  /* 让 disassemble() 的函数指针/handle 都初始化好 */
}

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#ifndef VERILATED_VYSYX_25020059_TOP__DPI_H_
#define VERILATED_VYSYX_25020059_TOP__DPI_H_  // guard

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at /home/wang/ysyx-workbench/npc/vsrc/ctrl.v:4:30
    extern void npc_trap(int code);
    // DPI import at /home/wang/ysyx-workbench/npc/vsrc/memory_if.v:5:43
    extern unsigned int pmem_read(unsigned int raddr, int i);
    // DPI import at /home/wang/ysyx-workbench/npc/vsrc/memory_if.v:6:43
    extern void pmem_write(unsigned int waddr, unsigned int wdata, char wmask);

#ifdef __cplusplus
}
#endif

#endif  // guard

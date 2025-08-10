// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_25020059_top.h for the primary calling header

#include "Vysyx_25020059_top__pch.h"
#include "Vysyx_25020059_top__Syms.h"
#include "Vysyx_25020059_top___024unit.h"

extern "C" void npc_trap(int code);

VL_INLINE_OPT void Vysyx_25020059_top___024unit____Vdpiimwrap_npc_trap_TOP____024unit(IData/*31:0*/ code) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vysyx_25020059_top___024unit____Vdpiimwrap_npc_trap_TOP____024unit\n"); );
    // Body
    int code__Vcvt;
    for (size_t code__Vidx = 0; code__Vidx < 1; ++code__Vidx) code__Vcvt = code;
    npc_trap(code__Vcvt);
}

extern "C" unsigned int pmem_r(unsigned int raddr, int i);

VL_INLINE_OPT void Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_r_TOP____024unit(IData/*31:0*/ raddr, IData/*31:0*/ i, IData/*31:0*/ &pmem_r__Vfuncrtn) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_r_TOP____024unit\n"); );
    // Body
    unsigned int raddr__Vcvt;
    for (size_t raddr__Vidx = 0; raddr__Vidx < 1; ++raddr__Vidx) raddr__Vcvt = raddr;
    int i__Vcvt;
    for (size_t i__Vidx = 0; i__Vidx < 1; ++i__Vidx) i__Vcvt = i;
    unsigned int pmem_r__Vfuncrtn__Vcvt;
    pmem_r__Vfuncrtn__Vcvt = pmem_r(raddr__Vcvt, i__Vcvt);
    pmem_r__Vfuncrtn = pmem_r__Vfuncrtn__Vcvt;
}

extern "C" void pmem_w(unsigned int waddr, unsigned int wdata, char wmask);

VL_INLINE_OPT void Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_w_TOP____024unit(IData/*31:0*/ waddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_w_TOP____024unit\n"); );
    // Body
    unsigned int waddr__Vcvt;
    for (size_t waddr__Vidx = 0; waddr__Vidx < 1; ++waddr__Vidx) waddr__Vcvt = waddr;
    unsigned int wdata__Vcvt;
    for (size_t wdata__Vidx = 0; wdata__Vidx < 1; ++wdata__Vidx) wdata__Vcvt = wdata;
    char wmask__Vcvt;
    for (size_t wmask__Vidx = 0; wmask__Vidx < 1; ++wmask__Vidx) wmask__Vcvt = wmask;
    pmem_w(waddr__Vcvt, wdata__Vcvt, wmask__Vcvt);
}

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

extern "C" void set_gpr_ptr(const svLogicVecVal* r);

VL_INLINE_OPT void Vysyx_25020059_top___024unit____Vdpiimwrap_set_gpr_ptr_TOP____024unit(VlUnpacked<IData/*31:0*/, 32> r) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vysyx_25020059_top___024unit____Vdpiimwrap_set_gpr_ptr_TOP____024unit\n"); );
    // Body
    svLogicVecVal r__Vcvt[32];
    for (size_t r__Vidx = 0; r__Vidx < 32; ++r__Vidx) VL_SET_SVLV_I(32, r__Vcvt + 1 * r__Vidx, (&r[0])[r__Vidx]);
    set_gpr_ptr(r__Vcvt);
}

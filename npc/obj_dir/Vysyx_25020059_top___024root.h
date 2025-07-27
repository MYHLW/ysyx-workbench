// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vysyx_25020059_top.h for the primary calling header

#ifndef VERILATED_VYSYX_25020059_TOP___024ROOT_H_
#define VERILATED_VYSYX_25020059_TOP___024ROOT_H_  // guard

#include "verilated.h"
class Vysyx_25020059_top___024unit;


class Vysyx_25020059_top__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vysyx_25020059_top___024root final : public VerilatedModule {
  public:
    // CELLS
    Vysyx_25020059_top___024unit* __PVT____024unit;

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    CData/*0:0*/ ysyx_25020059_top__DOT__rst_n;
    VL_IN8(rst,0,0);
    CData/*0:0*/ ysyx_25020059_top__DOT__ena;
    CData/*0:0*/ ysyx_25020059_top__DOT__branch;
    CData/*0:0*/ ysyx_25020059_top__DOT__zero;
    CData/*0:0*/ ysyx_25020059_top__DOT__jal_jump;
    CData/*0:0*/ ysyx_25020059_top__DOT__jalr_jump;
    CData/*0:0*/ ysyx_25020059_top__DOT__reg_wen;
    CData/*4:0*/ ysyx_25020059_top__DOT__reg_waddr;
    CData/*4:0*/ ysyx_25020059_top__DOT__reg1_raddr;
    CData/*4:0*/ ysyx_25020059_top__DOT__reg2_raddr;
    CData/*2:0*/ ysyx_25020059_top__DOT__imm_gen_op;
    CData/*3:0*/ ysyx_25020059_top__DOT__alu_op;
    CData/*1:0*/ ysyx_25020059_top__DOT__alu_src_sel;
    CData/*0:0*/ ysyx_25020059_top__DOT__mem_valid;
    CData/*0:0*/ ysyx_25020059_top__DOT__mem_wen;
    CData/*1:0*/ ysyx_25020059_top__DOT__mem_size;
    CData/*0:0*/ ysyx_25020059_top__DOT__mem_unsigned;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__ysyx_25020059_top__DOT__rst_n__0;
    CData/*0:0*/ __VactContinue;
    VL_IN(inst,31,0);
    VL_OUT(curr_pc,31,0);
    VL_OUT(next_pc,31,0);
    IData/*31:0*/ ysyx_25020059_top__DOT__reg1_rdata;
    IData/*31:0*/ ysyx_25020059_top__DOT__reg2_rdata;
    IData/*31:0*/ ysyx_25020059_top__DOT__imm;
    IData/*31:0*/ ysyx_25020059_top__DOT__alu_src1;
    IData/*31:0*/ ysyx_25020059_top__DOT__alu_src2;
    IData/*31:0*/ ysyx_25020059_top__DOT__alu_res;
    IData/*31:0*/ ysyx_25020059_top__DOT__mem_rdata;
    IData/*31:0*/ ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data;
    IData/*31:0*/ __Vfunc_pmem_read__1__Vfuncout;
    IData/*31:0*/ __VactIterCount;
    VL_OUT(reg_f[32],31,0);
    VlUnpacked<CData/*0:0*/, 3> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vysyx_25020059_top__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vysyx_25020059_top___024root(Vysyx_25020059_top__Syms* symsp, const char* v__name);
    ~Vysyx_25020059_top___024root();
    VL_UNCOPYABLE(Vysyx_25020059_top___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard

// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_25020059_top.h for the primary calling header

#include "Vysyx_25020059_top__pch.h"
#include "Vysyx_25020059_top___024root.h"

void Vysyx_25020059_top___024root___ico_sequent__TOP__0(Vysyx_25020059_top___024root* vlSelf);

void Vysyx_25020059_top___024root___eval_ico(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_ico\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vysyx_25020059_top___024root___ico_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
}

VL_INLINE_OPT void Vysyx_25020059_top___024root___ico_sequent__TOP__0(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___ico_sequent__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.ysyx_25020059_top__DOT__rst_n = (1U & 
                                               (~ (IData)(vlSelfRef.rst)));
    vlSelfRef.ysyx_25020059_top__DOT__reg_waddr = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__jump = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 0U;
    if ((0x33U == (0x7fU & vlSelfRef.inst))) {
        vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
            = (0x1fU & (vlSelfRef.inst >> 7U));
        vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
        if ((0U == (7U & (vlSelfRef.inst >> 0xcU)))) {
            vlSelfRef.ysyx_25020059_top__DOT__alu_op 
                = ((0U == (vlSelfRef.inst >> 0x19U))
                    ? 3U : 4U);
        }
        vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr 
            = (0x1fU & (vlSelfRef.inst >> 0xfU));
        vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr 
            = (0x1fU & (vlSelfRef.inst >> 0x14U));
        vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 0U;
    } else {
        if ((0x13U == (0x7fU & vlSelfRef.inst))) {
            vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                = (0x1fU & (vlSelfRef.inst >> 7U));
            vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
            if ((0U == (7U & (vlSelfRef.inst >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
            }
            vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr 
                = (0x1fU & (vlSelfRef.inst >> 0xfU));
            vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 1U;
        } else {
            if ((0x63U != (0x7fU & vlSelfRef.inst))) {
                if ((0x6fU == (0x7fU & vlSelfRef.inst))) {
                    vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                        = (0x1fU & (vlSelfRef.inst 
                                    >> 7U));
                    vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
                } else if ((0x37U == (0x7fU & vlSelfRef.inst))) {
                    vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                        = (0x1fU & (vlSelfRef.inst 
                                    >> 7U));
                    vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
                }
            }
            if ((0x63U == (0x7fU & vlSelfRef.inst))) {
                if ((1U == (7U & (vlSelfRef.inst >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 4U;
                }
                vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr 
                    = (0x1fU & (vlSelfRef.inst >> 0xfU));
                vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 0U;
            } else {
                if ((0x6fU == (0x7fU & vlSelfRef.inst))) {
                    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
                    vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 2U;
                } else if ((0x37U == (0x7fU & vlSelfRef.inst))) {
                    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
                    vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 1U;
                }
                if ((0x6fU != (0x7fU & vlSelfRef.inst))) {
                    if ((0x37U == (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr = 0U;
                    }
                }
            }
        }
        if ((0x13U != (0x7fU & vlSelfRef.inst))) {
            if ((0x63U == (0x7fU & vlSelfRef.inst))) {
                vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr 
                    = (0x1fU & (vlSelfRef.inst >> 0x14U));
            }
        }
    }
    vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op = 0U;
    if ((0x33U != (0x7fU & vlSelfRef.inst))) {
        if ((0x13U != (0x7fU & vlSelfRef.inst))) {
            if ((0x63U != (0x7fU & vlSelfRef.inst))) {
                if ((0x6fU == (0x7fU & vlSelfRef.inst))) {
                    vlSelfRef.ysyx_25020059_top__DOT__jump = 1U;
                }
            }
            if ((0x63U == (0x7fU & vlSelfRef.inst))) {
                if ((1U == (7U & (vlSelfRef.inst >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__branch = 1U;
                }
                vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op = 2U;
            } else if ((0x6fU == (0x7fU & vlSelfRef.inst))) {
                vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op = 3U;
            } else if ((0x37U == (0x7fU & vlSelfRef.inst))) {
                vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op = 4U;
            }
        }
    }
    vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata = 
        ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr))
          ? 0U : vlSelfRef.ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f
         [vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr]);
    vlSelfRef.ysyx_25020059_top__DOT__reg2_rdata = 
        ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr))
          ? 0U : vlSelfRef.ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f
         [vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr]);
    vlSelfRef.ysyx_25020059_top__DOT__imm = 0U;
    if ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__imm = (((- (IData)(
                                                             (vlSelfRef.inst 
                                                              >> 0x1fU))) 
                                                  << 0xcU) 
                                                 | (vlSelfRef.inst 
                                                    >> 0x14U));
    } else if ((1U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__imm = (((- (IData)(
                                                             (vlSelfRef.inst 
                                                              >> 0x1fU))) 
                                                  << 0xcU) 
                                                 | ((0xfe0U 
                                                     & (vlSelfRef.inst 
                                                        >> 0x14U)) 
                                                    | (0x1fU 
                                                       & (vlSelfRef.inst 
                                                          >> 7U))));
    } else if ((2U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__imm = (((- (IData)(
                                                             (vlSelfRef.inst 
                                                              >> 0x1fU))) 
                                                  << 0xcU) 
                                                 | ((0x800U 
                                                     & (vlSelfRef.inst 
                                                        << 4U)) 
                                                    | ((0x7e0U 
                                                        & (vlSelfRef.inst 
                                                           >> 0x14U)) 
                                                       | (0x1eU 
                                                          & (vlSelfRef.inst 
                                                             >> 7U)))));
    } else if ((3U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__imm = (((- (IData)(
                                                             (vlSelfRef.inst 
                                                              >> 0x1fU))) 
                                                  << 0x14U) 
                                                 | ((0xff000U 
                                                     & vlSelfRef.inst) 
                                                    | ((0x800U 
                                                        & (vlSelfRef.inst 
                                                           >> 9U)) 
                                                       | (0x7feU 
                                                          & (vlSelfRef.inst 
                                                             >> 0x14U)))));
    } else if ((4U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__imm = (0xfffff000U 
                                                 & vlSelfRef.inst);
    }
    if ((2U & (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel))) {
        vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
            = ((1U & (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel))
                ? vlSelfRef.ysyx_25020059_top__DOT__imm
                : 4U);
        vlSelfRef.ysyx_25020059_top__DOT__alu_src2 
            = vlSelfRef.curr_pc;
    } else {
        vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
            = vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata;
        vlSelfRef.ysyx_25020059_top__DOT__alu_src2 
            = ((1U & (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel))
                ? vlSelfRef.ysyx_25020059_top__DOT__imm
                : vlSelfRef.ysyx_25020059_top__DOT__reg2_rdata);
    }
    vlSelfRef.ysyx_25020059_top__DOT__zero = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__alu_res = 0U;
    if ((3U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__alu_res = 
            (vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
             + vlSelfRef.ysyx_25020059_top__DOT__alu_src2);
    } else if ((4U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__alu_res = 
            (vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
             - vlSelfRef.ysyx_25020059_top__DOT__alu_src2);
        vlSelfRef.ysyx_25020059_top__DOT__zero = (0U 
                                                  == vlSelfRef.ysyx_25020059_top__DOT__alu_res);
    }
    vlSelfRef.next_pc = ((IData)(vlSelfRef.ysyx_25020059_top__DOT__ena)
                          ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__jump)
                              ? (vlSelfRef.curr_pc 
                                 + vlSelfRef.ysyx_25020059_top__DOT__imm)
                              : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__branch) 
                                  & (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero))
                                  ? (vlSelfRef.curr_pc 
                                     + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                  : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__branch) 
                                      & (~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero)))
                                      ? (vlSelfRef.curr_pc 
                                         + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                      : ((IData)(4U) 
                                         + vlSelfRef.curr_pc))))
                          : vlSelfRef.curr_pc);
}

void Vysyx_25020059_top___024root___eval_triggers__ico(Vysyx_25020059_top___024root* vlSelf);

bool Vysyx_25020059_top___024root___eval_phase__ico(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_phase__ico\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vysyx_25020059_top___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vysyx_25020059_top___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vysyx_25020059_top___024root___eval_act(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_act\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
}

void Vysyx_25020059_top___024root___nba_sequent__TOP__0(Vysyx_25020059_top___024root* vlSelf);

void Vysyx_25020059_top___024root___eval_nba(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_nba\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vysyx_25020059_top___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
    }
}

VL_INLINE_OPT void Vysyx_25020059_top___024root___nba_sequent__TOP__0(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___nba_sequent__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f__v0;
    __VdlyVal__ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f__v0 = 0;
    CData/*4:0*/ __VdlyDim0__ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f__v0;
    __VdlyDim0__ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f__v0 = 0;
    CData/*0:0*/ __VdlySet__ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f__v0;
    __VdlySet__ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f__v0 = 0;
    // Body
    __VdlySet__ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f__v0 = 0U;
    if ((((IData)(vlSelfRef.ysyx_25020059_top__DOT__rst_n) 
          & (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg_wen)) 
         & (0U != (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg_waddr)))) {
        __VdlyVal__ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f__v0 
            = vlSelfRef.ysyx_25020059_top__DOT__alu_res;
        __VdlyDim0__ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f__v0 
            = vlSelfRef.ysyx_25020059_top__DOT__reg_waddr;
        __VdlySet__ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f__v0 = 1U;
    }
    if (vlSelfRef.ysyx_25020059_top__DOT__rst_n) {
        vlSelfRef.ysyx_25020059_top__DOT__ena = 1U;
        vlSelfRef.curr_pc = vlSelfRef.next_pc;
    } else {
        vlSelfRef.ysyx_25020059_top__DOT__ena = 0U;
        vlSelfRef.curr_pc = 0x80000000U;
    }
    if (__VdlySet__ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f__v0) {
        vlSelfRef.ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f[__VdlyDim0__ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f__v0] 
            = __VdlyVal__ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f__v0;
    }
    vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata = 
        ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr))
          ? 0U : vlSelfRef.ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f
         [vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr]);
    vlSelfRef.ysyx_25020059_top__DOT__reg2_rdata = 
        ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr))
          ? 0U : vlSelfRef.ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f
         [vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr]);
    if ((2U & (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel))) {
        vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
            = ((1U & (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel))
                ? vlSelfRef.ysyx_25020059_top__DOT__imm
                : 4U);
        vlSelfRef.ysyx_25020059_top__DOT__alu_src2 
            = vlSelfRef.curr_pc;
    } else {
        vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
            = vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata;
        vlSelfRef.ysyx_25020059_top__DOT__alu_src2 
            = ((1U & (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel))
                ? vlSelfRef.ysyx_25020059_top__DOT__imm
                : vlSelfRef.ysyx_25020059_top__DOT__reg2_rdata);
    }
    vlSelfRef.ysyx_25020059_top__DOT__zero = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__alu_res = 0U;
    if ((3U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__alu_res = 
            (vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
             + vlSelfRef.ysyx_25020059_top__DOT__alu_src2);
    } else if ((4U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__alu_res = 
            (vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
             - vlSelfRef.ysyx_25020059_top__DOT__alu_src2);
        vlSelfRef.ysyx_25020059_top__DOT__zero = (0U 
                                                  == vlSelfRef.ysyx_25020059_top__DOT__alu_res);
    }
    vlSelfRef.next_pc = ((IData)(vlSelfRef.ysyx_25020059_top__DOT__ena)
                          ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__jump)
                              ? (vlSelfRef.curr_pc 
                                 + vlSelfRef.ysyx_25020059_top__DOT__imm)
                              : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__branch) 
                                  & (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero))
                                  ? (vlSelfRef.curr_pc 
                                     + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                  : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__branch) 
                                      & (~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero)))
                                      ? (vlSelfRef.curr_pc 
                                         + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                      : ((IData)(4U) 
                                         + vlSelfRef.curr_pc))))
                          : vlSelfRef.curr_pc);
}

void Vysyx_25020059_top___024root___eval_triggers__act(Vysyx_25020059_top___024root* vlSelf);

bool Vysyx_25020059_top___024root___eval_phase__act(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_phase__act\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vysyx_25020059_top___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vysyx_25020059_top___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vysyx_25020059_top___024root___eval_phase__nba(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_phase__nba\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vysyx_25020059_top___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_25020059_top___024root___dump_triggers__ico(Vysyx_25020059_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_25020059_top___024root___dump_triggers__nba(Vysyx_25020059_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_25020059_top___024root___dump_triggers__act(Vysyx_25020059_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vysyx_25020059_top___024root___eval(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY((0x64U < __VicoIterCount))) {
#ifdef VL_DEBUG
            Vysyx_25020059_top___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("vsrc/top.v", 4, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vysyx_25020059_top___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
            Vysyx_25020059_top___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("vsrc/top.v", 4, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY((0x64U < vlSelfRef.__VactIterCount))) {
#ifdef VL_DEBUG
                Vysyx_25020059_top___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("vsrc/top.v", 4, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vysyx_25020059_top___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vysyx_25020059_top___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vysyx_25020059_top___024root___eval_debug_assertions(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_debug_assertions\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY((vlSelfRef.clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelfRef.rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG

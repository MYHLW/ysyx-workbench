// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_25020059_top.h for the primary calling header

#include "Vysyx_25020059_top__pch.h"
#include "Vysyx_25020059_top___024root.h"

VL_ATTR_COLD void Vysyx_25020059_top___024root___eval_static(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_static\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vysyx_25020059_top___024root___eval_initial(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_initial\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__ysyx_25020059_top__DOT__rst_n__0 
        = vlSelfRef.ysyx_25020059_top__DOT__rst_n;
}

VL_ATTR_COLD void Vysyx_25020059_top___024root___eval_final(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_final\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_25020059_top___024root___dump_triggers__stl(Vysyx_25020059_top___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vysyx_25020059_top___024root___eval_phase__stl(Vysyx_25020059_top___024root* vlSelf);

VL_ATTR_COLD void Vysyx_25020059_top___024root___eval_settle(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_settle\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vysyx_25020059_top___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("vsrc/top.v", 4, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vysyx_25020059_top___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_25020059_top___024root___dump_triggers__stl(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___dump_triggers__stl\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vysyx_25020059_top___024root___stl_sequent__TOP__0(Vysyx_25020059_top___024root* vlSelf);
VL_ATTR_COLD void Vysyx_25020059_top___024root____Vm_traceActivitySetAll(Vysyx_25020059_top___024root* vlSelf);

VL_ATTR_COLD void Vysyx_25020059_top___024root___eval_stl(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_stl\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vysyx_25020059_top___024root___stl_sequent__TOP__0(vlSelf);
        Vysyx_25020059_top___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD void Vysyx_25020059_top___024root___stl_sequent__TOP__0(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___stl_sequent__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.ysyx_25020059_top__DOT__reg_waddr = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__rst_n = (1U & 
                                               (~ (IData)(vlSelfRef.rst)));
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

VL_ATTR_COLD void Vysyx_25020059_top___024root___eval_triggers__stl(Vysyx_25020059_top___024root* vlSelf);

VL_ATTR_COLD bool Vysyx_25020059_top___024root___eval_phase__stl(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_phase__stl\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vysyx_25020059_top___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vysyx_25020059_top___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_25020059_top___024root___dump_triggers__ico(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___dump_triggers__ico\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_25020059_top___024root___dump_triggers__act(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___dump_triggers__act\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((2ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(negedge ysyx_25020059_top.rst_n)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_25020059_top___024root___dump_triggers__nba(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___dump_triggers__nba\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
    if ((2ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(negedge ysyx_25020059_top.rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vysyx_25020059_top___024root____Vm_traceActivitySetAll(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root____Vm_traceActivitySetAll\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
}

VL_ATTR_COLD void Vysyx_25020059_top___024root___ctor_var_reset(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___ctor_var_reset\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst = VL_RAND_RESET_I(1);
    vlSelf->inst = VL_RAND_RESET_I(32);
    vlSelf->curr_pc = VL_RAND_RESET_I(32);
    vlSelf->next_pc = VL_RAND_RESET_I(32);
    vlSelf->ysyx_25020059_top__DOT__rst_n = VL_RAND_RESET_I(1);
    vlSelf->ysyx_25020059_top__DOT__ena = VL_RAND_RESET_I(1);
    vlSelf->ysyx_25020059_top__DOT__branch = VL_RAND_RESET_I(1);
    vlSelf->ysyx_25020059_top__DOT__zero = VL_RAND_RESET_I(1);
    vlSelf->ysyx_25020059_top__DOT__jump = VL_RAND_RESET_I(1);
    vlSelf->ysyx_25020059_top__DOT__reg_wen = VL_RAND_RESET_I(1);
    vlSelf->ysyx_25020059_top__DOT__reg_waddr = VL_RAND_RESET_I(5);
    vlSelf->ysyx_25020059_top__DOT__reg1_raddr = VL_RAND_RESET_I(5);
    vlSelf->ysyx_25020059_top__DOT__reg2_raddr = VL_RAND_RESET_I(5);
    vlSelf->ysyx_25020059_top__DOT__reg1_rdata = VL_RAND_RESET_I(32);
    vlSelf->ysyx_25020059_top__DOT__reg2_rdata = VL_RAND_RESET_I(32);
    vlSelf->ysyx_25020059_top__DOT__imm_gen_op = VL_RAND_RESET_I(3);
    vlSelf->ysyx_25020059_top__DOT__imm = VL_RAND_RESET_I(32);
    vlSelf->ysyx_25020059_top__DOT__alu_op = VL_RAND_RESET_I(4);
    vlSelf->ysyx_25020059_top__DOT__alu_src_sel = VL_RAND_RESET_I(2);
    vlSelf->ysyx_25020059_top__DOT__alu_src1 = VL_RAND_RESET_I(32);
    vlSelf->ysyx_25020059_top__DOT__alu_src2 = VL_RAND_RESET_I(32);
    vlSelf->ysyx_25020059_top__DOT__alu_res = VL_RAND_RESET_I(32);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->ysyx_25020059_top__DOT__u_reg_file_0__DOT__reg_f[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigprevexpr___TOP__ysyx_25020059_top__DOT__rst_n__0 = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 3; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}

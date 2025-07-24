// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_25020059_top.h for the primary calling header

#include "Vysyx_25020059_top__pch.h"
#include "Vysyx_25020059_top__Syms.h"
#include "Vysyx_25020059_top___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_25020059_top___024root___dump_triggers__stl(Vysyx_25020059_top___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vysyx_25020059_top___024root___eval_triggers__stl(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_triggers__stl\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.set(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vysyx_25020059_top___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

void Vysyx_25020059_top___024unit____Vdpiimwrap_npc_trap_TOP____024unit(IData/*31:0*/ code);

VL_ATTR_COLD void Vysyx_25020059_top___024root___stl_sequent__TOP__0(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___stl_sequent__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((IData)((0x100073U == (0xfff0707fU & vlSelfRef.inst)))) {
        Vysyx_25020059_top___024unit____Vdpiimwrap_npc_trap_TOP____024unit(
                                                                           vlSelfRef.reg_f
                                                                           [0xaU]);
    }
    vlSelfRef.ysyx_25020059_top__DOT__reg_waddr = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__rst_n = (1U & 
                                               (~ (IData)(vlSelfRef.rst)));
    vlSelfRef.ysyx_25020059_top__DOT__jalr_jump = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__jal_jump = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op = 0U;
    if (((((((((0x33U == (0x7fU & vlSelfRef.inst)) 
               | (0x13U == (0x7fU & vlSelfRef.inst))) 
              | (0x67U == (0x7fU & vlSelfRef.inst))) 
             | (0x63U == (0x7fU & vlSelfRef.inst))) 
            | (0x6fU == (0x7fU & vlSelfRef.inst))) 
           | (0x37U == (0x7fU & vlSelfRef.inst))) | 
          (0x17U == (0x7fU & vlSelfRef.inst))) | (0x23U 
                                                  == 
                                                  (0x7fU 
                                                   & vlSelfRef.inst)))) {
        if ((0x33U == (0x7fU & vlSelfRef.inst))) {
            vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                = (0x1fU & (vlSelfRef.inst >> 7U));
            vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
            if ((0U == (7U & (vlSelfRef.inst >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__alu_op 
                    = ((0U == (vlSelfRef.inst >> 0x19U))
                        ? 3U : 4U);
            }
            vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr 
                = (0x1fU & (vlSelfRef.inst >> 0x14U));
            vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr 
                = (0x1fU & (vlSelfRef.inst >> 0xfU));
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
            } else if ((0x67U == (0x7fU & vlSelfRef.inst))) {
                vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                    = (0x1fU & (vlSelfRef.inst >> 7U));
                vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
                vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
                vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr 
                    = (0x1fU & (vlSelfRef.inst >> 0xfU));
                vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 2U;
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
                    } else if ((0x17U == (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                            = (0x1fU & (vlSelfRef.inst 
                                        >> 7U));
                        vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
                    }
                }
                if ((0x63U == (0x7fU & vlSelfRef.inst))) {
                    if ((1U == (7U & (vlSelfRef.inst 
                                      >> 0xcU)))) {
                        vlSelfRef.ysyx_25020059_top__DOT__alu_op = 4U;
                    }
                    vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr 
                        = (0x1fU & (vlSelfRef.inst 
                                    >> 0xfU));
                    vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 0U;
                } else {
                    if ((0x6fU == (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
                        vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 2U;
                    } else if ((0x37U == (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
                        vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 1U;
                    } else if ((0x17U == (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
                        vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 3U;
                    } else {
                        if ((0U == (7U & (vlSelfRef.inst 
                                          >> 0xcU)))) {
                            vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
                        } else if ((1U == (7U & (vlSelfRef.inst 
                                                 >> 0xcU)))) {
                            vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
                        } else if ((2U == (7U & (vlSelfRef.inst 
                                                 >> 0xcU)))) {
                            vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
                        }
                        vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 1U;
                    }
                    if ((0x6fU != (0x7fU & vlSelfRef.inst))) {
                        if ((0x37U == (0x7fU & vlSelfRef.inst))) {
                            vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr = 0U;
                        } else if ((0x17U != (0x7fU 
                                              & vlSelfRef.inst))) {
                            vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr 
                                = (0x1fU & (vlSelfRef.inst 
                                            >> 0xfU));
                        }
                    }
                }
            }
            if ((0x13U != (0x7fU & vlSelfRef.inst))) {
                if ((0x67U != (0x7fU & vlSelfRef.inst))) {
                    if ((0x63U == (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr 
                            = (0x1fU & (vlSelfRef.inst 
                                        >> 0x14U));
                    } else if ((0x6fU != (0x7fU & vlSelfRef.inst))) {
                        if ((0x37U != (0x7fU & vlSelfRef.inst))) {
                            if ((0x17U != (0x7fU & vlSelfRef.inst))) {
                                vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr 
                                    = (0x1fU & (vlSelfRef.inst 
                                                >> 0x14U));
                            }
                        }
                    }
                }
            }
        }
        if ((0x33U != (0x7fU & vlSelfRef.inst))) {
            if ((0x13U != (0x7fU & vlSelfRef.inst))) {
                if ((0x67U == (0x7fU & vlSelfRef.inst))) {
                    vlSelfRef.ysyx_25020059_top__DOT__jalr_jump = 1U;
                }
                if ((0x67U != (0x7fU & vlSelfRef.inst))) {
                    if ((0x63U != (0x7fU & vlSelfRef.inst))) {
                        if ((0x6fU == (0x7fU & vlSelfRef.inst))) {
                            vlSelfRef.ysyx_25020059_top__DOT__jal_jump = 1U;
                        }
                    }
                    if ((0x63U == (0x7fU & vlSelfRef.inst))) {
                        if ((1U == (7U & (vlSelfRef.inst 
                                          >> 0xcU)))) {
                            vlSelfRef.ysyx_25020059_top__DOT__branch = 1U;
                        }
                        vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op = 2U;
                    } else {
                        vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op 
                            = ((0x6fU == (0x7fU & vlSelfRef.inst))
                                ? 3U : ((0x37U == (0x7fU 
                                                   & vlSelfRef.inst))
                                         ? 4U : ((0x17U 
                                                  == 
                                                  (0x7fU 
                                                   & vlSelfRef.inst))
                                                  ? 4U
                                                  : 1U)));
                    }
                }
            }
        }
    }
    vlSelfRef.ysyx_25020059_top__DOT__reg2_rdata = 
        ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr))
          ? 0U : vlSelfRef.reg_f[vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr]);
    vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata = 
        ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr))
          ? 0U : vlSelfRef.reg_f[vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr]);
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
                          ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__jal_jump)
                              ? (vlSelfRef.curr_pc 
                                 + vlSelfRef.ysyx_25020059_top__DOT__imm)
                              : ((IData)(vlSelfRef.ysyx_25020059_top__DOT__jalr_jump)
                                  ? (0xfffffffeU & 
                                     (vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata 
                                      + vlSelfRef.ysyx_25020059_top__DOT__imm))
                                  : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__branch) 
                                      & (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero))
                                      ? (vlSelfRef.curr_pc 
                                         + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                      : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__branch) 
                                          & (~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero)))
                                          ? (vlSelfRef.curr_pc 
                                             + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                          : ((IData)(4U) 
                                             + vlSelfRef.curr_pc)))))
                          : vlSelfRef.curr_pc);
}

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
void Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_read_TOP____024unit(IData/*31:0*/ raddr, IData/*31:0*/ i, IData/*31:0*/ &pmem_read__Vfuncrtn);
void Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_write_TOP____024unit(IData/*31:0*/ waddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask);

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
    vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__reg_waddr = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__rst_n = (1U & 
                                               (~ (IData)(vlSelfRef.rst)));
    vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned = 0U;
    if ((1U & (~ ((((((((0x33U == (0x7fU & vlSelfRef.inst)) 
                        | (0x13U == (0x7fU & vlSelfRef.inst))) 
                       | (0x67U == (0x7fU & vlSelfRef.inst))) 
                      | (0x63U == (0x7fU & vlSelfRef.inst))) 
                     | (0x6fU == (0x7fU & vlSelfRef.inst))) 
                    | (0x37U == (0x7fU & vlSelfRef.inst))) 
                   | (0x17U == (0x7fU & vlSelfRef.inst))) 
                  | (0x23U == (0x7fU & vlSelfRef.inst)))))) {
        if ((3U == (0x7fU & vlSelfRef.inst))) {
            if ((0U == (7U & (vlSelfRef.inst >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned = 0U;
            } else if ((1U == (7U & (vlSelfRef.inst 
                                     >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned = 0U;
            } else if ((2U == (7U & (vlSelfRef.inst 
                                     >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned = 0U;
            } else if ((4U == (7U & (vlSelfRef.inst 
                                     >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned = 1U;
            } else if ((5U == (7U & (vlSelfRef.inst 
                                     >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned = 1U;
            }
        }
    }
    vlSelfRef.ysyx_25020059_top__DOT__mem_size = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__mem_wen = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__mem_valid = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__bge_branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__bltu_branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__blt_branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__bne_branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__beq_branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__bgeu_branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__jal_jump = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__jalr_jump = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr = 0U;
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
            vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
            vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                = (0x1fU & (vlSelfRef.inst >> 7U));
            if ((0U == (7U & (vlSelfRef.inst >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__alu_op 
                    = ((0U == (vlSelfRef.inst >> 0x19U))
                        ? 3U : 4U);
            } else if ((2U == (7U & (vlSelfRef.inst 
                                     >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__alu_op = 8U;
            } else if ((3U == (7U & (vlSelfRef.inst 
                                     >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__alu_op = 9U;
            } else if ((4U == (7U & (vlSelfRef.inst 
                                     >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__alu_op = 2U;
            } else if ((6U == (7U & (vlSelfRef.inst 
                                     >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__alu_op = 1U;
            } else if ((7U == (7U & (vlSelfRef.inst 
                                     >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__alu_op = 0U;
            } else if ((1U == (7U & (vlSelfRef.inst 
                                     >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__alu_op = 5U;
            }
            vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr 
                = (0x1fU & (vlSelfRef.inst >> 0xfU));
            vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr 
                = (0x1fU & (vlSelfRef.inst >> 0x14U));
            vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 0U;
        } else {
            if ((0x13U == (0x7fU & vlSelfRef.inst))) {
                vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
                vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                    = (0x1fU & (vlSelfRef.inst >> 7U));
                if ((0U == (7U & (vlSelfRef.inst >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
                } else if ((4U == (7U & (vlSelfRef.inst 
                                         >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 2U;
                } else if ((3U == (7U & (vlSelfRef.inst 
                                         >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 9U;
                } else if ((7U == (7U & (vlSelfRef.inst 
                                         >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 0U;
                } else if ((1U == (7U & (vlSelfRef.inst 
                                         >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 5U;
                } else if ((5U == (7U & (vlSelfRef.inst 
                                         >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__alu_op 
                        = ((0U == (vlSelfRef.inst >> 0x19U))
                            ? 6U : 7U);
                }
                vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr 
                    = (0x1fU & (vlSelfRef.inst >> 0xfU));
                vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 1U;
            } else if ((0x67U == (0x7fU & vlSelfRef.inst))) {
                vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
                vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                    = (0x1fU & (vlSelfRef.inst >> 7U));
                vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
                vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr 
                    = (0x1fU & (vlSelfRef.inst >> 0xfU));
                vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 2U;
            } else {
                if ((0x63U != (0x7fU & vlSelfRef.inst))) {
                    vlSelfRef.ysyx_25020059_top__DOT__reg_wen 
                        = ((0x6fU == (0x7fU & vlSelfRef.inst)) 
                           || ((0x37U == (0x7fU & vlSelfRef.inst)) 
                               || (0x17U == (0x7fU 
                                             & vlSelfRef.inst))));
                    if ((0x6fU == (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                            = (0x1fU & (vlSelfRef.inst 
                                        >> 7U));
                    } else if ((0x37U == (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                            = (0x1fU & (vlSelfRef.inst 
                                        >> 7U));
                    } else if ((0x17U == (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                            = (0x1fU & (vlSelfRef.inst 
                                        >> 7U));
                    }
                }
                if ((0x63U == (0x7fU & vlSelfRef.inst))) {
                    if ((0U == (7U & (vlSelfRef.inst 
                                      >> 0xcU)))) {
                        vlSelfRef.ysyx_25020059_top__DOT__alu_op = 4U;
                    } else if ((1U == (7U & (vlSelfRef.inst 
                                             >> 0xcU)))) {
                        vlSelfRef.ysyx_25020059_top__DOT__alu_op = 4U;
                    } else if ((4U == (7U & (vlSelfRef.inst 
                                             >> 0xcU)))) {
                        vlSelfRef.ysyx_25020059_top__DOT__alu_op = 0xaU;
                    } else if ((6U == (7U & (vlSelfRef.inst 
                                             >> 0xcU)))) {
                        vlSelfRef.ysyx_25020059_top__DOT__alu_op = 0xbU;
                    } else if ((5U == (7U & (vlSelfRef.inst 
                                             >> 0xcU)))) {
                        vlSelfRef.ysyx_25020059_top__DOT__alu_op = 0xaU;
                    } else if ((7U == (7U & (vlSelfRef.inst 
                                             >> 0xcU)))) {
                        vlSelfRef.ysyx_25020059_top__DOT__alu_op = 0xbU;
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
                if ((0x67U != (0x7fU & vlSelfRef.inst))) {
                    if ((0x63U != (0x7fU & vlSelfRef.inst))) {
                        if ((0x6fU != (0x7fU & vlSelfRef.inst))) {
                            if ((0x37U != (0x7fU & vlSelfRef.inst))) {
                                if ((0x17U != (0x7fU 
                                               & vlSelfRef.inst))) {
                                    if ((0U == (7U 
                                                & (vlSelfRef.inst 
                                                   >> 0xcU)))) {
                                        vlSelfRef.ysyx_25020059_top__DOT__mem_size = 0U;
                                    } else if ((1U 
                                                == 
                                                (7U 
                                                 & (vlSelfRef.inst 
                                                    >> 0xcU)))) {
                                        vlSelfRef.ysyx_25020059_top__DOT__mem_size = 1U;
                                    } else if ((2U 
                                                == 
                                                (7U 
                                                 & (vlSelfRef.inst 
                                                    >> 0xcU)))) {
                                        vlSelfRef.ysyx_25020059_top__DOT__mem_size = 2U;
                                    }
                                    vlSelfRef.ysyx_25020059_top__DOT__mem_wen = 1U;
                                    vlSelfRef.ysyx_25020059_top__DOT__mem_valid = 1U;
                                }
                            }
                        }
                        if ((0x6fU == (0x7fU & vlSelfRef.inst))) {
                            vlSelfRef.ysyx_25020059_top__DOT__jal_jump = 1U;
                        }
                    }
                    if ((0x63U == (0x7fU & vlSelfRef.inst))) {
                        if ((0U != (7U & (vlSelfRef.inst 
                                          >> 0xcU)))) {
                            if ((1U != (7U & (vlSelfRef.inst 
                                              >> 0xcU)))) {
                                if ((4U != (7U & (vlSelfRef.inst 
                                                  >> 0xcU)))) {
                                    if ((6U != (7U 
                                                & (vlSelfRef.inst 
                                                   >> 0xcU)))) {
                                        if ((5U == 
                                             (7U & 
                                              (vlSelfRef.inst 
                                               >> 0xcU)))) {
                                            vlSelfRef.ysyx_25020059_top__DOT__bge_branch = 1U;
                                        }
                                        if ((5U != 
                                             (7U & 
                                              (vlSelfRef.inst 
                                               >> 0xcU)))) {
                                            if ((7U 
                                                 == 
                                                 (7U 
                                                  & (vlSelfRef.inst 
                                                     >> 0xcU)))) {
                                                vlSelfRef.ysyx_25020059_top__DOT__bgeu_branch = 1U;
                                            }
                                        }
                                    }
                                    if ((6U == (7U 
                                                & (vlSelfRef.inst 
                                                   >> 0xcU)))) {
                                        vlSelfRef.ysyx_25020059_top__DOT__bltu_branch = 1U;
                                    }
                                }
                                if ((4U == (7U & (vlSelfRef.inst 
                                                  >> 0xcU)))) {
                                    vlSelfRef.ysyx_25020059_top__DOT__blt_branch = 1U;
                                }
                            }
                            if ((1U == (7U & (vlSelfRef.inst 
                                              >> 0xcU)))) {
                                vlSelfRef.ysyx_25020059_top__DOT__bne_branch = 1U;
                            }
                        }
                        if ((0U == (7U & (vlSelfRef.inst 
                                          >> 0xcU)))) {
                            vlSelfRef.ysyx_25020059_top__DOT__beq_branch = 1U;
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
                if ((0x67U == (0x7fU & vlSelfRef.inst))) {
                    vlSelfRef.ysyx_25020059_top__DOT__jalr_jump = 1U;
                }
            }
        }
    } else if ((3U == (0x7fU & vlSelfRef.inst))) {
        vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
        vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
            = (0x1fU & (vlSelfRef.inst >> 7U));
        if ((0U == (7U & (vlSelfRef.inst >> 0xcU)))) {
            vlSelfRef.ysyx_25020059_top__DOT__mem_size = 0U;
            vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
        } else if ((1U == (7U & (vlSelfRef.inst >> 0xcU)))) {
            vlSelfRef.ysyx_25020059_top__DOT__mem_size = 1U;
            vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
        } else if ((2U == (7U & (vlSelfRef.inst >> 0xcU)))) {
            vlSelfRef.ysyx_25020059_top__DOT__mem_size = 2U;
            vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
        } else if ((4U == (7U & (vlSelfRef.inst >> 0xcU)))) {
            vlSelfRef.ysyx_25020059_top__DOT__mem_size = 0U;
            vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
        } else if ((5U == (7U & (vlSelfRef.inst >> 0xcU)))) {
            vlSelfRef.ysyx_25020059_top__DOT__mem_size = 1U;
            vlSelfRef.ysyx_25020059_top__DOT__alu_op = 3U;
        }
        vlSelfRef.ysyx_25020059_top__DOT__mem_wen = 0U;
        vlSelfRef.ysyx_25020059_top__DOT__mem_valid = 1U;
        vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr 
            = (0x1fU & (vlSelfRef.inst >> 0xfU));
        vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 1U;
        vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op = 0U;
    }
    vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata = 
        ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr))
          ? 0U : vlSelfRef.reg_f[vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr]);
    vlSelfRef.ysyx_25020059_top__DOT__reg2_rdata = 
        ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr))
          ? 0U : vlSelfRef.reg_f[vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr]);
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
    if (((((((((3U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op)) 
               | (4U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) 
              | (8U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) 
             | (9U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) 
            | (0xaU == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) 
           | (0xbU == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) 
          | (0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) 
         | (1U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op)))) {
        if ((3U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
            vlSelfRef.ysyx_25020059_top__DOT__alu_res 
                = (vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
                   + vlSelfRef.ysyx_25020059_top__DOT__alu_src2);
        } else if ((4U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
            vlSelfRef.ysyx_25020059_top__DOT__alu_res 
                = (vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
                   - vlSelfRef.ysyx_25020059_top__DOT__alu_src2);
            vlSelfRef.ysyx_25020059_top__DOT__zero 
                = (0U == vlSelfRef.ysyx_25020059_top__DOT__alu_res);
        } else if ((8U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
            vlSelfRef.ysyx_25020059_top__DOT__alu_res 
                = (VL_LTS_III(32, vlSelfRef.ysyx_25020059_top__DOT__alu_src1, vlSelfRef.ysyx_25020059_top__DOT__alu_src2)
                    ? 1U : 0U);
        } else if ((9U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
            vlSelfRef.ysyx_25020059_top__DOT__alu_res 
                = ((vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
                    < vlSelfRef.ysyx_25020059_top__DOT__alu_src2)
                    ? 1U : 0U);
        } else if ((0xaU == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
            vlSelfRef.ysyx_25020059_top__DOT__alu_res 
                = (VL_LTS_III(32, vlSelfRef.ysyx_25020059_top__DOT__alu_src1, vlSelfRef.ysyx_25020059_top__DOT__alu_src2)
                    ? 1U : 0U);
            vlSelfRef.ysyx_25020059_top__DOT__zero 
                = (1U & (~ vlSelfRef.ysyx_25020059_top__DOT__alu_res));
        } else if ((0xbU == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
            vlSelfRef.ysyx_25020059_top__DOT__alu_res 
                = ((vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
                    < vlSelfRef.ysyx_25020059_top__DOT__alu_src2)
                    ? 1U : 0U);
            vlSelfRef.ysyx_25020059_top__DOT__zero 
                = (1U & (~ vlSelfRef.ysyx_25020059_top__DOT__alu_res));
        } else {
            vlSelfRef.ysyx_25020059_top__DOT__alu_res 
                = ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))
                    ? (vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
                       & vlSelfRef.ysyx_25020059_top__DOT__alu_src2)
                    : (vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
                       | vlSelfRef.ysyx_25020059_top__DOT__alu_src2));
        }
    } else if ((2U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__alu_res = 
            (vlSelfRef.ysyx_25020059_top__DOT__alu_src1 
             ^ vlSelfRef.ysyx_25020059_top__DOT__alu_src2);
    } else if ((5U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__alu_res = 
            VL_SHIFTL_III(32,32,32, vlSelfRef.ysyx_25020059_top__DOT__alu_src1, vlSelfRef.ysyx_25020059_top__DOT__alu_src2);
    } else if ((6U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__alu_res = 
            VL_SHIFTR_III(32,32,32, vlSelfRef.ysyx_25020059_top__DOT__alu_src1, vlSelfRef.ysyx_25020059_top__DOT__alu_src2);
    } else if ((7U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__alu_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__alu_res = 
            VL_SHIFTRS_III(32,32,32, vlSelfRef.ysyx_25020059_top__DOT__alu_src1, vlSelfRef.ysyx_25020059_top__DOT__alu_src2);
    }
    if (vlSelfRef.ysyx_25020059_top__DOT__mem_valid) {
        Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_read_TOP____024unit(vlSelfRef.ysyx_25020059_top__DOT__alu_res, 2U, vlSelfRef.__Vfunc_pmem_read__2__Vfuncout);
        vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw 
            = vlSelfRef.__Vfunc_pmem_read__2__Vfuncout;
        if (vlSelfRef.ysyx_25020059_top__DOT__mem_wen) {
            vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__write_data 
                = vlSelfRef.ysyx_25020059_top__DOT__reg2_rdata;
            if ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))) {
                vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__write_data 
                    = VL_SHIFTL_III(32,32,32, vlSelfRef.ysyx_25020059_top__DOT__reg2_rdata, 
                                    VL_SHIFTL_III(32,32,32, 
                                                  (3U 
                                                   & vlSelfRef.ysyx_25020059_top__DOT__alu_res), 3U));
            } else if ((1U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))) {
                vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__write_data 
                    = VL_SHIFTL_III(32,32,32, (0xffffU 
                                               & vlSelfRef.ysyx_25020059_top__DOT__reg2_rdata), 
                                    VL_SHIFTL_III(32,32,32, 
                                                  (3U 
                                                   & vlSelfRef.ysyx_25020059_top__DOT__alu_res), 3U));
            }
            Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_write_TOP____024unit(vlSelfRef.ysyx_25020059_top__DOT__alu_res, vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__write_data, 
                                                                                (0xfU 
                                                                                & ((0U 
                                                                                == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                                                                                 ? 
                                                                                ((IData)(1U) 
                                                                                << 
                                                                                (3U 
                                                                                & vlSelfRef.ysyx_25020059_top__DOT__alu_res))
                                                                                 : 
                                                                                ((1U 
                                                                                == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                                                                                 ? 
                                                                                ((IData)(3U) 
                                                                                << 
                                                                                (3U 
                                                                                & vlSelfRef.ysyx_25020059_top__DOT__alu_res))
                                                                                 : 
                                                                                ((2U 
                                                                                == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                                                                                 ? 0xfU
                                                                                 : 0U)))));
        }
        if ((1U & (~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_wen)))) {
            vlSelfRef.ysyx_25020059_top__DOT__mem_rdata 
                = ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                    ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                        ? (0xffU & vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw)
                        : (((- (IData)((1U & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw 
                                              >> 7U)))) 
                            << 8U) | (0xffU & vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw)))
                    : ((1U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                        ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                            ? (0xffffU & vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw)
                            : (((- (IData)((1U & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw 
                                                  >> 0xfU)))) 
                                << 0x10U) | (0xffffU 
                                             & vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw)))
                        : ((2U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                            ? vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw
                            : 0U)));
        }
    } else {
        vlSelfRef.ysyx_25020059_top__DOT__mem_rdata = 0U;
    }
    vlSelfRef.next_pc = ((IData)(vlSelfRef.ysyx_25020059_top__DOT__ena)
                          ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__jal_jump)
                              ? (vlSelfRef.curr_pc 
                                 + vlSelfRef.ysyx_25020059_top__DOT__imm)
                              : ((IData)(vlSelfRef.ysyx_25020059_top__DOT__jalr_jump)
                                  ? (0xfffffffeU & 
                                     (vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata 
                                      + vlSelfRef.ysyx_25020059_top__DOT__imm))
                                  : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__beq_branch) 
                                      & (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero))
                                      ? (vlSelfRef.curr_pc 
                                         + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                      : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__bne_branch) 
                                          & (~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero)))
                                          ? (vlSelfRef.curr_pc 
                                             + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                          : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__blt_branch) 
                                              & (~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero)))
                                              ? (vlSelfRef.curr_pc 
                                                 + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                              : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__bltu_branch) 
                                                  & (~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero)))
                                                  ? 
                                                 (vlSelfRef.curr_pc 
                                                  + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                                  : 
                                                 (((IData)(vlSelfRef.ysyx_25020059_top__DOT__bge_branch) 
                                                   & (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero))
                                                   ? 
                                                  (vlSelfRef.curr_pc 
                                                   + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                                   : 
                                                  (((IData)(vlSelfRef.ysyx_25020059_top__DOT__bgeu_branch) 
                                                    & (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero))
                                                    ? 
                                                   (vlSelfRef.curr_pc 
                                                    + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                                    : 
                                                   ((IData)(4U) 
                                                    + vlSelfRef.curr_pc)))))))))
                          : vlSelfRef.curr_pc);
}

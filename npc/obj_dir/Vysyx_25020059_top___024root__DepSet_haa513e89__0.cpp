// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vysyx_25020059_top.h for the primary calling header

#include "Vysyx_25020059_top__pch.h"
#include "Vysyx_25020059_top__Syms.h"
#include "Vysyx_25020059_top___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_25020059_top___024root___dump_triggers__ico(Vysyx_25020059_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vysyx_25020059_top___024root___eval_triggers__ico(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_triggers__ico\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered.set(0U, (IData)(vlSelfRef.__VicoFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vysyx_25020059_top___024root___dump_triggers__ico(vlSelf);
    }
#endif
}

void Vysyx_25020059_top___024unit____Vdpiimwrap_npc_trap_TOP____024unit(IData/*31:0*/ code);
void Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_read_TOP____024unit(IData/*31:0*/ raddr, IData/*31:0*/ i, IData/*31:0*/ &pmem_read__Vfuncrtn);
void Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_write_TOP____024unit(IData/*31:0*/ waddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask);

VL_INLINE_OPT void Vysyx_25020059_top___024root___ico_sequent__TOP__0(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___ico_sequent__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((IData)((0x100073U == (0xfff0707fU & vlSelfRef.inst)))) {
        Vysyx_25020059_top___024unit____Vdpiimwrap_npc_trap_TOP____024unit(
                                                                           vlSelfRef.reg_f
                                                                           [0xaU]);
    }
    vlSelfRef.ysyx_25020059_top__DOT__rst_n = (1U & 
                                               (~ (IData)(vlSelfRef.rst)));
    vlSelfRef.ysyx_25020059_top__DOT__reg_waddr = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__jalr_jump = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__jal_jump = 0U;
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
    vlSelfRef.ysyx_25020059_top__DOT__mem_valid = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__mem_wen = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__mem_size = 0U;
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
                    } else if ((0x37U == (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                            = (0x1fU & (vlSelfRef.inst 
                                        >> 7U));
                    } else if ((0x17U == (0x7fU & vlSelfRef.inst))) {
                        vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                            = (0x1fU & (vlSelfRef.inst 
                                        >> 7U));
                    }
                    vlSelfRef.ysyx_25020059_top__DOT__reg_wen 
                        = ((0x6fU == (0x7fU & vlSelfRef.inst)) 
                           || ((0x37U == (0x7fU & vlSelfRef.inst)) 
                               || (0x17U == (0x7fU 
                                             & vlSelfRef.inst))));
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
                    if ((0x63U != (0x7fU & vlSelfRef.inst))) {
                        if ((0x6fU == (0x7fU & vlSelfRef.inst))) {
                            vlSelfRef.ysyx_25020059_top__DOT__jal_jump = 1U;
                        }
                        if ((0x6fU != (0x7fU & vlSelfRef.inst))) {
                            if ((0x37U != (0x7fU & vlSelfRef.inst))) {
                                if ((0x17U != (0x7fU 
                                               & vlSelfRef.inst))) {
                                    vlSelfRef.ysyx_25020059_top__DOT__mem_valid = 1U;
                                    vlSelfRef.ysyx_25020059_top__DOT__mem_wen = 1U;
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
                                }
                            }
                        }
                    }
                }
            }
        }
    } else if ((3U == (0x7fU & vlSelfRef.inst))) {
        vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
            = (0x1fU & (vlSelfRef.inst >> 7U));
        vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
        vlSelfRef.ysyx_25020059_top__DOT__mem_valid = 1U;
        vlSelfRef.ysyx_25020059_top__DOT__mem_wen = 0U;
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
    if (vlSelfRef.ysyx_25020059_top__DOT__mem_valid) {
        Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_read_TOP____024unit(
                                                                            (0xfffffffcU 
                                                                             & vlSelfRef.ysyx_25020059_top__DOT__alu_res), 2U, vlSelfRef.__Vfunc_pmem_read__1__Vfuncout);
        vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
            = vlSelfRef.__Vfunc_pmem_read__1__Vfuncout;
        vlSelfRef.ysyx_25020059_top__DOT__mem_rdata 
            = ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                ? ((2U & vlSelfRef.ysyx_25020059_top__DOT__alu_res)
                    ? ((1U & vlSelfRef.ysyx_25020059_top__DOT__alu_res)
                        ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                            ? (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                               >> 0x18U) : (((- (IData)(
                                                        (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                         >> 0x1fU))) 
                                             << 8U) 
                                            | (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                               >> 0x18U)))
                        : ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                            ? (0xffU & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                        >> 0x10U)) : 
                           (((- (IData)((1U & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                               >> 0x17U)))) 
                             << 8U) | (0xffU & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                >> 0x10U)))))
                    : ((1U & vlSelfRef.ysyx_25020059_top__DOT__alu_res)
                        ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                            ? (0xffU & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                        >> 8U)) : (
                                                   ((- (IData)(
                                                               (1U 
                                                                & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                                   >> 0xfU)))) 
                                                    << 8U) 
                                                   | (0xffU 
                                                      & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                         >> 8U))))
                        : ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                            ? (0xffU & vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data)
                            : (((- (IData)((1U & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                  >> 7U)))) 
                                << 8U) | (0xffU & vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data)))))
                : ((1U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                    ? ((2U & vlSelfRef.ysyx_25020059_top__DOT__alu_res)
                        ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                            ? (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                               >> 0x10U) : (((- (IData)(
                                                        (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                         >> 0x1fU))) 
                                             << 0x10U) 
                                            | (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                               >> 0x10U)))
                        : ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                            ? (0xffffU & vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data)
                            : (((- (IData)((1U & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                  >> 0xfU)))) 
                                << 0x10U) | (0xffffU 
                                             & vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data))))
                    : ((2U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                        ? vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data
                        : 0U)));
        if (vlSelfRef.ysyx_25020059_top__DOT__mem_wen) {
            Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_write_TOP____024unit(vlSelfRef.ysyx_25020059_top__DOT__alu_res, vlSelfRef.ysyx_25020059_top__DOT__reg2_rdata, 
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
    } else {
        vlSelfRef.ysyx_25020059_top__DOT__mem_rdata = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vysyx_25020059_top___024root___dump_triggers__act(Vysyx_25020059_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vysyx_25020059_top___024root___eval_triggers__act(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___eval_triggers__act\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered.set(0U, ((IData)(vlSelfRef.clk) 
                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0))));
    vlSelfRef.__VactTriggered.set(1U, ((~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__rst_n)) 
                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__ysyx_25020059_top__DOT__rst_n__0)));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
    vlSelfRef.__Vtrigprevexpr___TOP__ysyx_25020059_top__DOT__rst_n__0 
        = vlSelfRef.ysyx_25020059_top__DOT__rst_n;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vysyx_25020059_top___024root___dump_triggers__act(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vysyx_25020059_top___024root___nba_sequent__TOP__0(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___nba_sequent__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VdlyVal__reg_f__v0;
    __VdlyVal__reg_f__v0 = 0;
    CData/*4:0*/ __VdlyDim0__reg_f__v0;
    __VdlyDim0__reg_f__v0 = 0;
    CData/*0:0*/ __VdlySet__reg_f__v0;
    __VdlySet__reg_f__v0 = 0;
    CData/*4:0*/ __VdlyDim0__reg_f__v1;
    __VdlyDim0__reg_f__v1 = 0;
    CData/*0:0*/ __VdlySet__reg_f__v1;
    __VdlySet__reg_f__v1 = 0;
    // Body
    __VdlySet__reg_f__v0 = 0U;
    __VdlySet__reg_f__v1 = 0U;
    if (vlSelfRef.ysyx_25020059_top__DOT__rst_n) {
        if (((IData)(vlSelfRef.ysyx_25020059_top__DOT__reg_wen) 
             & (0U != (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg_waddr)))) {
            __VdlyVal__reg_f__v0 = (((~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_wen)) 
                                     & (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_valid))
                                     ? vlSelfRef.ysyx_25020059_top__DOT__mem_rdata
                                     : vlSelfRef.ysyx_25020059_top__DOT__alu_res);
            __VdlyDim0__reg_f__v0 = vlSelfRef.ysyx_25020059_top__DOT__reg_waddr;
            __VdlySet__reg_f__v0 = 1U;
        }
        vlSelfRef.curr_pc = vlSelfRef.next_pc;
        vlSelfRef.ysyx_25020059_top__DOT__ena = 1U;
    } else {
        __VdlyDim0__reg_f__v1 = vlSelfRef.ysyx_25020059_top__DOT__reg_waddr;
        __VdlySet__reg_f__v1 = 1U;
        vlSelfRef.curr_pc = 0x80000000U;
        vlSelfRef.ysyx_25020059_top__DOT__ena = 0U;
    }
    if (__VdlySet__reg_f__v0) {
        vlSelfRef.reg_f[__VdlyDim0__reg_f__v0] = __VdlyVal__reg_f__v0;
    }
    if (__VdlySet__reg_f__v1) {
        vlSelfRef.reg_f[__VdlyDim0__reg_f__v1] = 0U;
    }
    if ((IData)((0x100073U == (0xfff0707fU & vlSelfRef.inst)))) {
        Vysyx_25020059_top___024unit____Vdpiimwrap_npc_trap_TOP____024unit(
                                                                           vlSelfRef.reg_f
                                                                           [0xaU]);
    }
    vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata = 
        ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr))
          ? 0U : vlSelfRef.reg_f[vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr]);
    vlSelfRef.ysyx_25020059_top__DOT__reg2_rdata = 
        ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr))
          ? 0U : vlSelfRef.reg_f[vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr]);
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
    if (vlSelfRef.ysyx_25020059_top__DOT__mem_valid) {
        Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_read_TOP____024unit(
                                                                            (0xfffffffcU 
                                                                             & vlSelfRef.ysyx_25020059_top__DOT__alu_res), 2U, vlSelfRef.__Vfunc_pmem_read__1__Vfuncout);
        vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
            = vlSelfRef.__Vfunc_pmem_read__1__Vfuncout;
        vlSelfRef.ysyx_25020059_top__DOT__mem_rdata 
            = ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                ? ((2U & vlSelfRef.ysyx_25020059_top__DOT__alu_res)
                    ? ((1U & vlSelfRef.ysyx_25020059_top__DOT__alu_res)
                        ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                            ? (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                               >> 0x18U) : (((- (IData)(
                                                        (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                         >> 0x1fU))) 
                                             << 8U) 
                                            | (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                               >> 0x18U)))
                        : ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                            ? (0xffU & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                        >> 0x10U)) : 
                           (((- (IData)((1U & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                               >> 0x17U)))) 
                             << 8U) | (0xffU & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                >> 0x10U)))))
                    : ((1U & vlSelfRef.ysyx_25020059_top__DOT__alu_res)
                        ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                            ? (0xffU & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                        >> 8U)) : (
                                                   ((- (IData)(
                                                               (1U 
                                                                & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                                   >> 0xfU)))) 
                                                    << 8U) 
                                                   | (0xffU 
                                                      & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                         >> 8U))))
                        : ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                            ? (0xffU & vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data)
                            : (((- (IData)((1U & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                  >> 7U)))) 
                                << 8U) | (0xffU & vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data)))))
                : ((1U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                    ? ((2U & vlSelfRef.ysyx_25020059_top__DOT__alu_res)
                        ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                            ? (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                               >> 0x10U) : (((- (IData)(
                                                        (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                         >> 0x1fU))) 
                                             << 0x10U) 
                                            | (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                               >> 0x10U)))
                        : ((IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned)
                            ? (0xffffU & vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data)
                            : (((- (IData)((1U & (vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data 
                                                  >> 0xfU)))) 
                                << 0x10U) | (0xffffU 
                                             & vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data))))
                    : ((2U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                        ? vlSelfRef.ysyx_25020059_top__DOT__u_mem_if_0__DOT__raw_data
                        : 0U)));
        if (vlSelfRef.ysyx_25020059_top__DOT__mem_wen) {
            Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_write_TOP____024unit(vlSelfRef.ysyx_25020059_top__DOT__alu_res, vlSelfRef.ysyx_25020059_top__DOT__reg2_rdata, 
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
    } else {
        vlSelfRef.ysyx_25020059_top__DOT__mem_rdata = 0U;
    }
}

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

void Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_read_TOP____024unit(IData/*31:0*/ raddr, IData/*31:0*/ i, IData/*31:0*/ &pmem_read__Vfuncrtn);
void Vysyx_25020059_top___024unit____Vdpiimwrap_npc_trap_TOP____024unit(IData/*31:0*/ code);
void Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_write_TOP____024unit(IData/*31:0*/ waddr, IData/*31:0*/ wdata, CData/*7:0*/ wmask);

VL_INLINE_OPT void Vysyx_25020059_top___024root___nba_sequent__TOP__0(Vysyx_25020059_top___024root* vlSelf) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root___nba_sequent__TOP__0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __Vfunc_pmem_read__0__Vfuncout;
    __Vfunc_pmem_read__0__Vfuncout = 0;
    IData/*31:0*/ __Vdly__ysyx_25020059_top__DOT__csr_mepc;
    __Vdly__ysyx_25020059_top__DOT__csr_mepc = 0;
    IData/*31:0*/ __Vdly__ysyx_25020059_top__DOT__csr_mtvec;
    __Vdly__ysyx_25020059_top__DOT__csr_mtvec = 0;
    IData/*31:0*/ __Vdly__ysyx_25020059_top__DOT__csr_mstatus;
    __Vdly__ysyx_25020059_top__DOT__csr_mstatus = 0;
    IData/*31:0*/ __Vdly__ysyx_25020059_top__DOT__csr_mcause;
    __Vdly__ysyx_25020059_top__DOT__csr_mcause = 0;
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
    __Vdly__ysyx_25020059_top__DOT__csr_mcause = vlSelfRef.ysyx_25020059_top__DOT__csr_mcause;
    __Vdly__ysyx_25020059_top__DOT__csr_mtvec = vlSelfRef.ysyx_25020059_top__DOT__csr_mtvec;
    __Vdly__ysyx_25020059_top__DOT__csr_mstatus = vlSelfRef.ysyx_25020059_top__DOT__csr_mstatus;
    __VdlySet__reg_f__v0 = 0U;
    __VdlySet__reg_f__v1 = 0U;
    __Vdly__ysyx_25020059_top__DOT__csr_mepc = vlSelfRef.ysyx_25020059_top__DOT__csr_mepc;
    if (vlSelfRef.ysyx_25020059_top__DOT__rst_n) {
        if (vlSelfRef.ysyx_25020059_top__DOT__csr_write) {
            if ((0x300U != (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_addr))) {
                if ((0x305U != (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_addr))) {
                    if ((0x341U != (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_addr))) {
                        if ((0x342U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_addr))) {
                            if ((1U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_op))) {
                                __Vdly__ysyx_25020059_top__DOT__csr_mcause 
                                    = vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata;
                            } else if ((2U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_op))) {
                                __Vdly__ysyx_25020059_top__DOT__csr_mcause 
                                    = (vlSelfRef.ysyx_25020059_top__DOT__csr_mcause 
                                       | vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata);
                            }
                        }
                    }
                }
                if ((0x305U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_addr))) {
                    if ((1U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_op))) {
                        __Vdly__ysyx_25020059_top__DOT__csr_mtvec 
                            = vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata;
                    } else if ((2U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_op))) {
                        __Vdly__ysyx_25020059_top__DOT__csr_mtvec 
                            = (vlSelfRef.ysyx_25020059_top__DOT__csr_mtvec 
                               | vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata);
                    }
                }
            }
            if ((0x300U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_addr))) {
                if ((1U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_op))) {
                    __Vdly__ysyx_25020059_top__DOT__csr_mstatus 
                        = vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata;
                } else if ((2U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_op))) {
                    __Vdly__ysyx_25020059_top__DOT__csr_mstatus 
                        = (vlSelfRef.ysyx_25020059_top__DOT__csr_mstatus 
                           | vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata);
                }
            }
        }
        if (vlSelfRef.ysyx_25020059_top__DOT__csr_ecall) {
            __Vdly__ysyx_25020059_top__DOT__csr_mcause = 0xbU;
            __Vdly__ysyx_25020059_top__DOT__csr_mstatus = 0x1800U;
        }
        if (vlSelfRef.ysyx_25020059_top__DOT__csr_mret) {
            __Vdly__ysyx_25020059_top__DOT__csr_mstatus 
                = (0xffffe7ffU & (0x80U | ((0xfffffff7U 
                                            & vlSelfRef.ysyx_25020059_top__DOT__csr_mstatus) 
                                           | (8U & 
                                              VL_SHIFTR_III(32,32,32, vlSelfRef.ysyx_25020059_top__DOT__csr_mstatus, 4U)))));
        }
        if (((IData)(vlSelfRef.ysyx_25020059_top__DOT__reg_wen) 
             & (0U != (IData)(vlSelfRef.ysyx_25020059_top__DOT__reg_waddr)))) {
            __VdlyVal__reg_f__v0 = ((IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_read)
                                     ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_read)
                                         ? ((0x300U 
                                             == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_addr))
                                             ? vlSelfRef.ysyx_25020059_top__DOT__csr_mstatus
                                             : ((0x305U 
                                                 == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_addr))
                                                 ? vlSelfRef.ysyx_25020059_top__DOT__csr_mtvec
                                                 : 
                                                ((0x341U 
                                                  == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_addr))
                                                  ? vlSelfRef.ysyx_25020059_top__DOT__csr_mepc
                                                  : 
                                                 ((0x342U 
                                                   == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_addr))
                                                   ? vlSelfRef.ysyx_25020059_top__DOT__csr_mcause
                                                   : 0U))))
                                         : 0U) : ((
                                                   (~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_wen)) 
                                                   & (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_valid))
                                                   ? vlSelfRef.ysyx_25020059_top__DOT__mem_rdata
                                                   : vlSelfRef.ysyx_25020059_top__DOT__alu_res));
            __VdlyDim0__reg_f__v0 = vlSelfRef.ysyx_25020059_top__DOT__reg_waddr;
            __VdlySet__reg_f__v0 = 1U;
        }
    } else {
        __Vdly__ysyx_25020059_top__DOT__csr_mcause = 0U;
        __Vdly__ysyx_25020059_top__DOT__csr_mtvec = 0x80000000U;
        __Vdly__ysyx_25020059_top__DOT__csr_mstatus = 0U;
        __VdlyDim0__reg_f__v1 = vlSelfRef.ysyx_25020059_top__DOT__reg_waddr;
        __VdlySet__reg_f__v1 = 1U;
    }
    vlSelfRef.ysyx_25020059_top__DOT__csr_mstatus = __Vdly__ysyx_25020059_top__DOT__csr_mstatus;
    vlSelfRef.ysyx_25020059_top__DOT__csr_mcause = __Vdly__ysyx_25020059_top__DOT__csr_mcause;
    vlSelfRef.ysyx_25020059_top__DOT__csr_mtvec = __Vdly__ysyx_25020059_top__DOT__csr_mtvec;
    if (__VdlySet__reg_f__v0) {
        vlSelfRef.reg_f[__VdlyDim0__reg_f__v0] = __VdlyVal__reg_f__v0;
    }
    if (__VdlySet__reg_f__v1) {
        vlSelfRef.reg_f[__VdlyDim0__reg_f__v1] = 0U;
    }
    if (vlSelfRef.ysyx_25020059_top__DOT__rst_n) {
        if (vlSelfRef.ysyx_25020059_top__DOT__csr_write) {
            if ((0x300U != (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_addr))) {
                if ((0x305U != (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_addr))) {
                    if ((0x341U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_addr))) {
                        if ((1U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_op))) {
                            __Vdly__ysyx_25020059_top__DOT__csr_mepc 
                                = vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata;
                        } else if ((2U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_op))) {
                            __Vdly__ysyx_25020059_top__DOT__csr_mepc 
                                = (vlSelfRef.ysyx_25020059_top__DOT__csr_mepc 
                                   | vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata);
                        }
                    }
                }
            }
        }
        if (vlSelfRef.ysyx_25020059_top__DOT__csr_ecall) {
            __Vdly__ysyx_25020059_top__DOT__csr_mepc 
                = vlSelfRef.curr_pc;
        }
    } else {
        __Vdly__ysyx_25020059_top__DOT__csr_mepc = 0U;
    }
    vlSelfRef.ysyx_25020059_top__DOT__csr_mepc = __Vdly__ysyx_25020059_top__DOT__csr_mepc;
    vlSelfRef.o_mstatus = vlSelfRef.ysyx_25020059_top__DOT__csr_mstatus;
    vlSelfRef.o_mcause = vlSelfRef.ysyx_25020059_top__DOT__csr_mcause;
    vlSelfRef.o_mtvec = vlSelfRef.ysyx_25020059_top__DOT__csr_mtvec;
    vlSelfRef.o_mepc = vlSelfRef.ysyx_25020059_top__DOT__csr_mepc;
    if (vlSelfRef.ysyx_25020059_top__DOT__rst_n) {
        Vysyx_25020059_top___024unit____Vdpiimwrap_pmem_read_TOP____024unit(vlSelfRef.ysyx_25020059_top__DOT__u_pc_reg_0__DOT__use_pc, 1U, __Vfunc_pmem_read__0__Vfuncout);
        vlSelfRef.ysyx_25020059_top__DOT__ena = 1U;
        vlSelfRef.inst = __Vfunc_pmem_read__0__Vfuncout;
        vlSelfRef.curr_pc = vlSelfRef.ysyx_25020059_top__DOT__u_pc_reg_0__DOT__use_pc;
    } else {
        vlSelfRef.ysyx_25020059_top__DOT__ena = 0U;
        vlSelfRef.curr_pc = 0x80000000U;
        vlSelfRef.inst = 0U;
    }
    if ((IData)((0x100073U == (0xfff0707fU & vlSelfRef.inst)))) {
        Vysyx_25020059_top___024unit____Vdpiimwrap_npc_trap_TOP____024unit(
                                                                           vlSelfRef.reg_f
                                                                           [0xaU]);
    }
    vlSelfRef.ysyx_25020059_top__DOT__reg_waddr = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__csr_read = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__csr_write = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__csr_addr = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__csr_rs1_addr = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__csr_op = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__csr_mret = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__csr_ecall = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__mem_wen = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__mem_valid = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__mem_size = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned = 0U;
    if ((1U & (~ ((((((((0x33U == (0x7fU & vlSelfRef.inst)) 
                        | (0x13U == (0x7fU & vlSelfRef.inst))) 
                       | (0x67U == (0x7fU & vlSelfRef.inst))) 
                      | (0x63U == (0x7fU & vlSelfRef.inst))) 
                     | (0x6fU == (0x7fU & vlSelfRef.inst))) 
                    | (0x37U == (0x7fU & vlSelfRef.inst))) 
                   | (0x17U == (0x7fU & vlSelfRef.inst))) 
                  | (0x23U == (0x7fU & vlSelfRef.inst)))))) {
        if ((3U != (0x7fU & vlSelfRef.inst))) {
            if ((0x73U == (0x7fU & vlSelfRef.inst))) {
                if ((0U == (7U & (vlSelfRef.inst >> 0xcU)))) {
                    if ((0x302U == (vlSelfRef.inst 
                                    >> 0x14U))) {
                        vlSelfRef.ysyx_25020059_top__DOT__csr_read = 0U;
                        vlSelfRef.ysyx_25020059_top__DOT__csr_write = 0U;
                        vlSelfRef.ysyx_25020059_top__DOT__csr_mret = 1U;
                    } else if ((0U == (vlSelfRef.inst 
                                       >> 0x14U))) {
                        vlSelfRef.ysyx_25020059_top__DOT__csr_read = 0U;
                        vlSelfRef.ysyx_25020059_top__DOT__csr_write = 0U;
                    }
                    if ((0x302U != (vlSelfRef.inst 
                                    >> 0x14U))) {
                        if ((0U == (vlSelfRef.inst 
                                    >> 0x14U))) {
                            vlSelfRef.ysyx_25020059_top__DOT__csr_ecall = 1U;
                        }
                    }
                } else if ((1U == (7U & (vlSelfRef.inst 
                                         >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__csr_read = 1U;
                    vlSelfRef.ysyx_25020059_top__DOT__csr_write = 1U;
                } else if ((2U == (7U & (vlSelfRef.inst 
                                         >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__csr_read = 1U;
                    vlSelfRef.ysyx_25020059_top__DOT__csr_write 
                        = (0U != (0x1fU & (vlSelfRef.inst 
                                           >> 0xfU)));
                }
                vlSelfRef.ysyx_25020059_top__DOT__csr_addr 
                    = (vlSelfRef.inst >> 0x14U);
                if ((0U != (7U & (vlSelfRef.inst >> 0xcU)))) {
                    if ((1U == (7U & (vlSelfRef.inst 
                                      >> 0xcU)))) {
                        vlSelfRef.ysyx_25020059_top__DOT__csr_rs1_addr 
                            = (0x1fU & (vlSelfRef.inst 
                                        >> 0xfU));
                        vlSelfRef.ysyx_25020059_top__DOT__csr_op = 1U;
                    } else if ((2U == (7U & (vlSelfRef.inst 
                                             >> 0xcU)))) {
                        if ((0U != (0x1fU & (vlSelfRef.inst 
                                             >> 0xfU)))) {
                            vlSelfRef.ysyx_25020059_top__DOT__csr_rs1_addr 
                                = (0x1fU & (vlSelfRef.inst 
                                            >> 0xfU));
                        }
                        vlSelfRef.ysyx_25020059_top__DOT__csr_op = 2U;
                    }
                }
            }
        }
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
    vlSelfRef.ysyx_25020059_top__DOT__bltu_branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__jalr_jump = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__jal_jump = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__bgeu_branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__bge_branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__blt_branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__bne_branch = 0U;
    vlSelfRef.ysyx_25020059_top__DOT__beq_branch = 0U;
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
            vlSelfRef.ysyx_25020059_top__DOT__alu_op 
                = ((0x4000U & vlSelfRef.inst) ? ((0x2000U 
                                                  & vlSelfRef.inst)
                                                  ? 
                                                 ((0x1000U 
                                                   & vlSelfRef.inst)
                                                   ? 0U
                                                   : 1U)
                                                  : 
                                                 ((0x1000U 
                                                   & vlSelfRef.inst)
                                                   ? 
                                                  ((0U 
                                                    == 
                                                    (vlSelfRef.inst 
                                                     >> 0x19U))
                                                    ? 6U
                                                    : 7U)
                                                   : 2U))
                    : ((0x2000U & vlSelfRef.inst) ? 
                       ((0x1000U & vlSelfRef.inst) ? 9U
                         : 8U) : ((0x1000U & vlSelfRef.inst)
                                   ? 5U : ((0U == (vlSelfRef.inst 
                                                   >> 0x19U))
                                            ? 3U : 4U))));
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
                } else if ((4U == (7U & (vlSelfRef.inst 
                                         >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 2U;
                } else if ((3U == (7U & (vlSelfRef.inst 
                                         >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 9U;
                } else if ((7U == (7U & (vlSelfRef.inst 
                                         >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 0U;
                } else if ((6U == (7U & (vlSelfRef.inst 
                                         >> 0xcU)))) {
                    vlSelfRef.ysyx_25020059_top__DOT__alu_op = 1U;
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
                if ((0U != (7U & (vlSelfRef.inst >> 0xcU)))) {
                    if ((4U != (7U & (vlSelfRef.inst 
                                      >> 0xcU)))) {
                        if ((3U != (7U & (vlSelfRef.inst 
                                          >> 0xcU)))) {
                            if ((7U != (7U & (vlSelfRef.inst 
                                              >> 0xcU)))) {
                                if ((6U != (7U & (vlSelfRef.inst 
                                                  >> 0xcU)))) {
                                    if ((1U == (7U 
                                                & (vlSelfRef.inst 
                                                   >> 0xcU)))) {
                                        vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 1U;
                                    } else if ((5U 
                                                == 
                                                (7U 
                                                 & (vlSelfRef.inst 
                                                    >> 0xcU)))) {
                                        vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 1U;
                                    }
                                }
                            }
                        }
                    }
                }
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
                                    vlSelfRef.ysyx_25020059_top__DOT__mem_wen = 1U;
                                    vlSelfRef.ysyx_25020059_top__DOT__mem_valid = 1U;
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
                                    if ((6U == (7U 
                                                & (vlSelfRef.inst 
                                                   >> 0xcU)))) {
                                        vlSelfRef.ysyx_25020059_top__DOT__bltu_branch = 1U;
                                    }
                                    if ((6U != (7U 
                                                & (vlSelfRef.inst 
                                                   >> 0xcU)))) {
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
                                        if ((5U == 
                                             (7U & 
                                              (vlSelfRef.inst 
                                               >> 0xcU)))) {
                                            vlSelfRef.ysyx_25020059_top__DOT__bge_branch = 1U;
                                        }
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
                    }
                }
                if ((0x67U == (0x7fU & vlSelfRef.inst))) {
                    vlSelfRef.ysyx_25020059_top__DOT__jalr_jump = 1U;
                }
            }
            if ((0x13U == (0x7fU & vlSelfRef.inst))) {
                if ((0U != (7U & (vlSelfRef.inst >> 0xcU)))) {
                    if ((4U != (7U & (vlSelfRef.inst 
                                      >> 0xcU)))) {
                        if ((3U != (7U & (vlSelfRef.inst 
                                          >> 0xcU)))) {
                            if ((7U != (7U & (vlSelfRef.inst 
                                              >> 0xcU)))) {
                                if ((6U != (7U & (vlSelfRef.inst 
                                                  >> 0xcU)))) {
                                    if ((1U == (7U 
                                                & (vlSelfRef.inst 
                                                   >> 0xcU)))) {
                                        vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op = 5U;
                                    } else if ((5U 
                                                == 
                                                (7U 
                                                 & (vlSelfRef.inst 
                                                    >> 0xcU)))) {
                                        vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op = 5U;
                                    }
                                }
                            }
                        }
                    }
                }
            } else if ((0x67U != (0x7fU & vlSelfRef.inst))) {
                vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op 
                    = ((0x63U == (0x7fU & vlSelfRef.inst))
                        ? 2U : ((0x6fU == (0x7fU & vlSelfRef.inst))
                                 ? 3U : ((0x37U == 
                                          (0x7fU & vlSelfRef.inst))
                                          ? 4U : ((0x17U 
                                                   == 
                                                   (0x7fU 
                                                    & vlSelfRef.inst))
                                                   ? 4U
                                                   : 1U))));
            }
        }
    } else if ((3U == (0x7fU & vlSelfRef.inst))) {
        vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
            = (0x1fU & (vlSelfRef.inst >> 7U));
        vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
        vlSelfRef.ysyx_25020059_top__DOT__mem_wen = 0U;
        vlSelfRef.ysyx_25020059_top__DOT__mem_valid = 1U;
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
    } else if ((0x73U == (0x7fU & vlSelfRef.inst))) {
        if ((0U != (7U & (vlSelfRef.inst >> 0xcU)))) {
            if ((1U == (7U & (vlSelfRef.inst >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                    = (0x1fU & (vlSelfRef.inst >> 7U));
                vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr 
                    = (0x1fU & (vlSelfRef.inst >> 0xfU));
            } else if ((2U == (7U & (vlSelfRef.inst 
                                     >> 0xcU)))) {
                vlSelfRef.ysyx_25020059_top__DOT__reg_waddr 
                    = (0x1fU & (vlSelfRef.inst >> 7U));
                vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr 
                    = (0x1fU & (vlSelfRef.inst >> 0xfU));
            }
        }
        if ((0U == (7U & (vlSelfRef.inst >> 0xcU)))) {
            if ((0x302U == (vlSelfRef.inst >> 0x14U))) {
                vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 0U;
                vlSelfRef.ysyx_25020059_top__DOT__alu_op = 0xfU;
                vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 0U;
            } else if ((0U == (vlSelfRef.inst >> 0x14U))) {
                vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 0U;
                vlSelfRef.ysyx_25020059_top__DOT__alu_op = 0xfU;
                vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel = 0U;
            }
        } else if ((1U == (7U & (vlSelfRef.inst >> 0xcU)))) {
            vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
        } else if ((2U == (7U & (vlSelfRef.inst >> 0xcU)))) {
            vlSelfRef.ysyx_25020059_top__DOT__reg_wen = 1U;
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
    } else if ((5U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op))) {
        vlSelfRef.ysyx_25020059_top__DOT__imm = (0x1fU 
                                                 & (vlSelfRef.inst 
                                                    >> 0x14U));
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
    vlSelfRef.ysyx_25020059_top__DOT__next_pc_from_mux 
        = ((IData)(vlSelfRef.ysyx_25020059_top__DOT__ena)
            ? ((IData)(vlSelfRef.ysyx_25020059_top__DOT__jal_jump)
                ? (vlSelfRef.curr_pc + vlSelfRef.ysyx_25020059_top__DOT__imm)
                : ((IData)(vlSelfRef.ysyx_25020059_top__DOT__jalr_jump)
                    ? (0xfffffffeU & (vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata 
                                      + vlSelfRef.ysyx_25020059_top__DOT__imm))
                    : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__beq_branch) 
                        & (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero))
                        ? (vlSelfRef.curr_pc + vlSelfRef.ysyx_25020059_top__DOT__imm)
                        : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__bne_branch) 
                            & (~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero)))
                            ? (vlSelfRef.curr_pc + vlSelfRef.ysyx_25020059_top__DOT__imm)
                            : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__blt_branch) 
                                & (~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero)))
                                ? (vlSelfRef.curr_pc 
                                   + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__bltu_branch) 
                                    & (~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero)))
                                    ? (vlSelfRef.curr_pc 
                                       + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                    : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__bge_branch) 
                                        & (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero))
                                        ? (vlSelfRef.curr_pc 
                                           + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                        : (((IData)(vlSelfRef.ysyx_25020059_top__DOT__bgeu_branch) 
                                            & (IData)(vlSelfRef.ysyx_25020059_top__DOT__zero))
                                            ? (vlSelfRef.curr_pc 
                                               + vlSelfRef.ysyx_25020059_top__DOT__imm)
                                            : ((IData)(4U) 
                                               + vlSelfRef.curr_pc)))))))))
            : vlSelfRef.curr_pc);
    vlSelfRef.next_pc = vlSelfRef.ysyx_25020059_top__DOT__next_pc_from_mux;
    vlSelfRef.ysyx_25020059_top__DOT__u_pc_reg_0__DOT__use_pc 
        = ((IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_mret)
            ? vlSelfRef.ysyx_25020059_top__DOT__csr_mepc
            : ((IData)(vlSelfRef.ysyx_25020059_top__DOT__csr_ecall)
                ? vlSelfRef.ysyx_25020059_top__DOT__csr_mtvec
                : vlSelfRef.ysyx_25020059_top__DOT__next_pc_from_mux));
}

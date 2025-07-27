// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vysyx_25020059_top__Syms.h"


void Vysyx_25020059_top___024root__trace_chg_0_sub_0(Vysyx_25020059_top___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vysyx_25020059_top___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root__trace_chg_0\n"); );
    // Init
    Vysyx_25020059_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vysyx_25020059_top___024root*>(voidSelf);
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vysyx_25020059_top___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vysyx_25020059_top___024root__trace_chg_0_sub_0(Vysyx_25020059_top___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    (void)vlSelf;  // Prevent unused variable warning
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root__trace_chg_0_sub_0\n"); );
    auto &vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelfRef.__Vm_traceActivity[1U])) {
        bufp->chgBit(oldp+0,(vlSelfRef.ysyx_25020059_top__DOT__rst_n));
        bufp->chgBit(oldp+1,(vlSelfRef.ysyx_25020059_top__DOT__branch));
        bufp->chgBit(oldp+2,(vlSelfRef.ysyx_25020059_top__DOT__jal_jump));
        bufp->chgBit(oldp+3,(vlSelfRef.ysyx_25020059_top__DOT__jalr_jump));
        bufp->chgBit(oldp+4,(vlSelfRef.ysyx_25020059_top__DOT__reg_wen));
        bufp->chgCData(oldp+5,(vlSelfRef.ysyx_25020059_top__DOT__reg_waddr),5);
        bufp->chgCData(oldp+6,(vlSelfRef.ysyx_25020059_top__DOT__reg1_raddr),5);
        bufp->chgCData(oldp+7,(vlSelfRef.ysyx_25020059_top__DOT__reg2_raddr),5);
        bufp->chgCData(oldp+8,(vlSelfRef.ysyx_25020059_top__DOT__imm_gen_op),3);
        bufp->chgIData(oldp+9,(vlSelfRef.ysyx_25020059_top__DOT__imm),32);
        bufp->chgCData(oldp+10,(vlSelfRef.ysyx_25020059_top__DOT__alu_op),4);
        bufp->chgCData(oldp+11,(vlSelfRef.ysyx_25020059_top__DOT__alu_src_sel),2);
        bufp->chgBit(oldp+12,(vlSelfRef.ysyx_25020059_top__DOT__mem_valid));
        bufp->chgBit(oldp+13,(vlSelfRef.ysyx_25020059_top__DOT__mem_wen));
        bufp->chgCData(oldp+14,(vlSelfRef.ysyx_25020059_top__DOT__mem_size),2);
        bufp->chgBit(oldp+15,(vlSelfRef.ysyx_25020059_top__DOT__mem_unsigned));
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U] 
                     | vlSelfRef.__Vm_traceActivity
                     [2U]))) {
        bufp->chgBit(oldp+16,(vlSelfRef.ysyx_25020059_top__DOT__zero));
        bufp->chgIData(oldp+17,((((~ (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_wen)) 
                                  & (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_valid))
                                  ? vlSelfRef.ysyx_25020059_top__DOT__mem_rdata
                                  : vlSelfRef.ysyx_25020059_top__DOT__alu_res)),32);
        bufp->chgIData(oldp+18,(vlSelfRef.ysyx_25020059_top__DOT__reg1_rdata),32);
        bufp->chgIData(oldp+19,(vlSelfRef.ysyx_25020059_top__DOT__reg2_rdata),32);
        bufp->chgIData(oldp+20,(vlSelfRef.ysyx_25020059_top__DOT__alu_src1),32);
        bufp->chgIData(oldp+21,(vlSelfRef.ysyx_25020059_top__DOT__alu_src2),32);
        bufp->chgIData(oldp+22,(vlSelfRef.ysyx_25020059_top__DOT__alu_res),32);
        bufp->chgIData(oldp+23,(vlSelfRef.ysyx_25020059_top__DOT__mem_rdata),32);
        bufp->chgCData(oldp+24,((0xfU & ((0U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                                          ? ((IData)(1U) 
                                             << (3U 
                                                 & vlSelfRef.ysyx_25020059_top__DOT__alu_res))
                                          : ((1U == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                                              ? ((IData)(3U) 
                                                 << 
                                                 (3U 
                                                  & vlSelfRef.ysyx_25020059_top__DOT__alu_res))
                                              : ((2U 
                                                  == (IData)(vlSelfRef.ysyx_25020059_top__DOT__mem_size))
                                                  ? 0xfU
                                                  : 0U))))),4);
    }
    bufp->chgBit(oldp+25,(vlSelfRef.clk));
    bufp->chgBit(oldp+26,(vlSelfRef.rst));
    bufp->chgIData(oldp+27,(vlSelfRef.inst),32);
    bufp->chgIData(oldp+28,(vlSelfRef.curr_pc),32);
    bufp->chgIData(oldp+29,(vlSelfRef.next_pc),32);
    bufp->chgIData(oldp+30,(vlSelfRef.reg_f[0]),32);
    bufp->chgIData(oldp+31,(vlSelfRef.reg_f[1]),32);
    bufp->chgIData(oldp+32,(vlSelfRef.reg_f[2]),32);
    bufp->chgIData(oldp+33,(vlSelfRef.reg_f[3]),32);
    bufp->chgIData(oldp+34,(vlSelfRef.reg_f[4]),32);
    bufp->chgIData(oldp+35,(vlSelfRef.reg_f[5]),32);
    bufp->chgIData(oldp+36,(vlSelfRef.reg_f[6]),32);
    bufp->chgIData(oldp+37,(vlSelfRef.reg_f[7]),32);
    bufp->chgIData(oldp+38,(vlSelfRef.reg_f[8]),32);
    bufp->chgIData(oldp+39,(vlSelfRef.reg_f[9]),32);
    bufp->chgIData(oldp+40,(vlSelfRef.reg_f[10]),32);
    bufp->chgIData(oldp+41,(vlSelfRef.reg_f[11]),32);
    bufp->chgIData(oldp+42,(vlSelfRef.reg_f[12]),32);
    bufp->chgIData(oldp+43,(vlSelfRef.reg_f[13]),32);
    bufp->chgIData(oldp+44,(vlSelfRef.reg_f[14]),32);
    bufp->chgIData(oldp+45,(vlSelfRef.reg_f[15]),32);
    bufp->chgIData(oldp+46,(vlSelfRef.reg_f[16]),32);
    bufp->chgIData(oldp+47,(vlSelfRef.reg_f[17]),32);
    bufp->chgIData(oldp+48,(vlSelfRef.reg_f[18]),32);
    bufp->chgIData(oldp+49,(vlSelfRef.reg_f[19]),32);
    bufp->chgIData(oldp+50,(vlSelfRef.reg_f[20]),32);
    bufp->chgIData(oldp+51,(vlSelfRef.reg_f[21]),32);
    bufp->chgIData(oldp+52,(vlSelfRef.reg_f[22]),32);
    bufp->chgIData(oldp+53,(vlSelfRef.reg_f[23]),32);
    bufp->chgIData(oldp+54,(vlSelfRef.reg_f[24]),32);
    bufp->chgIData(oldp+55,(vlSelfRef.reg_f[25]),32);
    bufp->chgIData(oldp+56,(vlSelfRef.reg_f[26]),32);
    bufp->chgIData(oldp+57,(vlSelfRef.reg_f[27]),32);
    bufp->chgIData(oldp+58,(vlSelfRef.reg_f[28]),32);
    bufp->chgIData(oldp+59,(vlSelfRef.reg_f[29]),32);
    bufp->chgIData(oldp+60,(vlSelfRef.reg_f[30]),32);
    bufp->chgIData(oldp+61,(vlSelfRef.reg_f[31]),32);
    bufp->chgBit(oldp+62,(vlSelfRef.ysyx_25020059_top__DOT__ena));
    bufp->chgIData(oldp+63,(vlSelfRef.reg_f[0xaU]),32);
    bufp->chgCData(oldp+64,((0x7fU & vlSelfRef.inst)),7);
    bufp->chgCData(oldp+65,((7U & (vlSelfRef.inst >> 0xcU))),3);
    bufp->chgCData(oldp+66,((vlSelfRef.inst >> 0x19U)),7);
    bufp->chgCData(oldp+67,((0x1fU & (vlSelfRef.inst 
                                      >> 7U))),5);
    bufp->chgCData(oldp+68,((0x1fU & (vlSelfRef.inst 
                                      >> 0xfU))),5);
    bufp->chgCData(oldp+69,((0x1fU & (vlSelfRef.inst 
                                      >> 0x14U))),5);
    bufp->chgSData(oldp+70,((vlSelfRef.inst >> 0x14U)),12);
}

void Vysyx_25020059_top___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vysyx_25020059_top___024root__trace_cleanup\n"); );
    // Init
    Vysyx_25020059_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vysyx_25020059_top___024root*>(voidSelf);
    Vysyx_25020059_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}

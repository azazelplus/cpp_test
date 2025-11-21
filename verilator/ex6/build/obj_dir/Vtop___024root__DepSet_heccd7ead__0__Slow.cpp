// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    // Body
    Vtop___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vtrigrprev__TOP__BTNC = vlSelf->BTNC;
    vlSelf->__Vtrigrprev__TOP__top__DOT____Vcellinp__lfsr_inst__rst_n 
        = vlSelf->top__DOT____Vcellinp__lfsr_inst__rst_n;
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    // Body
    vlSelf->DEC0P = 1U;
    vlSelf->DEC1P = 1U;
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    // Init
    CData/*0:0*/ __VstlContinue;
    // Body
    vlSelf->__VstlIterCount = 0U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        __VstlContinue = 0U;
        Vtop___024root___eval_triggers__stl(vlSelf);
        if (vlSelf->__VstlTriggered.any()) {
            __VstlContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VstlIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__stl(vlSelf);
#endif
                VL_FATAL_MT("/home/azazel/Code_git/verilator/ex6/vsrc/ex6.v", 116, "", "Settle region did not converge.");
            }
            vlSelf->__VstlIterCount = ((IData)(1U) 
                                       + vlSelf->__VstlIterCount);
            Vtop___024root___eval_stl(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VstlTriggered.at(0U)) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

extern const VlUnpacked<CData/*6:0*/, 16> Vtop__ConstPool__TABLE_hb2a417e2_0;

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
    // Init
    CData/*6:0*/ top__DOT__seg0_h;
    top__DOT__seg0_h = 0;
    CData/*6:0*/ top__DOT__seg1_h;
    top__DOT__seg1_h = 0;
    CData/*3:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*3:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    // Body
    vlSelf->top__DOT____Vcellinp__lfsr_inst__rst_n 
        = (1U & (~ (IData)(vlSelf->SW0)));
    vlSelf->top__DOT__lfsr_inst__DOT__all_zeros = (0U 
                                                   == (IData)(vlSelf->top__DOT__lfsr_inst__DOT__q_reg));
    vlSelf->top__DOT__lfsr_inst__DOT__feedback = (1U 
                                                  & VL_REDXOR_8(
                                                                (0xb8U 
                                                                 & (IData)(vlSelf->top__DOT__lfsr_inst__DOT__q_reg))));
    __Vtableidx1 = (0xfU & (IData)(vlSelf->top__DOT__lfsr_inst__DOT__q_reg));
    top__DOT__seg0_h = Vtop__ConstPool__TABLE_hb2a417e2_0
        [__Vtableidx1];
    __Vtableidx2 = (0xfU & ((IData)(vlSelf->top__DOT__lfsr_inst__DOT__q_reg) 
                            >> 4U));
    top__DOT__seg1_h = Vtop__ConstPool__TABLE_hb2a417e2_0
        [__Vtableidx2];
    vlSelf->SEG0A = (1U & (IData)(top__DOT__seg0_h));
    vlSelf->SEG0B = (1U & ((IData)(top__DOT__seg0_h) 
                           >> 1U));
    vlSelf->SEG0C = (1U & ((IData)(top__DOT__seg0_h) 
                           >> 2U));
    vlSelf->SEG0D = (1U & ((IData)(top__DOT__seg0_h) 
                           >> 3U));
    vlSelf->SEG0E = (1U & ((IData)(top__DOT__seg0_h) 
                           >> 4U));
    vlSelf->SEG0F = (1U & ((IData)(top__DOT__seg0_h) 
                           >> 5U));
    vlSelf->SEG0G = (1U & ((IData)(top__DOT__seg0_h) 
                           >> 6U));
    vlSelf->SEG1A = (1U & (IData)(top__DOT__seg1_h));
    vlSelf->SEG1B = (1U & ((IData)(top__DOT__seg1_h) 
                           >> 1U));
    vlSelf->SEG1C = (1U & ((IData)(top__DOT__seg1_h) 
                           >> 2U));
    vlSelf->SEG1D = (1U & ((IData)(top__DOT__seg1_h) 
                           >> 3U));
    vlSelf->SEG1E = (1U & ((IData)(top__DOT__seg1_h) 
                           >> 4U));
    vlSelf->SEG1F = (1U & ((IData)(top__DOT__seg1_h) 
                           >> 5U));
    vlSelf->SEG1G = (1U & ((IData)(top__DOT__seg1_h) 
                           >> 6U));
}

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    // Body
    if (vlSelf->__VstlTriggered.at(0U)) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VicoTriggered.at(0U)) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VactTriggered.at(0U)) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge BTNC or negedge top.__Vcellinp__lfsr_inst__rst_n)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VnbaTriggered.at(0U)) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge BTNC or negedge top.__Vcellinp__lfsr_inst__rst_n)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->BTNC = 0;
    vlSelf->SW0 = 0;
    vlSelf->SEG0A = 0;
    vlSelf->SEG0B = 0;
    vlSelf->SEG0C = 0;
    vlSelf->SEG0D = 0;
    vlSelf->SEG0E = 0;
    vlSelf->SEG0F = 0;
    vlSelf->SEG0G = 0;
    vlSelf->DEC0P = 0;
    vlSelf->SEG1A = 0;
    vlSelf->SEG1B = 0;
    vlSelf->SEG1C = 0;
    vlSelf->SEG1D = 0;
    vlSelf->SEG1E = 0;
    vlSelf->SEG1F = 0;
    vlSelf->SEG1G = 0;
    vlSelf->DEC1P = 0;
    vlSelf->top__DOT____Vcellinp__lfsr_inst__rst_n = 0;
    vlSelf->top__DOT__lfsr_inst__DOT__q_reg = 0;
    vlSelf->top__DOT__lfsr_inst__DOT__feedback = 0;
    vlSelf->top__DOT__lfsr_inst__DOT__all_zeros = 0;
    vlSelf->__Vtrigrprev__TOP__BTNC = 0;
    vlSelf->__Vtrigrprev__TOP__top__DOT____Vcellinp__lfsr_inst__rst_n = 0;
}

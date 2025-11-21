// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->top__DOT____Vcellinp__lfsr_inst__rst_n 
        = (1U & (~ (IData)(vlSelf->SW0)));
}

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
}

extern const VlUnpacked<CData/*6:0*/, 16> Vtop__ConstPool__TABLE_hb2a417e2_0;

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
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
    vlSelf->top__DOT__lfsr_inst__DOT__q_reg = ((IData)(vlSelf->top__DOT____Vcellinp__lfsr_inst__rst_n)
                                                ? ((IData)(vlSelf->top__DOT__lfsr_inst__DOT__all_zeros)
                                                    ? 0xaaU
                                                    : 
                                                   (((IData)(vlSelf->top__DOT__lfsr_inst__DOT__feedback) 
                                                     << 7U) 
                                                    | (0x7fU 
                                                       & ((IData)(vlSelf->top__DOT__lfsr_inst__DOT__q_reg) 
                                                          >> 1U))))
                                                : 0xaaU);
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

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(0U)) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Init
    CData/*0:0*/ __VicoContinue;
    VlTriggerVec<1> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    vlSelf->__VicoIterCount = 0U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        __VicoContinue = 0U;
        Vtop___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("/home/azazel/Code_git/verilator/ex6/vsrc/ex6.v", 116, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            Vtop___024root___eval_ico(vlSelf);
        }
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            Vtop___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vtop___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("/home/azazel/Code_git/verilator/ex6/vsrc/ex6.v", 116, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vtop___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("/home/azazel/Code_git/verilator/ex6/vsrc/ex6.v", 116, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vtop___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->BTNC & 0xfeU))) {
        Verilated::overWidthError("BTNC");}
    if (VL_UNLIKELY((vlSelf->SW0 & 0xfeU))) {
        Verilated::overWidthError("SW0");}
}
#endif  // VL_DEBUG

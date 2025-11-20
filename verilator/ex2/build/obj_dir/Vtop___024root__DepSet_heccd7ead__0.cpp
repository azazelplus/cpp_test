// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

extern const VlUnpacked<CData/*2:0*/, 512> Vtop__ConstPool__TABLE_h0d68042a_0;
extern const VlUnpacked<CData/*6:0*/, 16> Vtop__ConstPool__TABLE_hb2a417e2_0;

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    // Init
    CData/*7:0*/ top__DOT__SW;
    top__DOT__SW = 0;
    CData/*2:0*/ top__DOT__code;
    top__DOT__code = 0;
    CData/*6:0*/ top__DOT__h;
    top__DOT__h = 0;
    SData/*8:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*3:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    // Body
    top__DOT__SW = (((IData)(vlSelf->SW7) << 7U) | 
                    (((IData)(vlSelf->SW6) << 6U) | 
                     (((IData)(vlSelf->SW5) << 5U) 
                      | (((IData)(vlSelf->SW4) << 4U) 
                         | (((IData)(vlSelf->SW3) << 3U) 
                            | (((IData)(vlSelf->SW2) 
                                << 2U) | (((IData)(vlSelf->SW1) 
                                           << 1U) | (IData)(vlSelf->SW0))))))));
    __Vtableidx1 = (((IData)(top__DOT__SW) << 1U) | (IData)(vlSelf->SW8));
    top__DOT__code = Vtop__ConstPool__TABLE_h0d68042a_0
        [__Vtableidx1];
    __Vtableidx2 = top__DOT__code;
    top__DOT__h = Vtop__ConstPool__TABLE_hb2a417e2_0
        [__Vtableidx2];
    vlSelf->SEG0A = (1U & (IData)(top__DOT__h));
    vlSelf->SEG0B = (1U & ((IData)(top__DOT__h) >> 1U));
    vlSelf->SEG0C = (1U & ((IData)(top__DOT__h) >> 2U));
    vlSelf->SEG0D = (1U & ((IData)(top__DOT__h) >> 3U));
    vlSelf->SEG0E = (1U & ((IData)(top__DOT__h) >> 4U));
    vlSelf->SEG0F = (1U & ((IData)(top__DOT__h) >> 5U));
    vlSelf->SEG0G = (1U & ((IData)(top__DOT__h) >> 6U));
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

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
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
    VlTriggerVec<0> __VpreTriggered;
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
                VL_FATAL_MT("/home/azazel/Code_git/verilator/ex2/vsrc/ex2.v", 115, "", "Input combinational region did not converge.");
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
                    VL_FATAL_MT("/home/azazel/Code_git/verilator/ex2/vsrc/ex2.v", 115, "", "Active region did not converge.");
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
                VL_FATAL_MT("/home/azazel/Code_git/verilator/ex2/vsrc/ex2.v", 115, "", "NBA region did not converge.");
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
    if (VL_UNLIKELY((vlSelf->SW0 & 0xfeU))) {
        Verilated::overWidthError("SW0");}
    if (VL_UNLIKELY((vlSelf->SW1 & 0xfeU))) {
        Verilated::overWidthError("SW1");}
    if (VL_UNLIKELY((vlSelf->SW2 & 0xfeU))) {
        Verilated::overWidthError("SW2");}
    if (VL_UNLIKELY((vlSelf->SW3 & 0xfeU))) {
        Verilated::overWidthError("SW3");}
    if (VL_UNLIKELY((vlSelf->SW4 & 0xfeU))) {
        Verilated::overWidthError("SW4");}
    if (VL_UNLIKELY((vlSelf->SW5 & 0xfeU))) {
        Verilated::overWidthError("SW5");}
    if (VL_UNLIKELY((vlSelf->SW6 & 0xfeU))) {
        Verilated::overWidthError("SW6");}
    if (VL_UNLIKELY((vlSelf->SW7 & 0xfeU))) {
        Verilated::overWidthError("SW7");}
    if (VL_UNLIKELY((vlSelf->SW8 & 0xfeU))) {
        Verilated::overWidthError("SW8");}
}
#endif  // VL_DEBUG

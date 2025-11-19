// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmux4to1_2bit.h for the primary calling header

#include "verilated.h"

#include "Vmux4to1_2bit___024root.h"

VL_INLINE_OPT void Vmux4to1_2bit___024root___ico_sequent__TOP__0(Vmux4to1_2bit___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmux4to1_2bit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux4to1_2bit___024root___ico_sequent__TOP__0\n"); );
    // Init
    CData/*1:0*/ mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__lut_out;
    mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__lut_out = 0;
    // Body
    vlSelf->mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__data_list[0U] 
        = vlSelf->X3;
    vlSelf->mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__data_list[1U] 
        = vlSelf->X2;
    vlSelf->mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__data_list[2U] 
        = vlSelf->X1;
    vlSelf->mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__data_list[3U] 
        = vlSelf->X0;
    mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__lut_out 
        = ((- (IData)(((IData)(vlSelf->Y) == vlSelf->mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__key_list
                       [0U]))) & vlSelf->mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__data_list
           [0U]);
    mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__lut_out 
        = ((IData)(mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__lut_out) 
           | ((- (IData)(((IData)(vlSelf->Y) == vlSelf->mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__key_list
                          [1U]))) & vlSelf->mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__data_list
              [1U]));
    mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__lut_out 
        = ((IData)(mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__lut_out) 
           | ((- (IData)(((IData)(vlSelf->Y) == vlSelf->mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__key_list
                          [2U]))) & vlSelf->mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__data_list
              [2U]));
    mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__lut_out 
        = ((IData)(mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__lut_out) 
           | ((- (IData)(((IData)(vlSelf->Y) == vlSelf->mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__key_list
                          [3U]))) & vlSelf->mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__data_list
              [3U]));
    vlSelf->F = mux4to1_2bit__DOT__mux_instance__DOT__i0__DOT__lut_out;
}

void Vmux4to1_2bit___024root___eval_ico(Vmux4to1_2bit___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmux4to1_2bit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux4to1_2bit___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        Vmux4to1_2bit___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vmux4to1_2bit___024root___eval_act(Vmux4to1_2bit___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmux4to1_2bit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux4to1_2bit___024root___eval_act\n"); );
}

void Vmux4to1_2bit___024root___eval_nba(Vmux4to1_2bit___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmux4to1_2bit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux4to1_2bit___024root___eval_nba\n"); );
}

void Vmux4to1_2bit___024root___eval_triggers__ico(Vmux4to1_2bit___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vmux4to1_2bit___024root___dump_triggers__ico(Vmux4to1_2bit___024root* vlSelf);
#endif  // VL_DEBUG
void Vmux4to1_2bit___024root___eval_triggers__act(Vmux4to1_2bit___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vmux4to1_2bit___024root___dump_triggers__act(Vmux4to1_2bit___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vmux4to1_2bit___024root___dump_triggers__nba(Vmux4to1_2bit___024root* vlSelf);
#endif  // VL_DEBUG

void Vmux4to1_2bit___024root___eval(Vmux4to1_2bit___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmux4to1_2bit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux4to1_2bit___024root___eval\n"); );
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
        Vmux4to1_2bit___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                Vmux4to1_2bit___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("/home/azazel/Code_git/verilator/ex1/vsrc/ex1.v", 86, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            Vmux4to1_2bit___024root___eval_ico(vlSelf);
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
            Vmux4to1_2bit___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vmux4to1_2bit___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("/home/azazel/Code_git/verilator/ex1/vsrc/ex1.v", 86, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vmux4to1_2bit___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vmux4to1_2bit___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("/home/azazel/Code_git/verilator/ex1/vsrc/ex1.v", 86, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vmux4to1_2bit___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vmux4to1_2bit___024root___eval_debug_assertions(Vmux4to1_2bit___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vmux4to1_2bit__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmux4to1_2bit___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->Y & 0xfcU))) {
        Verilated::overWidthError("Y");}
    if (VL_UNLIKELY((vlSelf->X0 & 0xfcU))) {
        Verilated::overWidthError("X0");}
    if (VL_UNLIKELY((vlSelf->X1 & 0xfcU))) {
        Verilated::overWidthError("X1");}
    if (VL_UNLIKELY((vlSelf->X2 & 0xfcU))) {
        Verilated::overWidthError("X2");}
    if (VL_UNLIKELY((vlSelf->X3 & 0xfcU))) {
        Verilated::overWidthError("X3");}
}
#endif  // VL_DEBUG

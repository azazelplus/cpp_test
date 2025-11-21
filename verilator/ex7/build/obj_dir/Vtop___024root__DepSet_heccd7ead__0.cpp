// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
}

extern const VlUnpacked<CData/*6:0*/, 16> Vtop__ConstPool__TABLE_hb2a417e2_0;
extern const VlUnpacked<CData/*7:0*/, 256> Vtop__ConstPool__TABLE_ha352da98_0;

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*6:0*/ top__DOT__d0__DOT__h_raw;
    top__DOT__d0__DOT__h_raw = 0;
    CData/*6:0*/ top__DOT__d0__DOT__l_raw;
    top__DOT__d0__DOT__l_raw = 0;
    CData/*6:0*/ top__DOT__d1__DOT__h_raw;
    top__DOT__d1__DOT__h_raw = 0;
    CData/*6:0*/ top__DOT__d1__DOT__l_raw;
    top__DOT__d1__DOT__l_raw = 0;
    CData/*6:0*/ top__DOT__d2__DOT__h_raw;
    top__DOT__d2__DOT__h_raw = 0;
    CData/*6:0*/ top__DOT__d2__DOT__l_raw;
    top__DOT__d2__DOT__l_raw = 0;
    CData/*7:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*3:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    CData/*3:0*/ __Vtableidx3;
    __Vtableidx3 = 0;
    CData/*3:0*/ __Vtableidx4;
    __Vtableidx4 = 0;
    CData/*3:0*/ __Vtableidx5;
    __Vtableidx5 = 0;
    CData/*3:0*/ __Vtableidx6;
    __Vtableidx6 = 0;
    CData/*3:0*/ __Vtableidx7;
    __Vtableidx7 = 0;
    CData/*7:0*/ __Vdly__top__DOT__count;
    __Vdly__top__DOT__count = 0;
    CData/*7:0*/ __Vdly__top__DOT__cur_key;
    __Vdly__top__DOT__cur_key = 0;
    CData/*0:0*/ __Vdly__top__DOT__display_on;
    __Vdly__top__DOT__display_on = 0;
    CData/*1:0*/ __Vdly__top__DOT__state;
    __Vdly__top__DOT__state = 0;
    CData/*0:0*/ __Vdly__top__DOT__nextdata_n;
    __Vdly__top__DOT__nextdata_n = 0;
    CData/*2:0*/ __Vdly__top__DOT__inst_ps2_keyboard__DOT__ps2_clk_sync;
    __Vdly__top__DOT__inst_ps2_keyboard__DOT__ps2_clk_sync = 0;
    CData/*3:0*/ __Vdly__top__DOT__inst_ps2_keyboard__DOT__count;
    __Vdly__top__DOT__inst_ps2_keyboard__DOT__count = 0;
    CData/*2:0*/ __Vdly__top__DOT__inst_ps2_keyboard__DOT__w_ptr;
    __Vdly__top__DOT__inst_ps2_keyboard__DOT__w_ptr = 0;
    CData/*2:0*/ __Vdly__top__DOT__inst_ps2_keyboard__DOT__r_ptr;
    __Vdly__top__DOT__inst_ps2_keyboard__DOT__r_ptr = 0;
    CData/*0:0*/ __Vdly__top__DOT__overflow;
    __Vdly__top__DOT__overflow = 0;
    CData/*0:0*/ __Vdly__top__DOT__ready;
    __Vdly__top__DOT__ready = 0;
    CData/*2:0*/ __Vdlyvdim0__top__DOT__inst_ps2_keyboard__DOT__fifo__v0;
    __Vdlyvdim0__top__DOT__inst_ps2_keyboard__DOT__fifo__v0 = 0;
    CData/*7:0*/ __Vdlyvval__top__DOT__inst_ps2_keyboard__DOT__fifo__v0;
    __Vdlyvval__top__DOT__inst_ps2_keyboard__DOT__fifo__v0 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__inst_ps2_keyboard__DOT__fifo__v0;
    __Vdlyvset__top__DOT__inst_ps2_keyboard__DOT__fifo__v0 = 0;
    // Body
    __Vdly__top__DOT__inst_ps2_keyboard__DOT__ps2_clk_sync 
        = vlSelf->top__DOT__inst_ps2_keyboard__DOT__ps2_clk_sync;
    __Vdly__top__DOT__ready = vlSelf->top__DOT__ready;
    __Vdly__top__DOT__overflow = vlSelf->top__DOT__overflow;
    __Vdly__top__DOT__inst_ps2_keyboard__DOT__w_ptr 
        = vlSelf->top__DOT__inst_ps2_keyboard__DOT__w_ptr;
    __Vdly__top__DOT__inst_ps2_keyboard__DOT__count 
        = vlSelf->top__DOT__inst_ps2_keyboard__DOT__count;
    __Vdly__top__DOT__inst_ps2_keyboard__DOT__r_ptr 
        = vlSelf->top__DOT__inst_ps2_keyboard__DOT__r_ptr;
    __Vdlyvset__top__DOT__inst_ps2_keyboard__DOT__fifo__v0 = 0U;
    __Vdly__top__DOT__nextdata_n = vlSelf->top__DOT__nextdata_n;
    __Vdly__top__DOT__state = vlSelf->top__DOT__state;
    __Vdly__top__DOT__display_on = vlSelf->top__DOT__display_on;
    __Vdly__top__DOT__count = vlSelf->top__DOT__count;
    __Vdly__top__DOT__cur_key = vlSelf->top__DOT__cur_key;
    __Vdly__top__DOT__inst_ps2_keyboard__DOT__ps2_clk_sync 
        = ((6U & ((IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__ps2_clk_sync) 
                  << 1U)) | (IData)(vlSelf->ps2_clk));
    if (vlSelf->rst) {
        __Vdly__top__DOT__inst_ps2_keyboard__DOT__count = 0U;
        __Vdly__top__DOT__inst_ps2_keyboard__DOT__w_ptr = 0U;
        __Vdly__top__DOT__inst_ps2_keyboard__DOT__r_ptr = 0U;
        __Vdly__top__DOT__overflow = 0U;
        __Vdly__top__DOT__ready = 0U;
        __Vdly__top__DOT__count = 0U;
        __Vdly__top__DOT__cur_key = 0U;
        vlSelf->top__DOT__cur_ascii = 0U;
        __Vdly__top__DOT__display_on = 0U;
        __Vdly__top__DOT__state = 0U;
        __Vdly__top__DOT__nextdata_n = 1U;
    } else {
        if (vlSelf->top__DOT__ready) {
            if ((1U & (~ (IData)(vlSelf->top__DOT__nextdata_n)))) {
                __Vdly__top__DOT__inst_ps2_keyboard__DOT__r_ptr 
                    = (7U & ((IData)(1U) + (IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__r_ptr)));
                if (((IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__w_ptr) 
                     == (7U & ((IData)(1U) + (IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__r_ptr))))) {
                    __Vdly__top__DOT__ready = 0U;
                }
            }
        }
        if ((IData)((4U == (6U & (IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__ps2_clk_sync))))) {
            if ((0xaU == (IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__count))) {
                if ((((~ (IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__buffer)) 
                      & (IData)(vlSelf->ps2_data)) 
                     & VL_REDXOR_32((0x1ffU & ((IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__buffer) 
                                               >> 1U))))) {
                    __Vdlyvval__top__DOT__inst_ps2_keyboard__DOT__fifo__v0 
                        = (0xffU & ((IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__buffer) 
                                    >> 1U));
                    __Vdlyvset__top__DOT__inst_ps2_keyboard__DOT__fifo__v0 = 1U;
                    __Vdlyvdim0__top__DOT__inst_ps2_keyboard__DOT__fifo__v0 
                        = vlSelf->top__DOT__inst_ps2_keyboard__DOT__w_ptr;
                    __Vdly__top__DOT__ready = 1U;
                    __Vdly__top__DOT__inst_ps2_keyboard__DOT__w_ptr 
                        = (7U & ((IData)(1U) + (IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__w_ptr)));
                    __Vdly__top__DOT__overflow = ((IData)(vlSelf->top__DOT__overflow) 
                                                  | ((IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__r_ptr) 
                                                     == 
                                                     (7U 
                                                      & ((IData)(1U) 
                                                         + (IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__w_ptr)))));
                }
                __Vdly__top__DOT__inst_ps2_keyboard__DOT__count = 0U;
            } else {
                vlSelf->top__DOT__inst_ps2_keyboard__DOT____Vlvbound_h1a91ade8__0 
                    = vlSelf->ps2_data;
                if ((9U >= (IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__count))) {
                    vlSelf->top__DOT__inst_ps2_keyboard__DOT__buffer 
                        = (((~ ((IData)(1U) << (IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__count))) 
                            & (IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__buffer)) 
                           | (0x3ffU & ((IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT____Vlvbound_h1a91ade8__0) 
                                        << (IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__count))));
                }
                __Vdly__top__DOT__inst_ps2_keyboard__DOT__count 
                    = (0xfU & ((IData)(1U) + (IData)(vlSelf->top__DOT__inst_ps2_keyboard__DOT__count)));
            }
        }
        __Vdly__top__DOT__nextdata_n = 1U;
        if (((IData)(vlSelf->top__DOT__ready) & (IData)(vlSelf->top__DOT__nextdata_n))) {
            __Vdly__top__DOT__nextdata_n = 0U;
            if ((0U == (IData)(vlSelf->top__DOT__state))) {
                if ((0xf0U == (IData)(vlSelf->top__DOT__data))) {
                    __Vdly__top__DOT__state = 1U;
                } else if ((1U & ((~ (IData)(vlSelf->top__DOT__display_on)) 
                                  | ((IData)(vlSelf->top__DOT__cur_key) 
                                     != (IData)(vlSelf->top__DOT__data))))) {
                    __Vdly__top__DOT__cur_key = vlSelf->top__DOT__data;
                    vlSelf->top__DOT__cur_ascii = vlSelf->top__DOT__ascii_out;
                    if ((0U != (IData)(vlSelf->top__DOT__ascii_out))) {
                        __Vdly__top__DOT__count = (0xffU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlSelf->top__DOT__count)));
                        __Vdly__top__DOT__display_on = 1U;
                    }
                }
            } else if ((1U == (IData)(vlSelf->top__DOT__state))) {
                __Vdly__top__DOT__display_on = 0U;
                __Vdly__top__DOT__state = 0U;
            }
        }
    }
    vlSelf->top__DOT__inst_ps2_keyboard__DOT__count 
        = __Vdly__top__DOT__inst_ps2_keyboard__DOT__count;
    vlSelf->top__DOT__inst_ps2_keyboard__DOT__w_ptr 
        = __Vdly__top__DOT__inst_ps2_keyboard__DOT__w_ptr;
    vlSelf->top__DOT__overflow = __Vdly__top__DOT__overflow;
    vlSelf->top__DOT__inst_ps2_keyboard__DOT__ps2_clk_sync 
        = __Vdly__top__DOT__inst_ps2_keyboard__DOT__ps2_clk_sync;
    vlSelf->top__DOT__inst_ps2_keyboard__DOT__r_ptr 
        = __Vdly__top__DOT__inst_ps2_keyboard__DOT__r_ptr;
    if (__Vdlyvset__top__DOT__inst_ps2_keyboard__DOT__fifo__v0) {
        vlSelf->top__DOT__inst_ps2_keyboard__DOT__fifo[__Vdlyvdim0__top__DOT__inst_ps2_keyboard__DOT__fifo__v0] 
            = __Vdlyvval__top__DOT__inst_ps2_keyboard__DOT__fifo__v0;
    }
    vlSelf->top__DOT__state = __Vdly__top__DOT__state;
    vlSelf->top__DOT__ready = __Vdly__top__DOT__ready;
    vlSelf->top__DOT__nextdata_n = __Vdly__top__DOT__nextdata_n;
    vlSelf->top__DOT__display_on = __Vdly__top__DOT__display_on;
    vlSelf->top__DOT__count = __Vdly__top__DOT__count;
    vlSelf->top__DOT__cur_key = __Vdly__top__DOT__cur_key;
    vlSelf->top__DOT__data = vlSelf->top__DOT__inst_ps2_keyboard__DOT__fifo
        [vlSelf->top__DOT__inst_ps2_keyboard__DOT__r_ptr];
    __Vtableidx6 = (0xfU & ((IData)(vlSelf->top__DOT__count) 
                            >> 4U));
    top__DOT__d2__DOT__h_raw = Vtop__ConstPool__TABLE_hb2a417e2_0
        [__Vtableidx6];
    __Vtableidx7 = (0xfU & (IData)(vlSelf->top__DOT__count));
    top__DOT__d2__DOT__l_raw = Vtop__ConstPool__TABLE_hb2a417e2_0
        [__Vtableidx7];
    __Vtableidx2 = (0xfU & ((IData)(vlSelf->top__DOT__cur_key) 
                            >> 4U));
    top__DOT__d0__DOT__h_raw = Vtop__ConstPool__TABLE_hb2a417e2_0
        [__Vtableidx2];
    __Vtableidx3 = (0xfU & (IData)(vlSelf->top__DOT__cur_key));
    top__DOT__d0__DOT__l_raw = Vtop__ConstPool__TABLE_hb2a417e2_0
        [__Vtableidx3];
    __Vtableidx4 = (0xfU & ((IData)(vlSelf->top__DOT__cur_ascii) 
                            >> 4U));
    top__DOT__d1__DOT__h_raw = Vtop__ConstPool__TABLE_hb2a417e2_0
        [__Vtableidx4];
    __Vtableidx5 = (0xfU & (IData)(vlSelf->top__DOT__cur_ascii));
    top__DOT__d1__DOT__l_raw = Vtop__ConstPool__TABLE_hb2a417e2_0
        [__Vtableidx5];
    __Vtableidx1 = vlSelf->top__DOT__data;
    vlSelf->top__DOT__ascii_out = Vtop__ConstPool__TABLE_ha352da98_0
        [__Vtableidx1];
    vlSelf->seg5 = (1U | ((0x80U & ((IData)(top__DOT__d2__DOT__h_raw) 
                                    << 7U)) | ((0x40U 
                                                & ((IData)(top__DOT__d2__DOT__h_raw) 
                                                   << 5U)) 
                                               | ((0x20U 
                                                   & ((IData)(top__DOT__d2__DOT__h_raw) 
                                                      << 3U)) 
                                                  | ((0x10U 
                                                      & ((IData)(top__DOT__d2__DOT__h_raw) 
                                                         << 1U)) 
                                                     | ((8U 
                                                         & ((IData)(top__DOT__d2__DOT__h_raw) 
                                                            >> 1U)) 
                                                        | ((4U 
                                                            & ((IData)(top__DOT__d2__DOT__h_raw) 
                                                               >> 3U)) 
                                                           | (2U 
                                                              & ((IData)(top__DOT__d2__DOT__h_raw) 
                                                                 >> 5U)))))))));
    vlSelf->seg4 = (1U | ((0x80U & ((IData)(top__DOT__d2__DOT__l_raw) 
                                    << 7U)) | ((0x40U 
                                                & ((IData)(top__DOT__d2__DOT__l_raw) 
                                                   << 5U)) 
                                               | ((0x20U 
                                                   & ((IData)(top__DOT__d2__DOT__l_raw) 
                                                      << 3U)) 
                                                  | ((0x10U 
                                                      & ((IData)(top__DOT__d2__DOT__l_raw) 
                                                         << 1U)) 
                                                     | ((8U 
                                                         & ((IData)(top__DOT__d2__DOT__l_raw) 
                                                            >> 1U)) 
                                                        | ((4U 
                                                            & ((IData)(top__DOT__d2__DOT__l_raw) 
                                                               >> 3U)) 
                                                           | (2U 
                                                              & ((IData)(top__DOT__d2__DOT__l_raw) 
                                                                 >> 5U)))))))));
    if (vlSelf->top__DOT__display_on) {
        vlSelf->seg1 = (1U | ((0x80U & ((IData)(top__DOT__d0__DOT__h_raw) 
                                        << 7U)) | (
                                                   (0x40U 
                                                    & ((IData)(top__DOT__d0__DOT__h_raw) 
                                                       << 5U)) 
                                                   | ((0x20U 
                                                       & ((IData)(top__DOT__d0__DOT__h_raw) 
                                                          << 3U)) 
                                                      | ((0x10U 
                                                          & ((IData)(top__DOT__d0__DOT__h_raw) 
                                                             << 1U)) 
                                                         | ((8U 
                                                             & ((IData)(top__DOT__d0__DOT__h_raw) 
                                                                >> 1U)) 
                                                            | ((4U 
                                                                & ((IData)(top__DOT__d0__DOT__h_raw) 
                                                                   >> 3U)) 
                                                               | (2U 
                                                                  & ((IData)(top__DOT__d0__DOT__h_raw) 
                                                                     >> 5U)))))))));
        vlSelf->seg0 = (1U | ((0x80U & ((IData)(top__DOT__d0__DOT__l_raw) 
                                        << 7U)) | (
                                                   (0x40U 
                                                    & ((IData)(top__DOT__d0__DOT__l_raw) 
                                                       << 5U)) 
                                                   | ((0x20U 
                                                       & ((IData)(top__DOT__d0__DOT__l_raw) 
                                                          << 3U)) 
                                                      | ((0x10U 
                                                          & ((IData)(top__DOT__d0__DOT__l_raw) 
                                                             << 1U)) 
                                                         | ((8U 
                                                             & ((IData)(top__DOT__d0__DOT__l_raw) 
                                                                >> 1U)) 
                                                            | ((4U 
                                                                & ((IData)(top__DOT__d0__DOT__l_raw) 
                                                                   >> 3U)) 
                                                               | (2U 
                                                                  & ((IData)(top__DOT__d0__DOT__l_raw) 
                                                                     >> 5U)))))))));
        vlSelf->seg3 = (1U | ((0x80U & ((IData)(top__DOT__d1__DOT__h_raw) 
                                        << 7U)) | (
                                                   (0x40U 
                                                    & ((IData)(top__DOT__d1__DOT__h_raw) 
                                                       << 5U)) 
                                                   | ((0x20U 
                                                       & ((IData)(top__DOT__d1__DOT__h_raw) 
                                                          << 3U)) 
                                                      | ((0x10U 
                                                          & ((IData)(top__DOT__d1__DOT__h_raw) 
                                                             << 1U)) 
                                                         | ((8U 
                                                             & ((IData)(top__DOT__d1__DOT__h_raw) 
                                                                >> 1U)) 
                                                            | ((4U 
                                                                & ((IData)(top__DOT__d1__DOT__h_raw) 
                                                                   >> 3U)) 
                                                               | (2U 
                                                                  & ((IData)(top__DOT__d1__DOT__h_raw) 
                                                                     >> 5U)))))))));
        vlSelf->seg2 = (1U | ((0x80U & ((IData)(top__DOT__d1__DOT__l_raw) 
                                        << 7U)) | (
                                                   (0x40U 
                                                    & ((IData)(top__DOT__d1__DOT__l_raw) 
                                                       << 5U)) 
                                                   | ((0x20U 
                                                       & ((IData)(top__DOT__d1__DOT__l_raw) 
                                                          << 3U)) 
                                                      | ((0x10U 
                                                          & ((IData)(top__DOT__d1__DOT__l_raw) 
                                                             << 1U)) 
                                                         | ((8U 
                                                             & ((IData)(top__DOT__d1__DOT__l_raw) 
                                                                >> 1U)) 
                                                            | ((4U 
                                                                & ((IData)(top__DOT__d1__DOT__l_raw) 
                                                                   >> 3U)) 
                                                               | (2U 
                                                                  & ((IData)(top__DOT__d1__DOT__l_raw) 
                                                                     >> 5U)))))))));
    } else {
        vlSelf->seg1 = 0xffU;
        vlSelf->seg0 = 0xffU;
        vlSelf->seg3 = 0xffU;
        vlSelf->seg2 = 0xffU;
    }
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
    VlTriggerVec<1> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
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
                    VL_FATAL_MT("/home/azazel/Code_git/verilator/ex7/vsrc/ex7.v", 187, "", "Active region did not converge.");
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
                VL_FATAL_MT("/home/azazel/Code_git/verilator/ex7/vsrc/ex7.v", 187, "", "NBA region did not converge.");
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
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY((vlSelf->ps2_clk & 0xfeU))) {
        Verilated::overWidthError("ps2_clk");}
    if (VL_UNLIKELY((vlSelf->ps2_data & 0xfeU))) {
        Verilated::overWidthError("ps2_data");}
}
#endif  // VL_DEBUG

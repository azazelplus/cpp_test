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

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigrprev__TOP__clk = vlSelf->clk;
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
                VL_FATAL_MT("/home/azazel/Code_git/verilator/ex7/vsrc/ex7.v", 187, "", "Settle region did not converge.");
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
extern const VlUnpacked<CData/*7:0*/, 256> Vtop__ConstPool__TABLE_ha352da98_0;

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
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
    // Body
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
    vlSelf->top__DOT__data = vlSelf->top__DOT__inst_ps2_keyboard__DOT__fifo
        [vlSelf->top__DOT__inst_ps2_keyboard__DOT__r_ptr];
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
    __Vtableidx1 = vlSelf->top__DOT__data;
    vlSelf->top__DOT__ascii_out = Vtop__ConstPool__TABLE_ha352da98_0
        [__Vtableidx1];
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
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VactTriggered.at(0U)) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
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
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = 0;
    vlSelf->rst = 0;
    vlSelf->ps2_clk = 0;
    vlSelf->ps2_data = 0;
    vlSelf->seg0 = 0;
    vlSelf->seg1 = 0;
    vlSelf->seg2 = 0;
    vlSelf->seg3 = 0;
    vlSelf->seg4 = 0;
    vlSelf->seg5 = 0;
    vlSelf->top__DOT__data = 0;
    vlSelf->top__DOT__ready = 0;
    vlSelf->top__DOT__overflow = 0;
    vlSelf->top__DOT__nextdata_n = 0;
    vlSelf->top__DOT__cur_key = 0;
    vlSelf->top__DOT__cur_ascii = 0;
    vlSelf->top__DOT__count = 0;
    vlSelf->top__DOT__state = 0;
    vlSelf->top__DOT__display_on = 0;
    vlSelf->top__DOT__ascii_out = 0;
    vlSelf->top__DOT__inst_ps2_keyboard__DOT__buffer = 0;
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->top__DOT__inst_ps2_keyboard__DOT__fifo[__Vi0] = 0;
    }
    vlSelf->top__DOT__inst_ps2_keyboard__DOT__w_ptr = 0;
    vlSelf->top__DOT__inst_ps2_keyboard__DOT__r_ptr = 0;
    vlSelf->top__DOT__inst_ps2_keyboard__DOT__count = 0;
    vlSelf->top__DOT__inst_ps2_keyboard__DOT__ps2_clk_sync = 0;
    vlSelf->top__DOT__inst_ps2_keyboard__DOT____Vlvbound_h1a91ade8__0 = 0;
    vlSelf->__Vtrigrprev__TOP__clk = 0;
}

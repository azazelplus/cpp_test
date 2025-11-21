// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"

class Vtop__Syms;

class Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(BTNC,0,0);
    CData/*0:0*/ top__DOT____Vcellinp__lfsr_inst__rst_n;
    VL_IN8(SW0,0,0);
    VL_OUT8(SEG0A,0,0);
    VL_OUT8(SEG0B,0,0);
    VL_OUT8(SEG0C,0,0);
    VL_OUT8(SEG0D,0,0);
    VL_OUT8(SEG0E,0,0);
    VL_OUT8(SEG0F,0,0);
    VL_OUT8(SEG0G,0,0);
    VL_OUT8(DEC0P,0,0);
    VL_OUT8(SEG1A,0,0);
    VL_OUT8(SEG1B,0,0);
    VL_OUT8(SEG1C,0,0);
    VL_OUT8(SEG1D,0,0);
    VL_OUT8(SEG1E,0,0);
    VL_OUT8(SEG1F,0,0);
    VL_OUT8(SEG1G,0,0);
    VL_OUT8(DEC1P,0,0);
    CData/*7:0*/ top__DOT__lfsr_inst__DOT__q_reg;
    CData/*0:0*/ top__DOT__lfsr_inst__DOT__feedback;
    CData/*0:0*/ top__DOT__lfsr_inst__DOT__all_zeros;
    CData/*0:0*/ __Vtrigrprev__TOP__BTNC;
    CData/*0:0*/ __Vtrigrprev__TOP__top__DOT____Vcellinp__lfsr_inst__rst_n;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VstlIterCount;
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard

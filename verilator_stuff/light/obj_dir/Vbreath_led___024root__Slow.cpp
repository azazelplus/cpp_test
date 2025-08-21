// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vbreath_led.h for the primary calling header

#include "verilated.h"

#include "Vbreath_led__Syms.h"
#include "Vbreath_led___024root.h"

void Vbreath_led___024root___ctor_var_reset(Vbreath_led___024root* vlSelf);

Vbreath_led___024root::Vbreath_led___024root(Vbreath_led__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vbreath_led___024root___ctor_var_reset(this);
}

void Vbreath_led___024root::__Vconfigure(bool first) {
    if (false && first) {}  // Prevent unused
}

Vbreath_led___024root::~Vbreath_led___024root() {
}

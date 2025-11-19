// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VBREATH_LED__SYMS_H_
#define VERILATED_VBREATH_LED__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vbreath_led.h"

// INCLUDE MODULE CLASSES
#include "Vbreath_led___024root.h"

// SYMS CLASS (contains all model state)
class Vbreath_led__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vbreath_led* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vbreath_led___024root          TOP;

    // CONSTRUCTORS
    Vbreath_led__Syms(VerilatedContext* contextp, const char* namep, Vbreath_led* modelp);
    ~Vbreath_led__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard

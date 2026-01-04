// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VDUAL_CONTROL_SWITCH__SYMS_H_
#define VERILATED_VDUAL_CONTROL_SWITCH__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vdual_control_switch.h"

// INCLUDE MODULE CLASSES
#include "Vdual_control_switch___024root.h"

// SYMS CLASS (contains all model state)
class Vdual_control_switch__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vdual_control_switch* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vdual_control_switch___024root TOP;

    // CONSTRUCTORS
    Vdual_control_switch__Syms(VerilatedContext* contextp, const char* namep, Vdual_control_switch* modelp);
    ~Vdual_control_switch__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard

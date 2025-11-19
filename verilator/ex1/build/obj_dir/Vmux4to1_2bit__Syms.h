// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VMUX4TO1_2BIT__SYMS_H_
#define VERILATED_VMUX4TO1_2BIT__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vmux4to1_2bit.h"

// INCLUDE MODULE CLASSES
#include "Vmux4to1_2bit___024root.h"

// SYMS CLASS (contains all model state)
class Vmux4to1_2bit__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vmux4to1_2bit* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vmux4to1_2bit___024root        TOP;

    // CONSTRUCTORS
    Vmux4to1_2bit__Syms(VerilatedContext* contextp, const char* namep, Vmux4to1_2bit* modelp);
    ~Vmux4to1_2bit__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard

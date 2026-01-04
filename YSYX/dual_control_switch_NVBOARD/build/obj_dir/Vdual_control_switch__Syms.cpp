// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vdual_control_switch__Syms.h"
#include "Vdual_control_switch.h"
#include "Vdual_control_switch___024root.h"

// FUNCTIONS
Vdual_control_switch__Syms::~Vdual_control_switch__Syms()
{
}

Vdual_control_switch__Syms::Vdual_control_switch__Syms(VerilatedContext* contextp, const char* namep, Vdual_control_switch* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
}

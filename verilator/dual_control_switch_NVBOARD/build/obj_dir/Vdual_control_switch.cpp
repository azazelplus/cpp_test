// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vdual_control_switch.h"
#include "Vdual_control_switch__Syms.h"

//============================================================
// Constructors

Vdual_control_switch::Vdual_control_switch(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vdual_control_switch__Syms(contextp(), _vcname__, this)}
    , a{vlSymsp->TOP.a}
    , b{vlSymsp->TOP.b}
    , f{vlSymsp->TOP.f}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vdual_control_switch::Vdual_control_switch(const char* _vcname__)
    : Vdual_control_switch(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vdual_control_switch::~Vdual_control_switch() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vdual_control_switch___024root___eval_debug_assertions(Vdual_control_switch___024root* vlSelf);
#endif  // VL_DEBUG
void Vdual_control_switch___024root___eval_static(Vdual_control_switch___024root* vlSelf);
void Vdual_control_switch___024root___eval_initial(Vdual_control_switch___024root* vlSelf);
void Vdual_control_switch___024root___eval_settle(Vdual_control_switch___024root* vlSelf);
void Vdual_control_switch___024root___eval(Vdual_control_switch___024root* vlSelf);

void Vdual_control_switch::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vdual_control_switch::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vdual_control_switch___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vdual_control_switch___024root___eval_static(&(vlSymsp->TOP));
        Vdual_control_switch___024root___eval_initial(&(vlSymsp->TOP));
        Vdual_control_switch___024root___eval_settle(&(vlSymsp->TOP));
    }
    // MTask 0 start
    VL_DEBUG_IF(VL_DBG_MSGF("MTask0 starting\n"););
    Verilated::mtaskId(0);
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vdual_control_switch___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfThreadMTask(vlSymsp->__Vm_evalMsgQp);
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vdual_control_switch::eventsPending() { return false; }

uint64_t Vdual_control_switch::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vdual_control_switch::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vdual_control_switch___024root___eval_final(Vdual_control_switch___024root* vlSelf);

VL_ATTR_COLD void Vdual_control_switch::final() {
    Vdual_control_switch___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vdual_control_switch::hierName() const { return vlSymsp->name(); }
const char* Vdual_control_switch::modelName() const { return "Vdual_control_switch"; }
unsigned Vdual_control_switch::threads() const { return 1; }

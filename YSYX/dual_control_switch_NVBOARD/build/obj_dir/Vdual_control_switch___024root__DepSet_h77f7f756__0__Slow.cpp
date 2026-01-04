// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdual_control_switch.h for the primary calling header

#include "verilated.h"

#include "Vdual_control_switch__Syms.h"
#include "Vdual_control_switch___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vdual_control_switch___024root___dump_triggers__stl(Vdual_control_switch___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vdual_control_switch___024root___eval_triggers__stl(Vdual_control_switch___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vdual_control_switch__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdual_control_switch___024root___eval_triggers__stl\n"); );
    // Body
    vlSelf->__VstlTriggered.at(0U) = (0U == vlSelf->__VstlIterCount);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vdual_control_switch___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

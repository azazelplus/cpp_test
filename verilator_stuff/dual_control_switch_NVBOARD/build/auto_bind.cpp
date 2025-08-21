#include <nvboard.h>
#include "Vdual_control_switch.h"

void nvboard_bind_all_pins(Vdual_control_switch* top) {
	nvboard_bind_pin( &top->a, 1, SW0);
	nvboard_bind_pin( &top->b, 1, SW1);
	nvboard_bind_pin( &top->f, 1, LD0);
}

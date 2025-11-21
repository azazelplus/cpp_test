#include <nvboard.h>
#include "Vtop.h"

void nvboard_bind_all_pins(Vtop* top) {
	nvboard_bind_pin( &top->BTNC, 1, BTNC);
	nvboard_bind_pin( &top->SW0, 1, SW0);
	nvboard_bind_pin( &top->SEG0A, 1, SEG0A);
	nvboard_bind_pin( &top->SEG0B, 1, SEG0B);
	nvboard_bind_pin( &top->SEG0C, 1, SEG0C);
	nvboard_bind_pin( &top->SEG0D, 1, SEG0D);
	nvboard_bind_pin( &top->SEG0E, 1, SEG0E);
	nvboard_bind_pin( &top->SEG0F, 1, SEG0F);
	nvboard_bind_pin( &top->SEG0G, 1, SEG0G);
	nvboard_bind_pin( &top->DEC0P, 1, DEC0P);
	nvboard_bind_pin( &top->SEG1A, 1, SEG1A);
	nvboard_bind_pin( &top->SEG1B, 1, SEG1B);
	nvboard_bind_pin( &top->SEG1C, 1, SEG1C);
	nvboard_bind_pin( &top->SEG1D, 1, SEG1D);
	nvboard_bind_pin( &top->SEG1E, 1, SEG1E);
	nvboard_bind_pin( &top->SEG1F, 1, SEG1F);
	nvboard_bind_pin( &top->SEG1G, 1, SEG1G);
	nvboard_bind_pin( &top->DEC1P, 1, DEC1P);
}

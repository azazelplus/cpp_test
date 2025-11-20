#include <nvboard.h>
#include "Vtop.h"

void nvboard_bind_all_pins(Vtop* top) {
	nvboard_bind_pin( &top->SW0, 1, SW0);
	nvboard_bind_pin( &top->SW1, 1, SW1);
	nvboard_bind_pin( &top->SW2, 1, SW2);
	nvboard_bind_pin( &top->SW3, 1, SW3);
	nvboard_bind_pin( &top->SW4, 1, SW4);
	nvboard_bind_pin( &top->SW5, 1, SW5);
	nvboard_bind_pin( &top->SW6, 1, SW6);
	nvboard_bind_pin( &top->SW7, 1, SW7);
	nvboard_bind_pin( &top->SW8, 1, SW8);
	nvboard_bind_pin( &top->SEG0A, 1, SEG0A);
	nvboard_bind_pin( &top->SEG0B, 1, SEG0B);
	nvboard_bind_pin( &top->SEG0C, 1, SEG0C);
	nvboard_bind_pin( &top->SEG0D, 1, SEG0D);
	nvboard_bind_pin( &top->SEG0E, 1, SEG0E);
	nvboard_bind_pin( &top->SEG0F, 1, SEG0F);
	nvboard_bind_pin( &top->SEG0G, 1, SEG0G);
	nvboard_bind_pin( &top->DEC0P, 1, DEC0P);
}

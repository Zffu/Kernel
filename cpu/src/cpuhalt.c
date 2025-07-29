#include <cpuhalt.h>
#include <pit.h>
#include <isr.h>

#include <stdbool.h>

volatile bool cpu_is_halted = false;
volatile uint64_t halt_total_ticks = 0;
volatile uint64_t halt_idle_ticks = 0;

static void cpuhalt_timercallback(registers_t reg) {
	++halt_total_ticks;
	if(cpu_is_halted) ++halt_idle_ticks;
}

void cpuhalt_idle_loop() {
	while(1) {
		cpu_is_halted = true;
		asm volatile("hlt");
		cpu_is_halted = false;
	}
}

void cpuhalt_init() {
	pit_inittimer(HALTING_HZ, cpuhalt_timercallback);
}

void cpuhalt_gather_stats(cpu_halt_stats* statptr) {
	statptr->idle_ticks = halt_idle_ticks;
	statptr->total_ticks = halt_total_ticks;

	halt_idle_ticks = 0;
	halt_total_ticks = 0;
}


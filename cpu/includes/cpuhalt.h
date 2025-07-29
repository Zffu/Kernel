/**
 * CPU halting & idle
 */

#pragma once

#define HALTING_HZ 100

#include <stdint.h>

typedef struct cpu_halt_stats {
	volatile uint64_t total_ticks;
	volatile uint64_t idle_ticks;
} cpu_halt_stats;

void cpuhalt_init();

void cpuhalt_idle_loop();

void cpuhalt_gather_stats(cpu_halt_stats* statptr);


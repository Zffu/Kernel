#pragma once

#include <types.h>

typedef void (*pit_callback_f)(registers_t regs);

void pit_inittimer(u32 freq, pit_callback_f callback);
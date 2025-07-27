#pragma once

#include <types.h>

#define KERNEL_CS 0x08

typedef struct idt_gate_t {
	u16 low_off;
	u16 sel;
	u8 always0;
	u8 flags;
	u16 high_off;
} __attribute__((packed)) idt_gate_t;

typedef struct idt_reg_t {
	u16 limit;
	u32 base;
} __attribute((packed)) idt_reg_t;

#define IDT_ENTRIES 256

void set_idt_gate(int n, u32 handler);
void set_idt();
#include <screenprint.h>

#include <isr.h>
#include <keyboard/keyboard.h>

void main() {
	screenprint("[INFO] Installing the CPU ISR\n");
	isr_install();

	screenprint("[INFO] Loading IRQs\n\n");
	irq_install();

	__asm__ __volatile__("int $0x21");
}

void user_input(char* i) {
	
}
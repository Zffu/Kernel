#include <screenprint.h>

#include <isr.h>
#include <keyboard/keyboard.h>

void main() {
	screenprint("[INFO] Installing the CPU ISR\n");
	isr_install();

	screenprint("[INFO] Loading IRQs\n\n");
	irq_install();
}

void user_input(char* i) {
	
}
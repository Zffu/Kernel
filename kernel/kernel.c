#include <screenprint.h>

#include <isr.h>
#include <keyboard/keyboard.h>

void main() {
	screenprint("[INFO] Installing the CPU ISR\n");
	isr_install();

	screenprint("[INFO] Loading Keyboard handler\n\n");
	keyboard_init();
}
#include <screenprint.h>

#include <isr.h>
#include <ps2kbdold.h>
#include <ps2kbd.h>

void main() {
	clearscreen();
	
	screenprint("[INFO] Installing the CPU ISR\n");
	isr_install();

	asm volatile("sti");
	ps2kbd_load();
	screenlog("Loaded ps2kbd driver");

	__asm__ __volatile__("int $0x21");	
}

void user_input(char* i) {
	
}
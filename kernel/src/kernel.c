#include <screenprint.h>

#include <isr.h>
#include <ps2kbdold.h>
#include <ps2kbd.h>

#include <input/inputstream.h>

void main() {
	clearscreen();
	
	screenprint("[INFO] Installing the CPU ISR\n");
	isr_install();

	asm volatile("sti");
	ps2kbd_load();
	screenlog("Loaded ps2kbd driver");

	__asm__ __volatile__("int $0x21");	
}

void userinput_finish(char* buff) {
	screenlog("> ");
	screenprint(buff);
}

void userinput_push(char c) {
	screenprint((char*){c});
}

inputstream_t inputstream = {
	.buff = {0},
	.sz = 0,
	.user_finish = userinput_finish,
	.user_push = userinput_push
};


inputstream_t* kbd_input_stream() {
	return &inputstream;
}
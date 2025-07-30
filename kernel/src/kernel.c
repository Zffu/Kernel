#include <screenprint.h>

#include <isr.h>
#include <ps2kbd.h>

#include <cpuhalt.h>

#include <input/inputstream.h>

#include <keyboard/keyboard.h>

#include <str.h>


volatile keycode scancode_map_set51[256] __attribute__((used)) = {
    [0x10] = KEY_Q,
};



void main() {

	clearscreen();


	char b[50];
	int_to_ascii(scancode_map_set51[0x10], b);
	screenprint(b);
	screenprint("\n");

	screenprint("[INFO] Installing the CPU ISR\n");
	isr_install();

	asm volatile("sti");
	ps2kbd_load();
	screenlog("Loaded ps2kbd driver");

	__asm__ __volatile__("int $0x21");	

	screenlog("Enabling CPU halting");
	cpuhalt_init();

	cpuhalt_idle_loop();
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
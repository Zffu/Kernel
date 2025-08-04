#include <eventio.h>
#include <taskio/taskio.h>
#include <keyboard/keyboard.h>
#include <keyboard/layout.h>

#include <str.h>

#include <shell/kshell.h>
#include <screenprint.h>

extern internal_task_t* taskio_internaltask_queue;

char kshell_line_buff[256] = {0};
int kshell_buff_sz = 0;

void kshell_start_sess() {
	eventio_register(KBDKEY_PRESS, kshell_kbd_callback);
	kshell_print_userinput_line();
}

void kshell_kbd_callback(int val) {
	if(val == KEY_ENTER || val == KEY_KP_ENTER) {
		kshell_process_entry();
		kshell_print_userinput_line();

		kshell_buff_sz = 0;
	}

	if(val == KEY_BACKSPACE && kshell_buff_sz > 0) {
		kshell_buff_sz--;
		kshell_line_buff[kshell_buff_sz] = '\0';

		screenbackspace();
	}

	else if(val >= WRITABLE_KEY_START && val <= WRITABLE_KEY_END) {
		kbd_state_t state = {
			.alt_gr = keyboard_iskeypressed(KEY_RALT),
			.caps_lock = keyboard_iskeypressed(KEY_CAPSLOCK),
			.ctrl = keyboard_iskeypressed(KEY_LCTRL) || keyboard_iskeypressed(KEY_RCTRL),
			.shift = keyboard_iskeypressed(KEY_RSHIFT) || keyboard_iskeypressed(KEY_LSHIFT)
		};

		char c = kbd_translate_keycode(val, state, kbdhandler_azerty, AZERTY);

		kshell_line_buff[kshell_buff_sz] = c;
		++kshell_buff_sz;

		screenprint_char_at(c, -1, -1);
	}
}

void kshell_print_userinput_line() {
	screenprint("\n");
	screenprint("* root@kernel: $");
}

void kshell_process_entry() {
	char* args[32] = {0};
	int arg_sz = 0;

	str_split(kshell_line_buff, ' ', args, &arg_sz);

	if(strcmp(kshell_line_buff, "taskio")) {
		if(strcmp(args[0], "list")) {
			screenprint("\nTaskIO running tasks (Internal):\n");

			internal_task_t* n = taskio_internaltask_queue;

			while(n != 0) {
				screenprint("- ");
				screenprint(n->name);
				screenprint(" INTERNALTASK DETACHABLE\n");

				n = n->next;
			}
		} else if(strcmp(args[0], "detach")) {
			internal_task_t* n = taskio_internaltask_queue;

			while(n != 0) {
				if(strcmp(n->name, args[1])) {
					n->detatch();
					break;
				}
			}

			screenprint("\nInternal Task ");
			screenprint(args[1]);
			screenprint(" was detached if it was active!");
		}
	}
}
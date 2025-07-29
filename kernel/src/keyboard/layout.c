#include <keyboard/layout.h>
#include <keyboard/keyboard.h>

kbd_textpair common_kbd_texttable[] = {
	[KEY_0] = {0, '0'}, [KEY_1] = {0, '1'},
	[KEY_2] = {0, '2'}, [KEY_3] = {0, '3'},
	[KEY_4] = {0, '4'}, [KEY_5] = {0, '5'},
	[KEY_6] = {0, '6'}, [KEY_7] = {0, '7'},
	[KEY_8] = {0, '8'}, [KEY_9] = {0, '9'},
    [KEY_A] = { 'a', 'A' }, [KEY_B] = { 'b', 'B' },
    [KEY_C] = { 'c', 'C' }, [KEY_D] = { 'd', 'D' },
    [KEY_E] = { 'e', 'E' }, [KEY_F] = { 'f', 'F' },
    [KEY_G] = { 'g', 'G' }, [KEY_H] = { 'h', 'H' },
    [KEY_I] = { 'i', 'I' }, [KEY_J] = { 'j', 'J' },
    [KEY_K] = { 'k', 'K' }, [KEY_L] = { 'l', 'L' },
    [KEY_M] = { 'm', 'M' }, [KEY_N] = { 'n', 'N' },
    [KEY_O] = { 'o', 'O' }, [KEY_P] = { 'p', 'P' },
    [KEY_Q] = { 'q', 'Q' }, [KEY_R] = { 'r', 'R' },
    [KEY_S] = { 's', 'S' }, [KEY_T] = { 't', 'T' },
    [KEY_U] = { 'u', 'U' }, [KEY_V] = { 'v', 'V' },
    [KEY_W] = { 'w', 'W' }, [KEY_X] = { 'x', 'X' },
    [KEY_Y] = { 'y', 'Y' }, [KEY_Z] = { 'z', 'Z' },
};

char kbdhandler_qwerty(keycode code, kbd_state_t state){
	bool up = state.caps_lock || state.shift;
	
	if(!up && code >= KEY_1 && code <= KEY_0) {
		char numkey[10] = "!@#$%^&.()";

		return numkey[code - KEY_1];
	}
	
	return 0;
}

char kbdhandler_azerty(keycode code, kbd_state_t state) {
	bool up = state.caps_lock || state.shift;

	if(!up && code >= KEY_1 && code <= KEY_0) {
		char numkey[10] = "&é\"\'(-è_çà";

		return numkey[code - KEY_1];
	}
	
	return 0;
}

char kbd_translate_keycode(keycode code, kbd_state_t state, kbd_layout_charhandler handler, kbd_layout_t layout) {

	/**
	 * Quick adaptations to avoid using the handler for everything
	 */

	if(layout == AZERTY) {
		switch(code) {
			case KEY_A:
				code = KEY_Q;
				break;
			case KEY_Q:
				code = KEY_A;
				break;
			case KEY_W:
				code = KEY_Z;
				break;	
		}
	}

	if(handler) {
		char c = handler(code, state);
		if(c != 0x00) return c;
	}

	if(code >= KEY_KP_1 && code <= KEY_KP_9) {
		code = code - (KEY_KP_1 - KEY_1);
	}


	kbd_textpair pair = common_kbd_texttable[code];

	return (state.shift || state.caps_lock) ? pair.upper : pair.lower;
}
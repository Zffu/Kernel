#include <keyboard/keyboard.h>
#include <types.h>

#include <screenprint.h>

#include <keyboard/layout.h>
#include <kernel.h>


u8 kb_bitmask[14] = {0};

/**
 * @name keyboard_handlekeypress
 * 
 * Handles when a key is pressed.
 * 
 * @param code the internal keycode
 */
void keyboard_handlekeypress(keycode code) {
	kb_bitmask[code / 8] |= (1U << code % 8);

	if(code == KEY_BACKSPACE) {
		screenbackspace();
	}
	else if(code == KEY_ENTER || code == KEY_KP_ENTER) {
		inputstream_flush(kbd_input_stream());
	}
	else {

		kbd_state_t state = {
			.alt_gr = keyboard_iskeypressed(KEY_RALT),
			.caps_lock = keyboard_iskeypressed(KEY_CAPSLOCK),
			.ctrl = keyboard_iskeypressed(KEY_LCTRL) || keyboard_iskeypressed(KEY_RCTRL),
			.shift = keyboard_iskeypressed(KEY_RSHIFT) || keyboard_iskeypressed(KEY_LSHIFT)
		};

		if(code >= WRITABLE_KEY_START && code <= WRITABLE_KEY_END) {
			screenprint("sending key\n");
			inputstream_push(kbd_translate_keycode(code, state, kbdhandler_qwerty, AZERTY), kbd_input_stream());
		}
	}
}

/**
 * @name keyboard_handlekeyrelease
 * 
 * Handles when a key is released
 * 
 * @param code the internal keycode
 */
void keyboard_handlekeyrelease(keycode code) {
	kb_bitmask[code / 8] &= ~(1U << code % 8);
}

/**
 * @name keyboard_iskeypressed
 * 
 * Returns whenever the given keycode is being pressed or not.
 * 
 * @param code the internal keycode.
 * 
 * @return true or false.
 */
bool keyboard_iskeypressed(keycode code) {
	return (kb_bitmask[code / 8] >> code % 8) & 1 == 1;
}
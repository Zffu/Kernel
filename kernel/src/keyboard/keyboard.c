#include <keyboard/keyboard.h>
#include <types.h>

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
/**
 * Keyboard commons for the Kernel, basically allows for multiple "drivers" to be treated the same.
 */

#pragma once

typedef enum keycode {
	ESCAPE,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	PRINT_SCREEN,
	STOP_SCROLL,
	PAUSE,

	KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_PAREN, KEY_BRACKETS,

	NUMKEY_0, NUMKEY_1, NUMKEY_2, NUMKEY_3, NUMKEY_4, NUMKEY_5, NUMKEY_6, NUMKEY_7, NUMKEY_8, NUMKEY_9,
	LOCK_NUM,
	DIVIDE_NUM,
	MULTIPLY_NUM,
	MINUS_NUM,
	PLUS_NUM,
	ENTER_NUM,
	DOT,

	ARROW_UP,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT,

	TAB,
	LOCK_MAJ,
	SHIFT,
	SHIFT_LEFT,
	CONTROL,
	MENU_KEY,
	ALT,
	SPACE,
	ALT_LEFT,
	FN, 
	LIST,
	CONTROL_LEFT,
	ENTER,
	DELETE,
	
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X, 
	KEY_Y,
	KEY_Z,

	/**
	 * The > key
	 */
	SPECIAL_1,

	/**
	 * The question mark key
	 */
	SPECIAL_2,

	/**
	 * The dot & ; key
	 */
	SPECIAL_3,

	/**
	 * The slash key
	 */
	SPECIAL_4,

	/**
	 * Exclamation point key
	 */
	SPECIAL_5,

	/**
	 * ^ key
	 */
	SPECIAL_6,

	/**
	 * Dollar sing key
	 */
	SPECIAL_7,

	/**
	 * Star key
	 */
	SPECIAL_8,

	/**
	 * Percent key
	 */
	SPECIAL_9

} keycode;

/**
 * @name keyboard_handlekeypress
 * 
 * Handles when a key is pressed.
 */
void keyboard_handlekeypress(keycode code);

/**
 * @name keyboard_handlekeyrelease
 * 
 * Handles when a key is released
 */
void keyboard_handlekeyrelease(keycode code);
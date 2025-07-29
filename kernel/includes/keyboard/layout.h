/**
 * Keyboard layout handling
 */

#include <keyboard/keyboard.h>
#include <types.h>

#pragma once



typedef enum kbd_layout_t {
	QWERTY,
	AZERTY
} kbd_layout_t;

typedef struct kbd_textpair {
	char lower;
	char upper;
} kbd_textpair;

typedef char (*kbd_layout_charhandler)(keycode code, kbd_state_t state);

char kbd_translate_keycode(keycode code, kbd_state_t state, kbd_layout_charhandler handler, kbd_layout_t layout);

char kbdhandler_qwerty(keycode code, kbd_state_t state);
char kbdhandler_azerty(keycode code, kbd_state_t state);
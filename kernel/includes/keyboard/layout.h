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

keycode get_keycode_layout_ps2kbd(u8 scancode, kbd_layout_t layout);

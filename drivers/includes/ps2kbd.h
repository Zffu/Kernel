/**
 * PS/2 Keyboard driver
 */

#pragma once

#include <stdbool.h>

/**
 * LEDs bits
 */
#define PS2KBD_LED_LOCK_SCROLL 0
#define PS2KBD_LED_NUMBER_LOCK 1
#define PS2KBD_LED_CAPS_LOCK 2

typedef struct ps2kbd_led_state {
	bool lock_scroll;
	bool number_lock;
	bool caps_lock;
} ps2kbd_led_state_t;

void ps2kbd_set_led_state(int led, bool state);
void ps2kbd_push_led_state(ps2kbd_led_state_t ledstate);
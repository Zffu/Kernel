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

typedef enum ps2kbd_scanmode_t {
	TYPEMATIC_AUTOREPEAT,
	PRESS_RELEASE,
	PRESS,
	ALL
} ps2kbd_scanmode_t;

/**
 * @name ps2kbd_set_led_state 
 * 
 * Sends a single LED state update to the PS/2 keyboard.
 * 
 * @param led the LED bit, found in the PS2KBD_LED_* defines
 * @param state the state, if lit, true if not false
 */
void ps2kbd_set_led_state(int led, bool state);

/**
 * @param ps2kbd_push_led_state
 * 
 * Sends a batch LED update to the PS/2 keyboard.
 * 
 * @param ledstate the state structure.
 */
void ps2kbd_push_led_state(ps2kbd_led_state_t ledstate);

/**
 * @param ps2kbd_echo
 * 
 * Sends an echo packet to the PS/2 keyboard.
 * 
 * @return true if the keyboard echoed back, false if it didn't
 */
bool ps2kbd_echo();

/**
 * @name ps2kbd_enable_scanning
 * 
 * Enable the keyboard key scanning.
 */
void ps2kbd_enable_scanning();

/**
 * @name ps2kbd_disable_scanning
 * 
 * Disables the kayboard key scanning
 */
void ps2kbd_disable_scanning();

/**
 * @name ps2kbd_set_default_params
 * 
 * Resets the keyboard parameters to default
 */
void ps2kbd_set_default_params();

/**
 * @name ps2kbd_set_scanmode_global
 * 
 * Sets the scanning mode globally.
 * 
 * @param mode the given mode
 */
void ps2kbd_set_scanmode_global(ps2kbd_scanmode_t mode);

/**
 * @name ps2kbd_set_scanmode_key
 * 
 * Sets the scanning mode for a specific key
 * 
 * @param mode the given mode
 * @param key the key's scan code (must be from the )
 */
void ps2kbd_set_scanmode_key(ps2kbd_scanmode_t mode, unsigned char key);

/**
 * @name ps2kbd_set_typematic_rate_delay
 * 
 * Sets the repeat rate and the delay before keys are repeated.
 * 
 * @param repeat_rate the repeat rate in Hz.
 * @param delays_before_key_repeat the delays in miliseconds before the key repeat
 */
void ps2kbd_set_typematic_rate_delay(int repeat_rate, int delays_before_key_repeat);

/**
 * @name get_current_scancode_set
 * 
 * Gets the current scan code set.
 * 
 * @return the scan code set, either 1, 2 or 3
 */
int get_current_scancode_set();
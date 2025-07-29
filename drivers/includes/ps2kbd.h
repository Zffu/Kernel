/**
 * PS/2 Keyboard driver
 */

#pragma once

#include <stdbool.h>

#define PS2KBD_DATAPORT 0x60
#define PS2KBD_COMMANDPORT 0x64

/**
 * Layout-dependant keys
 */
#define KEYCODE_A 0x1C
#define KEYCODE_Q 0x15
#define KEYCODE_W 0x1D
#define KEYCODE_Z 0x1A
#define KEYCODE_M 0x3A
#define KEYCODE_SEMICOLON 0x4C
#define KEYCODE_APOSTROPHE 0x52
#define KEYCODE_GRAVE 0x0E
#define KEYCODE_MINUS 0x4E
#define KEYCODE_EQUAL 0x55
#define KEYCODE_COMMA 0x41
#define KEYCODE_DOT 0x49
#define KEYCODE_Y 0x35
#define KEYCODE_SLASH 0x4A
#define KEYCODE_LBRACKET 0x54
#define KEYCODE_RBRACKET 0x5B
#define KEYCODE_BACKSLASH 0x5D


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

bool ps2kbd_ack();

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

/**
 * @name ps2kbd_load
 * 
 * Loads the ps2kbd driver.
 */
void ps2kbd_load();
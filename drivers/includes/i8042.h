/**
 * Controller for the PS/2 stuff
 */

#pragma once

#include <stdbool.h>

#define I8042_COMMAND_PORT 0x64
#define I8042_DATA_PORT 0x60

/**
 * @name i8042_wait_input_buffempty
 * 
 * Waits for the COMMAND port to be ready
 */
void i8042_wait_input_buffempty();

/**
 * @name i8042_wait_output_bufferfull
 * 
 * Waits for the output buffer to be full.
 */
void i8042_wait_output_bufferfull();

/**
 * @name i8042_enable_keyboard_port
 * 
 * Enables the keyboard PS/2 port
 */
void i8042_enable_keyboard_port();

/**
 * @name i8042_iskeyboard_translated
 * 
 * Is the PS/2 keyboard translated into set 1
 */
bool i8042_iskeyboard_translated();
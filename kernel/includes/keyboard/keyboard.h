/**
 * Keyboard commons for the Kernel, basically allows for multiple "drivers" to be treated the same.
 */

#pragma once

typedef int keycode;

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
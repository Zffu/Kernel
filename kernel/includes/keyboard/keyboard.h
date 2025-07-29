/**
 * Keyboard commons for the Kernel, basically allows for multiple "drivers" to be treated the same.
 */

#pragma once

/**
 * Untranslated keycodes, refer to QWERTY positions
 */
typedef enum keycode {
    KEY_NONE = 0,
    KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I,
    KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R,
    KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

    KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,

    KEY_ENTER, KEY_ESC, KEY_BACKSPACE, KEY_TAB, KEY_SPACE,
    KEY_MINUS, KEY_EQUAL, KEY_LBRACKET, KEY_RBRACKET,
    KEY_BACKSLASH, KEY_SEMICOLON, KEY_APOSTROPHE,
    KEY_GRAVE, KEY_COMMA, KEY_DOT, KEY_SLASH,

    KEY_CAPSLOCK,

    KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6,
    KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12,

    KEY_PRINT_SCREEN, KEY_SCROLL_LOCK, KEY_PAUSE,
    KEY_INSERT, KEY_HOME, KEY_PAGE_UP,
    KEY_DELETE, KEY_END, KEY_PAGE_DOWN,
    KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP,

    KEY_NUMLOCK, KEY_KP_DIVIDE, KEY_KP_MULTIPLY, KEY_KP_SUBTRACT,
    KEY_KP_ADD, KEY_KP_ENTER, KEY_KP_1, KEY_KP_2, KEY_KP_3,
    KEY_KP_4, KEY_KP_5, KEY_KP_6, KEY_KP_7, KEY_KP_8, KEY_KP_9, KEY_KP_0, KEY_KP_DOT,

    KEY_LCTRL, KEY_LSHIFT, KEY_LALT, KEY_LGUI,
    KEY_RCTRL, KEY_RSHIFT, KEY_RALT, KEY_RGUI,
    KEY_APPS,

    KEY_UNKNOWN
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
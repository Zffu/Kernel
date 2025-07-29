#include <ps2kbd.h>
#include <driver.h>

#include <str.h>

#include <keyboard/layout.h>

#include <cpuhalt.h>

#include <isr.h>

#include <screenprint.h>

keycode scancode_map[256] = {
    [0x1C] = KEY_A, [0x32] = KEY_B, [0x21] = KEY_C, [0x23] = KEY_D,
    [0x24] = KEY_E, [0x2B] = KEY_F, [0x34] = KEY_G, [0x33] = KEY_H,
    [0x43] = KEY_I, [0x3B] = KEY_J, [0x42] = KEY_K, [0x4B] = KEY_L,
    [0x3A] = KEY_M, [0x31] = KEY_N, [0x44] = KEY_O, [0x4D] = KEY_P,
    [0x15] = KEY_Q, [0x2D] = KEY_R, [0x1B] = KEY_S, [0x2C] = KEY_T,
    [0x3C] = KEY_U, [0x2A] = KEY_V, [0x1D] = KEY_W, [0x22] = KEY_X,
    [0x35] = KEY_Y, [0x1A] = KEY_Z,

    [0x16] = KEY_1, [0x1E] = KEY_2, [0x26] = KEY_3, [0x25] = KEY_4,
    [0x2E] = KEY_5, [0x36] = KEY_6, [0x3D] = KEY_7, [0x3E] = KEY_8,
    [0x46] = KEY_9, [0x45] = KEY_0,

    [0x5A] = KEY_ENTER, [0x76] = KEY_ESC, [0x66] = KEY_BACKSPACE, [0x0D] = KEY_TAB,
    [0x29] = KEY_SPACE, [0x4E] = KEY_MINUS, [0x55] = KEY_EQUAL,
    [0x54] = KEY_LBRACKET, [0x5B] = KEY_RBRACKET, [0x5D] = KEY_BACKSLASH,
    [0x4C] = KEY_SEMICOLON, [0x52] = KEY_APOSTROPHE, [0x0E] = KEY_GRAVE,
    [0x41] = KEY_COMMA, [0x49] = KEY_DOT, [0x4A] = KEY_SLASH,

    [0x58] = KEY_CAPSLOCK,

    [0x05] = KEY_F1, [0x06] = KEY_F2, [0x04] = KEY_F3, [0x0C] = KEY_F4,
    [0x03] = KEY_F5, [0x0B] = KEY_F6, [0x83] = KEY_F7, [0x0A] = KEY_F8,
    [0x01] = KEY_F9, [0x09] = KEY_F10, [0x78] = KEY_F11, [0x07] = KEY_F12,

    [0x14] = KEY_LCTRL, [0x12] = KEY_LSHIFT, [0x11] = KEY_LALT, [0x59] = KEY_RSHIFT,

    [0x77] = KEY_NUMLOCK, [0x7C] = KEY_KP_MULTIPLY, [0x7B] = KEY_KP_SUBTRACT,
    [0x79] = KEY_KP_ADD, [0x70] = KEY_KP_0, [0x69] = KEY_KP_1,
    [0x72] = KEY_KP_2, [0x7A] = KEY_KP_3, [0x6B] = KEY_KP_4,
    [0x73] = KEY_KP_5, [0x74] = KEY_KP_6, [0x6C] = KEY_KP_7,
    [0x75] = KEY_KP_8, [0x7D] = KEY_KP_9, [0x71] = KEY_KP_DOT
};

keycode scancode_e0_map[256] = {
    [0x11] = KEY_RALT, [0x14] = KEY_RCTRL,
    [0x1F] = KEY_LGUI, [0x27] = KEY_RGUI, [0x2F] = KEY_APPS,

    [0x4A] = KEY_KP_DIVIDE, [0x5A] = KEY_KP_ENTER,
    [0x6B] = KEY_LEFT, [0x6C] = KEY_HOME, [0x6D] = KEY_PAGE_UP,
    [0x69] = KEY_END, [0x71] = KEY_DELETE, [0x70] = KEY_INSERT,
    [0x72] = KEY_DOWN, [0x74] = KEY_RIGHT, [0x75] = KEY_UP,
    [0x7A] = KEY_PAGE_DOWN, [0x7D] = KEY_PAGE_UP
};

bool isBreakMode = false;
bool hasE0Prefix = false;

bool ps2kbd_ack() {
	while(!(port_get_byte(0x64) & 0x01));
	return port_get_byte(0x60) == 0xFA;
}

/**
 * @name ps2kbd_set_led_state 
 * 
 * Sends a single LED state update to the PS/2 keyboard.
 * 
 * @param led the LED bit, found in the PS2KBD_LED_* defines
 * @param state the state, if lit, true if not false
 */
void ps2kbd_set_led_state(int led, bool state) {
	port_put_byte(0x60, 0xED);
	port_put_byte(0x60, (1 << led));
	ps2kbd_ack();
}

void ps2kbd_push_led_state(ps2kbd_led_state_t state) {
	port_put_byte(0x60, 0xED);
	int i = 0;

	if(state.caps_lock) i |= (1 << PS2KBD_LED_CAPS_LOCK);
	if(state.lock_scroll) i |= (1 << PS2KBD_LED_LOCK_SCROLL);
	if(state.number_lock) i |= (1 << PS2KBD_LED_NUMBER_LOCK);

	port_put_byte(0x60, i);
	ps2kbd_ack();
}

/**
 * @param ps2kbd_echo
 * 
 * Sends an echo packet to the PS/2 keyboard.
 * 
 * @return true if the keyboard echoed back, false if it didn't
 */
bool ps2kbd_echo() {
	port_put_byte(0x60, 0xEE);
	while (!(port_get_byte(0x64) & 0x01));
	screendebug("It ended");
	return port_get_byte(0x60) == 0xEE;
}

/**
 * @name ps2kbd_enable_scanning
 * 
 * Enable the keyboard key scanning.
 */
void ps2kbd_enable_scanning() {
	port_put_byte(0x60, 0xF4);
}

/**
 * @name ps2kbd_disable_scanning
 * 
 * Disables the kayboard key scanning
 */
void ps2kbd_disable_scanning() {
	port_put_byte(0x60, 0xF5);
}


static void ps2kbd_callback(registers_t regs) {
	if (!(port_get_byte(0x64) & 0x1)) return;

	u8 scancode = port_get_byte(0x60);

	/**
	 * Check for bounds.
	 */
	//if(hasE0Prefix && scancode > 125) return;
	//if(!hasE0Prefix && scancode > 0x83) return;

	if(scancode == 0xFF) return;

	if(scancode == 0xF0) {
		isBreakMode = true;
		return;
	}

	if(scancode == 0xE0) {
		hasE0Prefix = true;
		return;
	}

	if(!isBreakMode && scancode & 0x80) {
		isBreakMode = true;
		scancode &= 0x7F;
	}

	char b[32] = {0};
	byte_to_hex(scancode, b);

	screenprint("Key: 0x");
	screenprint(b);
	screenprint("\n");

	if(scancode == 0x10) {
		cpu_halt_stats stats;
		cpuhalt_gather_stats(&stats);
		char b[32] = {0};

		screenprint("CPU Idle ticks: ");
		int_to_ascii(stats.idle_ticks, b);
		screenprint(b);

		screenprint("\nCPU Busy ticks: ");
		int_to_ascii(stats.total_ticks - stats.idle_ticks, b);
		screenprint(b);

		screenprint("\nCPU Total ticks: ");
		int_to_ascii(stats.total_ticks, b);
		screenprint(b);

		screenprint("\nCPU usage: ");
		float_to_string(100.0f * (1.0f - ((float)stats.idle_ticks / stats.total_ticks)), b, 5);
		screenprint(b);
		screenprint("%\n");
	}
	
	keycode code = (hasE0Prefix) ? scancode_e0_map[scancode] : scancode_map[scancode];

	if(!isBreakMode) keyboard_handlekeypress(code);
	else keyboard_handlekeyrelease(code);

	isBreakMode = false;
	hasE0Prefix = false;
}

/**
 * @name ps2kbd_load
 * 
 * Loads the ps2kbd driver.
 */
void ps2kbd_load() {
#ifndef PS2KBD_FAST
	while(port_get_byte(0x64) & 0x2);
	screendebug("PS/2 controller ready");

	while(port_get_byte(0x64) & 0x1) {
		port_get_byte(0x60);
	}
	screendebug("Flushed ps2kbd IO");
#endif

	port_put_byte(0x64, 0xAE);
	screendebug("Enabled keyboard PS/2 port");

	port_put_byte(0x60, 0xF0);
	port_put_byte(0x60, 0x02);
	//screendebug("Defined ps2kbd scan layout to standart");

	port_put_byte(0x60, 0xF0);
	port_put_byte(0x60, 0x00);
	while(port_get_byte(0x60) != 0xFA);

	u8 scancode = port_get_byte(0x60);

	switch(scancode) {
		case 0x43:
			screendebug("1");
			break;
		case 0x41:
			screendebug("2");
			break;
		case 0x3F:
			screendebug("3");
			break;
		default:
			char e[6];
			int_to_ascii(scancode, e);
			screenprint(e);
	}

	ps2kbd_enable_scanning();
	screendebug("Enabled ps2kbd scanning");



	while(port_get_byte(0x64) & 0x2);
	port_put_byte(0x64, 0x20);

	while(!(port_get_byte(0x64) & 0x1));
	u8 command = port_get_byte(0x60);

	if((command & 0x40) != 0) {
		screendebug("ps2kbd translation to set 1 is enabled!");
	}
	else {
		screendebug("translations are disabled!");
	}

	command &= ~0x40;

	

	register_interrupt_handler(IRQ1, ps2kbd_callback);

#ifndef PS2KBD_FAST
	while((port_get_byte(0x64) & 2) != 0);
	port_put_byte(0x60, 0xF4);
#endif
}
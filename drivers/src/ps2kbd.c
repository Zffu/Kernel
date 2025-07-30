#include <ps2kbd.h>
#include <i8042.h>
#include <driver.h>

#include <str.h>

#include <keyboard/layout.h>

#include <cpuhalt.h>

#include <isr.h>

#include <screenprint.h>

static keycode scancode_map_set1[256] = {
    [0x01] = KEY_ESC,
    [0x02] = KEY_1, [0x03] = KEY_2, [0x04] = KEY_3, [0x05] = KEY_4,
    [0x06] = KEY_5, [0x07] = KEY_6, [0x08] = KEY_7, [0x09] = KEY_8,
    [0x0A] = KEY_9, [0x0B] = KEY_0, [0x0C] = KEY_MINUS, [0x0D] = KEY_EQUAL,
    [0x0E] = KEY_BACKSPACE, [0x0F] = KEY_TAB,

    [0x10] = KEY_Q, [0x11] = KEY_W, [0x12] = KEY_E, [0x13] = KEY_R,
    [0x14] = KEY_T, [0x15] = KEY_Y, [0x16] = KEY_U, [0x17] = KEY_I,
    [0x18] = KEY_O, [0x19] = KEY_P, [0x1A] = KEY_LBRACKET, [0x1B] = KEY_RBRACKET,
    [0x1C] = KEY_ENTER, [0x1D] = KEY_LCTRL,

    [0x1E] = KEY_A, [0x1F] = KEY_S, [0x20] = KEY_D, [0x21] = KEY_F,
    [0x22] = KEY_G, [0x23] = KEY_H, [0x24] = KEY_J, [0x25] = KEY_K,
    [0x26] = KEY_L, [0x27] = KEY_SEMICOLON, [0x28] = KEY_APOSTROPHE,
    [0x29] = KEY_GRAVE,

    [0x2A] = KEY_LSHIFT, [0x2B] = KEY_BACKSLASH,
    [0x2C] = KEY_Z, [0x2D] = KEY_X, [0x2E] = KEY_C, [0x2F] = KEY_V,
    [0x30] = KEY_B, [0x31] = KEY_N, [0x32] = KEY_M,
    [0x33] = KEY_COMMA, [0x34] = KEY_DOT, [0x35] = KEY_SLASH,
    [0x36] = KEY_RSHIFT, [0x37] = KEY_KP_MULTIPLY,
    [0x38] = KEY_LALT, [0x39] = KEY_SPACE,
    [0x3A] = KEY_CAPSLOCK,

    [0x3B] = KEY_F1, [0x3C] = KEY_F2, [0x3D] = KEY_F3, [0x3E] = KEY_F4,
    [0x3F] = KEY_F5, [0x40] = KEY_F6, [0x41] = KEY_F7, [0x42] = KEY_F8,
    [0x43] = KEY_F9, [0x44] = KEY_F10,

    [0x45] = KEY_NUMLOCK, [0x46] = KEY_SCROLL_LOCK,
    [0x47] = KEY_KP_7, [0x48] = KEY_KP_8, [0x49] = KEY_KP_9,
    [0x4A] = KEY_KP_SUBTRACT,
    [0x4B] = KEY_KP_4, [0x4C] = KEY_KP_5, [0x4D] = KEY_KP_6,
    [0x4E] = KEY_KP_ADD,
    [0x4F] = KEY_KP_1, [0x50] = KEY_KP_2, [0x51] = KEY_KP_3,
    [0x52] = KEY_KP_0, [0x53] = KEY_KP_DOT,

    [0x57] = KEY_F11, [0x58] = KEY_F12
};

static keycode scancode_e0_map_set1[128] = {
    [0x1C] = KEY_KP_ENTER,
    [0x1D] = KEY_RCTRL,
    [0x35] = KEY_KP_DIVIDE,
    [0x37] = KEY_PRINT_SCREEN,  // Only on press + specific conditions
    [0x38] = KEY_RALT,
    [0x47] = KEY_HOME,
    [0x48] = KEY_UP,
    [0x49] = KEY_PAGE_UP,
    [0x4B] = KEY_LEFT,
    [0x4D] = KEY_RIGHT,
    [0x4F] = KEY_END,
    [0x50] = KEY_DOWN,
    [0x51] = KEY_PAGE_DOWN,
    [0x52] = KEY_INSERT,
    [0x53] = KEY_DELETE,
    [0x5B] = KEY_LGUI,
    [0x5C] = KEY_RGUI,
    [0x5D] = KEY_APPS,
    [0x46] = KEY_PAUSE, // See note below
};

static keycode scancode_map_set2[256] = {
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

static keycode scancode_e0_map_set2[256] = {
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
int ps2kbd_scancode_set = 0;

void ps2kbd_ack() {
	while(port_get_byte(0x60) != 0xFA);
}

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

bool ps2kbd_echo() {
	port_put_byte(I8042_DATA_PORT, 0xEE);

	i8042_wait_output_bufferfull();

	return port_get_byte(I8042_DATA_PORT) == 0xEE;
}

void ps2kbd_enable_scanning() {
	port_put_byte(I8042_DATA_PORT, 0xF4);
}

void ps2kbd_disable_scanning() {
	port_put_byte(I8042_DATA_PORT, 0xF5);
}


static void ps2kbd_callback(registers_t regs) {
	i8042_wait_input_buffempty();

	u8 scancode = port_get_byte(I8042_DATA_PORT);

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

	if(ps2kbd_scancode_set == 1 && !isBreakMode && scancode & 0x80) {
		isBreakMode = true;
		scancode &= 0x7F;
	}

	keycode code = KEY_UNKNOWN;

	switch(ps2kbd_scancode_set) {
		case 1:
			code = (hasE0Prefix) ? scancode_e0_map_set1[scancode] : scancode_map_set1[scancode];
			break;
		case 2:
			code = (hasE0Prefix) ? scancode_e0_map_set2[scancode] : scancode_map_set2[scancode];
			break;
	}

	char b[50];
	int_to_ascii(code, b);

	screenprint("Keycode: ");
	screenprint(b);
	screenprint("\n");

	byte_to_hex(scancode, b);
	screenprint("Scancode: 0x");
	screenprint(b);
	screenprint("\n");

	volatile keycode test_val = scancode_map_set1[0x10];

	int_to_ascii(KEY_Q, b);
	screenprint("KEY_Q = "); screenprint(b); screenprint("\n");

	int_to_ascii(test_val, b);
	screenprint("map[0x10] = "); screenprint(b); screenprint("\n");

	byte_to_hex(test_val, b);
	screenprint("0x");
	screenprint(b);
	screenprint("\n");

	if(!isBreakMode) keyboard_handlekeypress(code);
	else keyboard_handlekeyrelease(code);

	isBreakMode = false;
	hasE0Prefix = false;
}

int ps2kbd_scancode_getset() {
	if(i8042_iskeyboard_translated()) return 1;

	port_put_byte(I8042_DATA_PORT, 0xF0);
	port_put_byte(I8042_DATA_PORT, 0x00);
	ps2kbd_ack();

	u8 code = port_get_byte(I8042_DATA_PORT);
	

	switch(code) {
		case 0x43:
			return 1;
		case 0x41:
			return 2;
		case 0x3F:
			return 3;		
	}

	return -1;
}

void ps2kbd_load() {
	i8042_wait_input_buffempty();

	i8042_enable_keyboard_port();
	screendebug("Enabled keyboard PS/2 port");

	int set = ps2kbd_scancode_getset();

	if(set == -1) {
		screenwarn("ps2kbd scancode set was invalid, defaulting to scancode set 1");
		ps2kbd_scancode_set = 1;
	}
	else {
		ps2kbd_scancode_set = set;
	}
	
	char b[5];
	int_to_ascii(ps2kbd_scancode_set, b);

	screenprint("Current scancode set: ");
	screenprint(b);
	screenprint("\n");

	ps2kbd_enable_scanning();

	register_interrupt_handler(IRQ1, ps2kbd_callback);

	screenlog("Loaded ps2kbd driver");
}
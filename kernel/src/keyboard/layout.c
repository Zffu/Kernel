#include <keyboard/keyboard.h>
#include <keyboard/layout.h>

keycode get_keycode_layout_ps2kbd(u8 scancode, kbd_layout_t layout) {
	switch(scancode) {
		case 0x1C:
			return (layout == QWERTY) ? KEY_A : KEY_Q;
		case 0x15:
			return (layout == QWERTY) ? KEY_Q : KEY_A;
		case 0x1A:
			return (layout == QWERTY) ? KEY_Z : KEY_W;
		case 0x1D:
			return (layout == QWERTY) ? KEY_W : KEY_Z;	
		case 0x3A:
			return (layout == QWERTY) ? KEY_M : SPECIAL_2;
		case 0x4C:
			return (layout == QWERTY) ? SPECIAL_3 : KEY_M;	
	}
}

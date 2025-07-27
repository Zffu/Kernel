#include <keyboard/keyboard.h>
#include <driver.h>

#include <isr.h>

#include <screenprint.h>

static void keyboard_callback(registers_t regs) {
    u8 scancode = port_get_byte(0x60);
    print_letter(scancode);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}

// TODO: Improve this weird piece of garbage
void print_letter(u8 scancode) {
    switch (scancode) {
        case 0x0:
            screenprint("ERROR");
            break;
        case 0x1:
            screenprint("ESC");
            break;
        case 0x2:
            screenprint("1");
            break;
        case 0x3:
            screenprint("2");
            break;
        case 0x4:
            screenprint("3");
            break;
        case 0x5:
            screenprint("4");
            break;
        case 0x6:
            screenprint("5");
            break;
        case 0x7:
            screenprint("6");
            break;
        case 0x8:
            screenprint("7");
            break;
        case 0x9:
            screenprint("8");
            break;
        case 0x0A:
            screenprint("9");
            break;
        case 0x0B:
            screenprint("0");
            break;
        case 0x0C:
            screenprint("-");
            break;
        case 0x0D:
            screenprint("+");
            break;
        case 0x0E:
            screenprint("Backspace");
            break;
        case 0x0F:
            screenprint("Tab");
            break;
        case 0x10:
            screenprint("Q");
            break;
        case 0x11:
            screenprint("W");
            break;
        case 0x12:
            screenprint("E");
            break;
        case 0x13:
            screenprint("R");
            break;
        case 0x14:
            screenprint("T");
            break;
        case 0x15:
            screenprint("Y");
            break;
        case 0x16:
            screenprint("U");
            break;
        case 0x17:
            screenprint("I");
            break;
        case 0x18:
            screenprint("O");
            break;
        case 0x19:
            screenprint("P");
            break;
		case 0x1A:
			screenprint("[");
			break;
		case 0x1B:
			screenprint("]");
			break;
		case 0x1C:
			screenprint("ENTER");
			break;
		case 0x1D:
			screenprint("LCtrl");
			break;
		case 0x1E:
			screenprint("A");
			break;
		case 0x1F:
			screenprint("S");
			break;
        case 0x20:
            screenprint("D");
            break;
        case 0x21:
            screenprint("F");
            break;
        case 0x22:
            screenprint("G");
            break;
        case 0x23:
            screenprint("H");
            break;
        case 0x24:
            screenprint("J");
            break;
        case 0x25:
            screenprint("K");
            break;
        case 0x26:
            screenprint("L");
            break;
        case 0x27:
            screenprint(";");
            break;
        case 0x28:
            screenprint("'");
            break;
        case 0x29:
            screenprint("`");
            break;
		case 0x2A:
			screenprint("LShift");
			break;
		case 0x2B:
			screenprint("\\");
			break;
		case 0x2C:
			screenprint("Z");
			break;
		case 0x2D:
			screenprint("X");
			break;
		case 0x2E:
			screenprint("C");
			break;
		case 0x2F:
			screenprint("V");
			break;
        case 0x30:
            screenprint("B");
            break;
        case 0x31:
            screenprint("N");
            break;
        case 0x32:
            screenprint("M");
            break;
        case 0x33:
            screenprint(",");
            break;
        case 0x34:
            screenprint(".");
            break;
        case 0x35:
            screenprint("/");
            break;
        case 0x36:
            screenprint("Rshift");
            break;
        case 0x37:
            screenprint("Keypad *");
            break;
        case 0x38:
            screenprint("LAlt");
            break;
        case 0x39:
            screenprint("Spc");
            break;
        default:
            /* 'keuyp' event corresponds to the 'keydown' + 0x80 
             * it may still be a scancode we haven't implemented yet, or
             * maybe a control/escape sequence */
            if (scancode <= 0x7f) {
                screenprint("Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                screenprint("key up ");
                print_letter(scancode - 0x80);
            } else screenprint("Unknown key up");
            break;
    }
}
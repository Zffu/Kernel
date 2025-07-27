#include <keyboard/keyboard.h>
#include <driver.h>

#include <kernel.h>

#include <isr.h>

#include <screenprint.h>

static char key_buffer[256];

#define BACKSPACE 0x0E
#define ENTER 0x1C

#define SC_MAX 57
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t regs) {
    if (!(port_get_byte(0x64) & 0x1)) return; // Check if output buffer is empty

    u8 scancode = port_get_byte(0x60);

    if(scancode == 0xFF) {
        screenprint("invalid");
        return;
    }
    
    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        backspace(key_buffer);
        screenbackspace();
    } else if (scancode == ENTER) {
        screenprint("\n");
        user_input(key_buffer); /* kernel-controlled function */
        key_buffer[0] = '\0';
    } else {
        char letter = sc_ascii[(int)scancode];
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        screenprint(str);
    }
}

void keyboard_init() {
    while(port_get_byte(0x64) & 0x2);
    screenlog("Keyboard controller ready");

    while(port_get_byte(0x64) & 0x1) {
        port_get_byte(0x60);
    }
    screenlog("Flushed Keyboard IO");

    port_put_byte(0x64, 0xAE);
    screenlog("Enabled first PS/2 port");

    port_put_byte(0x60, 0xF0);
    port_put_byte(0x60, 0x02);
    screenlog("Set keyboard scan code!");

    port_put_byte(0x60, 0xF4);
    screenlog("Enabled keyboard scanning");

    register_interrupt_handler(IRQ1, keyboard_callback); 
    screenlog("Registered keyboard interruption");

    while((port_get_byte(0x64) & 2) != 0);
    port_put_byte(0x60, 0xF4);

    screenlog("Keyboard ready");
}
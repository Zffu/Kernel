#include <ps2kbd.h>
#include <driver.h>

#include <isr.h>

#include <screenprint.h>

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

static void ps2kbd_callback(registers_t regs) {

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
	screendebug("Defined ps2kbd scan layout to standart");

	ps2kbd_enable_scanning();
	screendebug("Enabled ps2kbd scanning");

	register_interrupt_handler(IRQ1, ps2kbd_callback);

#ifndef PS2KBD_FAST
	while((port_get_byte(0x64) & 2) != 0);
	port_put_byte(0x60, 0xF4);
#endif
}
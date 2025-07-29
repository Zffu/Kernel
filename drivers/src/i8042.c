#include <i8042.h>
#include <driver.h>

#include <stdbool.h>

void i8042_wait_input_buffempty() {
	while(port_get_byte(I8042_COMMAND_PORT) & 0x2);
}

void i8042_wait_output_bufferfull() {
	while(!(port_get_byte(I8042_COMMAND_PORT) & 0x1));
}

void i8042_enable_keyboard_port() {
	port_put_byte(I8042_COMMAND_PORT, 0xAE);
}

bool i8042_iskeyboard_translated() {
	i8042_wait_input_buffempty();
	
	port_put_byte(I8042_COMMAND_PORT, 0x20);
	i8042_wait_output_bufferfull();

	u8 cmd = port_get_byte(I8042_DATA_PORT);

	return ((cmd & 0x40) != 0);
}
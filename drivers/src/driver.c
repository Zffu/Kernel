#include <driver.h>

byte_t port_get_byte(port port) {
	byte_t result;
	__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_put_byte(port port, byte_t data) {
	__asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

word_t port_get_word(port port) {
	word_t result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_put_word(port port, word_t data) {
	__asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
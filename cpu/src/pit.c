#include <pit.h>

#include <driver.h>
#include <types.h>

#include <isr.h>

void pit_inittimer(u32 freq, pit_callback_f callback) {
    register_interrupt_handler(IRQ0, callback);

    u32 divisor = 1193180 / freq;
    u8 low  = (u8)(divisor & 0xFF);
    u8 high = (u8)( (divisor >> 8) & 0xFF);

    port_put_byte(0x43, 0x36); 
    port_put_byte(0x40, low);
    port_put_byte(0x40, high);
}
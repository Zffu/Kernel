#include <types.h>

u8 port_is_allowed(u8 port) {
    if(port == 0x60 || port == 0x64) return 1;
    return 0;
}
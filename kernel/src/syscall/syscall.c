#include <klib/syscall.h>
#include <syscall.h>
#include <io/ioports.h>

#include <types.h>

syscall_response khandle_syscall(syscall call, SYSCALL_ARGBUFF argbuff) {
    switch(call) {
        case PRINT:
            return DENIED_STRICT;

        case IOPORT_REQ:
            if(argbuff == SYSCALL_NOARGS) return INVALID_SYSCALL;
            u8* ptr = (u8*) argbuff;

            u8 port = *ptr;
            u8 mode = *(ptr + 1);

            if(port < 0) return INVALID_SYSCALL;
            if(mode < 0 || mode > 1) return INVALID_SYSCALL;

            if(!port_is_allowed(port)) return DENIED;

            // TODO: check for driver permissions
            break;
        
        

            
    }
}
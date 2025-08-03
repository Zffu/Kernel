#include <klib/syscall.h>
#include <syscall.h>

syscall_response khandle_syscall(syscall call, SYSCALL_ARGBUFF argbuff) {
    switch(call) {
        case PRINT:
            return DENIED_STRICT;
        case IOPORT_REQ:
        
    }
}
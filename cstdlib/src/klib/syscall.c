#include <klib/syscall.h>
#include <types.h>

syscall_response ksyscall(syscall call, SYSCALL_ARGBUFF args) {
    __asm__("mov %%al, al" : : "a" ((u8) call));
    __asm__("mov %%eax, ebx" : : "a" (args)); // MUST BE A POINTER

#ifdef SYSCALL_MODERN_INSTRUCTION
    __asm__("syscall");
#else
    __asm__("int 0x80");
#endif

    u8 result;
    __asm__("mov bl, %%al" : "=a" (result));

    if(result < DENIED || result > SYSCALL_RESPONSE_SZ) {
        return UNDEFINED;
    }

    return (syscall_response) result;
}
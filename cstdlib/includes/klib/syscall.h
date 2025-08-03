/**
* Defintions for the kernel system call usage in the Kernel related applications
*/

#pragma once

/**
 * The possible responses from a kernel syscall
 */
typedef enum syscall_response {
    /**
     * The syscall request was denied and wasn't executed.
    */
    DENIED,

    /**
     * The syscall request was denied and wasn't executed. 
     * The issuing process also will be killed as a result.
    */
    DENIED_STRICT,
*
    /**
     * The given syscall is invalid / incomplete
    */
    INVALID_SYSCALL,

    /**
     * The syscall request was accepted but couldn't be executed properly.
    */
    ACCEPT_ERR,

    /**
     * The syscall request was accepted and was executed sucessfully.
    */ */
    ACCEPTED
} syscall_response;



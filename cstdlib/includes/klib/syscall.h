/**
* Defintions for the kernel system call usage in the Kernel related applications
*/

#pragma once


#define SYSCALL_ARGBUFF void*
#define SYSCALL_NOARGS ((void*)0)

#ifndef SYSCALL_MODERN_INSTRUCTION
#define SYSCALL_INTERRUPT 0x80
#endif

#define SYSCALL_RESPONSE_SZ ACCEPTED

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
    */ 
    ACCEPTED,

    UNDEFINED
} syscall_response;


/**
 * The available system calls.
*/
typedef enum syscall {
    
    /**
     * Prints a message
    */
    PRINT,

    /**
     * Asks for either read or write rights on a specific IO port,
     * The issuer task has to be considered as a driver task for the request to be considered.
    */
    IOPORT_REQ,

    /**
     * Requests to apply the driver status to the issuer process. This request will always fail if said task isn't
     * internally spun by the kernel.
    */
    DRIVERTASK_REQ,

    /**
    * Kills a specified task. This request will fail if the permissions of the issuer aren't high enough (if a program tries closing another program and isn't privilleged).
    */
    TASK_KILL,

    /**
     * Spawns / creates a process. The request will fail if the issuer tries spawning a task that is either internal or requires higher permissions than what the issuer has.
    */
    TASK_SPAWN
    
} syscall;

/**
 * Requests a syscall to the kernel.
 * @param call the systemcall to request
 * @param args the syscall arguments, should be SYSCALL_NOARGS if no arguments
 * @return a response to your syscall.s
*/
syscall_response ksyscall(syscall call, SYSCALL_ARGBUFF args);
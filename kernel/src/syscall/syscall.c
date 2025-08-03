#include <klib/syscall.h>
#include <syscall.h>
#include <io/ioports.h>

#include <taskio.h>

#include <str.h>

#include <types.h>

extern internal_task_t* taskio_internaltask_queue;
extern task_t* taskio_task_queue;

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
        
        case TASK_KILL:
            if(argbuff == SYSCALL_NOARGS) return INVALID_SYSCALL;
            u8* ptr = (u8*) argbuff;

            u8 task_type = *ptr;
            char* task_name = (char*) (ptr + 1);

            if(task_type < 0 || task_type > 1) return INVALID_SYSCALL;
            if(task_name == 0) return INVALID_SYSCALL;

            // Internal
            if(task_type == 0x01) {
                internal_task_t* node = taskio_internaltask_queue;

                while(node != 0) {
                    if(strcmp(task_name, node->name)) {
                        node->detach();

                        return ACCEPTED;
                    }

                    node = node->next;
                }

                return ACCEPT_ERR;
            }
            
            task_t* node = taskio_task_queue;

            while(node != 0) {
                if(strcmp(task_name, node)) {
                    // TODO: remove node

                    return ACCEPTED;
                }

                node = node->next;
            }

            return ACCEPT_ERR;
    }
}
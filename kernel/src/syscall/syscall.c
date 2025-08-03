#include <klib/syscall.h>
#include <syscall.h>
#include <io/ioports.h>

#include <taskio/taskio.h>

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

            //TODO: check permissions of task before using priviledged function

            if(task_kill_instant(task_name, task_type) == 0) return ACCEPT_ERR;
            return ACCEPT;

        case TASK_SPAWN:
            if(argbuff == SYSCALL_NOARGS) return INVALID_SYSCALL;
            u8* ptr = (u8*) argbuff;

            u8 mode = *(ptr);
            u8* point = *((u8**)(ptr + 1));
            char* name = *((char**)(ptr + sizeof(u8*) + 1));

            if(mode < 0 || mode > 1) return INVALID_SYSCALL;
            if(point == 0 || name == 0) return INVALID_SYSCALL;

            // TODO: make internal tasks require additional permissions

            if(mode == 0x00) {
                task_t* task = create_task(name, (entry_point_t)(point));

                if(task == 0) return ACCEPT_ERR;
                return ACCEPT;
            }

            internal_task_t* task = create_internal_task(name, (detach_point_t)(point));

            if(task == 0) return ACCEPT_ERR;
            return ACCEPT;
        default:
            return INVALID_SYSCALL;
        
    }
}
#include <klib/syscall.h>
#include <syscall.h>
#include <io/ioports.h>

#include <taskio/taskio.h>

#include <types.h>

syscall_response khandle_syscall(syscall call, SYSCALL_ARGBUFF argbuff) {

    if(current_task == 0) {
        return DENIED;
    }

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

            if(current_task->type < DRIVER) {
                task_kill_instant(current_task, 0x00);
                return DENIED_STRICT;
            }

            if(!port_is_allowed(port)) return DENIED;

            break;
        
        case TASK_KILL:
            if(argbuff == SYSCALL_NOARGS) return INVALID_SYSCALL;
            u8* ptr = (u8*) argbuff;

            u8 task_type = *ptr;
            char* task_name = (char*) (ptr + 1);

            if(task_type < 0 || task_type > 1) return INVALID_SYSCALL;
            if(task_name == 0) return INVALID_SYSCALL;
        
            //TODO: add a permission check here

            if(task_kill_instant(task_name, task_type) == 0) return ACCEPT_ERR;
            return ACCEPTED;

        case TASK_SPAWN:
            if(argbuff == SYSCALL_NOARGS) return INVALID_SYSCALL;
            u8* ptr = (u8*) argbuff;

            u8 mode = *(ptr);
            u8* point = *((u8**)(ptr + 1));
            char* name = *((char**)(ptr + sizeof(u8*) + 1));

            if(mode < 0 || mode > 1) return INVALID_SYSCALL;
            if(point == 0 || name == 0) return INVALID_SYSCALL;

            if(current_task->type != KERNEL_INTEGRATED) return DENIED;

            if(mode == 0x00) {
                task_t* task = create_task(name, (entry_point_t)(point));

                if(task == 0) return ACCEPT_ERR;
                return ACCEPTED;
            }

            internal_task_t* task = create_internal_task(name, (detach_point_t)(point));

            if(task == 0) return ACCEPT_ERR;
            return ACCEPTED;
        default:
            return INVALID_SYSCALL;
        
    }
}
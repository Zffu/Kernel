/**
 * TaskIO definitions
 */

#pragma once

#include <types.h>

#ifndef TASKIO_PERTASK_STACK_SIZE 
#define TASKIO_PERTASK_STACK_SIZE 256
#endif

#define TASKIO_TASK_LIKELY_POINTER u8*

extern task_t* taskio_task_queue;
extern internal_task_t* taskio_internaltask_queue;

#define TASKIO_FINDTASK(name) find_task(name, taskio_task_queue)
#define TASKIO_FINDINTERNALTASK(name) find_task(name, taskio_internaltask_queue)

/**
 * Defines tasks that are fully 'internal', AKA tasks that do NOT need to be ticked 
 * trough the CPU timer interrupt
 */
typedef struct taskio_task_t__bundled {
	char* name;
	void *(*detatch)();

	struct taskio_task_t__bundled* prev;
	struct taskio_task_t__bundled* next;
} internal_task_t;

/**
 * Defines tasks that are ticked in the CPU timer interrupt
 */
typedef struct taskio_task_t {
	char* name;
	u32* stack;

	u32 esp, ebp, eip;
	u32 eax, ebx, ecx, edx;
	u32 esi, edi;
	u32 eflags;

	struct taskio_task_t* prev;
	struct taskio_task_t* next;
} task_t;

typedef void (*entry_point_t)();
typedef void (*detach_point_t)();

/**
 * @name create_task
 * 
 * @param name the name of the task
 * @param entry_point the entry point
 */
task_t* create_task(char* name, void (*entry_point)());

/**
 * @name create_internal_task
 * 
 * @param name the name of the internal task
 * @param detach the function allowing to detach/kill the internal tasks
 */
internal_task_t* create_internal_task(char* name, void (*detach)());

/**
 * @name find_task
 *
 * Finds a task based on the name of it. It is recomended to use the FINDTASK macros instead.
 *
 * @param name the name of the task
 * @param tree the tree pointer of the tasks. 
*/
TASKIO_TASK_LIKELY_POINTER find_task(char* name, TASKIO_TASK_LIKELY_POINTER tree);

/**
 * @name task_kill_instant
 *
 * Kills the task if it exists, skips every permission / authority check when killing the task, doesn't wait for the app to be ready.
 *
 * @param name the name of the task
 * @param tree the tree pointer of the tasks.
 * @param mode the mode, 0x00 if normal task, 0x01 if internal
 * @return 0x00 if the task couldn't be killed, 0x01 if it was
 */
u8 task_kill_instant(char* name, TASKIO_TASK_LIKELY_POINTER tree, u8 mode);

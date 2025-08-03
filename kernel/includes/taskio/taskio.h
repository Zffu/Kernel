/**
 * TaskIO definitions
 */

#pragma once

#include <types.h>

#ifndef TASKIO_PERTASK_STACK_SIZE 
#define TASKIO_PERTASK_STACK_SIZE 256
#endif

#define TASKIO_TASK_LIKELY_POINTER taskio_task_common_t*

extern task_t* taskio_task_queue;
extern internal_task_t* taskio_internaltask_queue;

#define TASKIO_FINDTASK(name) find_task(name, taskio_task_queue)
#define TASKIO_FINDINTERNALTASK(name) find_task(name, taskio_internaltask_queue)

#define TASKIO_FINDTASK_0(name) TASKIO_FINDTASK(name)
#define TASKIO_FINDTASK_1(name) TASKIO_FINDINTERNALTASK(name)

#define TASKIO_KILLTASKBYNAME(name, result, type) \
	TASKIO_TASK_LIKELY_POINTER task = TASKIO_FINDTASK_##type(name); \
	result = (task != 0) ? taskthis_kill_instant(result, type) : 0x00;

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

	struct taskio_task_t* prev;
	struct taskio_task_t* next;

	u32* stack;

	u32 esp, ebp, eip;
	u32 eax, ebx, ecx, edx;
	u32 esi, edi;
	u32 eflags;
} task_t;

/**
 * Common structures between task_t and internal_task_t
*/
typedef struct taskio_task_common_t {
	char* name;

	struct taskio_task_common_t* prev;
	struct taskio_task_common_t* next;
} taskio_task_common_t;

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
 * @name taskthis_kill_instant
 *
 * Kills the task, skips every permission / authority check when killing the task, doesn't wait for the app to be ready.
 *
 * @param task the pointer of the task
 * @param mode the mode, 0x00 if normal task, 0x01 if internal
 * @return 0x00 if the task couldn't be killed, 0x01 if it was
 */
u8 task_kill_instant(TASKIO_TASK_LIKELY_POINTER task, u8 mode);

/**
 * @name get_current_task
 * @return the current running task
*/
#define get_current_task() taskio_task_queue;
/**
 * TaskIO definitions
 */

#pragma once

#include <types.h>

#ifndef TASKIO_PERTASK_STACK_SIZE 
#define TASKIO_PERTASK_STACK_SIZE 256
#endif

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
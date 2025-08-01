/**
 * TaskIO definitions
 */

#pragma once

#include <types.h>

typedef struct taskio_task_t__bundled {
	u8 id;
	void *(detatch)();

	struct taskio_task_t__bundled* next;
	struct taskio_task_t__bundled* prev;
} internal_task_t;

typedef struct taskio_task_t {
	char* name;
	u32* stack;

	u32 esp, ebp, eip;
	u32 eax, ebx, ecx, edx;
	u32 esi, edi;
	u32 eflags;
} task_t;
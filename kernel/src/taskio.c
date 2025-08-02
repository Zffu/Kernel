#include <taskio.h>
#include <memalloc.h>
#include <mem.h>

task_t* taskio_task_queue;
internal_task_t* taskio_internaltask_queue;

task_t* create_task(char* name, void (*entry_point)()) {
	task_t* task = kmallocs(sizeof(task_t), 1);
	task->stack = kmallocs(TASKIO_PERTASK_STACK_SIZE, 1);

	u32 top = (u32) task->stack + TASKIO_PERTASK_STACK_SIZE;

	#ifdef TASKIO_EMPTY_STACK
	memset(task->stack, 0, TASKIO_PERTASK_STACK_SIZE);
	#endif

	task->esp = top - 16;
	task->ebp = task->esp;
	task->eip = (u32) entry_point;

	task->next = taskio_task_queue;

	if(!taskio_task_queue) {
		taskio_task_queue = task;
		task->next = 0;
	}
	else {
		taskio_task_queue->prev = task;
		task->next = taskio_task_queue;
		taskio_task_queue = task;
	}
}

internal_task_t* create_internal_task(char* name, void (*detach)()) {
	internal_task_t* task = kmallocs(sizeof(task_t), 1);

	task->name = name;

	task->next = taskio_internaltask_queue;
	task->detatch = detach;

	if(!taskio_internaltask_queue) {
		taskio_internaltask_queue = task;
		task->next = 0;
	}
	else {
		taskio_internaltask_queue->prev = task;
		task->next = taskio_internaltask_queue;
		taskio_internaltask_queue = task;
	}
}
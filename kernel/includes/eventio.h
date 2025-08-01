#pragma once

typedef enum event_t {
	KBDKEY
} event_t;

#define EVENTSZ 1

typedef struct eventio_node_t {
	void (*handler)(int val);

	struct eventio_node_t* prev;
	struct eventio_node_t* next;
} eventio_node_t;

void eventio_register(event_t event, void (*handler)(int val));
void eventio_trigger(event_t event, int val);
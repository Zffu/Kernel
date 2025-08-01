#include <eventio.h>
#include <memalloc.h>

#include <stdlib.h>

eventio_node_t* eventio_event_nodes[EVENTSZ] = {0};

void eventio_register(event_t event, void (*handler)(int val)) {
	eventio_node_t* node = kmallocs(sizeof(eventio_node_t), 1);
	
	node->handler = node;
	node->prev = 0;

	if(!eventio_event_nodes[event]) {
		eventio_event_nodes[event] = node;
		node->next = 0;
	}
	else {
		node->next = event;
		eventio_event_nodes[event]->prev = node;
		eventio_event_nodes[event] = node;
	}
}

void eventio_trigger(event_t event, int val) {
	eventio_node_t* n = eventio_event_nodes[event];

	while(n != 0) {
		n->handler(val);
	
		n = n->next;
	}
}
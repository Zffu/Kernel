#pragma once

#define INPUTSTREAM_MAX 257

typedef struct inputstream_t {
	char buff[INPUTSTREAM_MAX];
	int sz;
	void (*user_finish)(char* buff);
	void (*user_push)(char c);
} inputstream_t;

void inputstream_push(char c, inputstream_t* stream);

void inputstream_flush(inputstream_t* stream);
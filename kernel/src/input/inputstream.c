#include <input/inputstream.h>

void inputstream_push(char c, inputstream_t* stream) {
	stream->buff[stream->sz] = c;
	++stream->sz;

	stream->user_push(c);

	if(stream->sz <= (INPUTSTREAM_MAX - 1)) {
		stream->buff[stream->sz] = '\0';
		stream->user_finish(stream->buff);
		stream->sz = 0;
	}
}

void inputstream_flush(inputstream_t* stream) {
	stream->buff[stream->sz] = '\0';
	stream->user_finish(stream->buff);
	stream->sz = 0;
}
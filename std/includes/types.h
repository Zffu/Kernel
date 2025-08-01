#pragma once

#define REGISTER_FAMILLY(type, sz) \
	typedef type s##sz; \
	typedef unsigned type u##sz;


REGISTER_FAMILLY(int, 32)
REGISTER_FAMILLY(short, 16)
REGISTER_FAMILLY(char, 8)

typedef unsigned char byte_t;
typedef unsigned short word_t;

typedef unsigned short port;

#define LOW16(addr) (u16)((addr) & 0xFFFF)
#define HIGH16(addr) (u16)(((addr) >> 16) & 0xFFFF)
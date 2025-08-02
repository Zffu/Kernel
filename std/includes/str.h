#include <types.h>

void int_to_ascii(int n, char* str);
void hex_to_ascii(int n, char str[]);

void byte_to_hex(unsigned char byte, char *out);

int uint_to_str(unsigned int value, char *out);
void float_to_string(float f, char *out, int precision);

void backspace(char* s);

void append(char* s, char n);

u8 strcmp(char* s, char* s2);

int strlen(char* s);

void str_split(char* str, char seperator, char** argptrs, int* arg_sz);
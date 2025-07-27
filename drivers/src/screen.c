#include <driver.h>
#include <screen.h>

int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

/**
 * STD screenprint defs
 */

void print_at(char* text, int col, int row) {
	int offset;
	if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

	int i = 0;
    while (text[i] != 0) {
        offset = print_char(text[i++], col, row, WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void print(char* text) {
	print_at(text, -1, -1);
}

void clearscreen() {
	int screen_sz = MAX_COLS * MAX_ROW;
	int i;
	char* screen = VIDEO_ADDR;

	for(int i = 0; i < screen_sz; ++i) {
		screen[i * 2] =  ' ';
		screen[i * 2 + 1] = WHITE_ON_BLACK;
	}

	set_cursor_offset(get_offset(0, 0));
}

/**
 * Private Kernel defs
 */
int print_char(char c, int col, int row, char attr) {
	unsigned char* mem = (unsigned char*) VIDEO_ADDR;
	if(!attr)attr = WHITE_ON_BLACK;

	if(col >= MAX_COLS || row >= MAX_ROW) {
        mem[2*(MAX_COLS)*(MAX_ROW)-2] = 'E';
        mem[2*(MAX_COLS)*(MAX_ROW)-1] = RED_ON_WHITE;
		return get_offset(col, row);
	}

	int offset;
	if(col >= 0 && row >= 0) offset = get_offset(col, row);
	else offset = get_cursor_offset();

	if(c == '\n') {
		row = get_offset_row(offset);
		offset = get_offset(0, row + 1);
	} else {
		mem[offset] = c;
		mem[offset + 1]= attr;
		offset += 2;
	}

	set_cursor_offset(offset);
	return offset;
}

int get_cursor_offset() {
	port_put_byte(REG_SCREEN_CONTROL, 14);
	int offset = port_get_byte(REG_SCREEN_DATA) << 8;
	port_put_byte(REG_SCREEN_CONTROL, 15);
	offset += port_get_byte(REG_SCREEN_DATA);

	return offset * 2;
}

void set_cursor_offset(int offset) {
	offset /= 2;
	port_put_byte(REG_SCREEN_CONTROL, 14);
	port_put_byte(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
	port_put_byte(REG_SCREEN_CONTROL, 15);
	port_put_byte(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }
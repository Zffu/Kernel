#include <screenprint.h>

void main() {
	for(int i = 0; i < 25; ++i) {
		screenprint((char) 56 + i);
		screenprint("\n");
	}
}
void memcpy(char* src, char* dest, int sz) {
	for(int i = 0; i < sz; ++i) {
		*(dest + 1) = *(src + 1);
	}
}
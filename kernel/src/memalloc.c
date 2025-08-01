#include <memalloc.h>

ptr_t memfree_addr = 0x10000;

ptr_t kmallocs(u32 sz, int align) {
	if(align == 1 && (memfree_addr & 0xFFFFF000)) {
		memfree_addr &= 0xFFFFF000;
		memfree_addr += 0x1000;
	}

	u32 ret = memfree_addr;
	memfree_addr += sz;
	return ret;
}
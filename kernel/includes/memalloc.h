#pragma once

#include <types.h>

typedef u32 ptr_t;

/**
 * @name kmallocs
 * 
 * Simple version of malloc
 * 
 * @param sz the size
 * @param align the alignement
 * 
 * @return the pointer to the allocation
 */
ptr_t kmallocs(u32 sz, int align);
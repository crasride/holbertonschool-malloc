#include "malloc.h"

#define ALIGN(size) (((size) + 7) / 8 * 8)
#define ALIGN_PTR(ptr) ((void *)(((size_t)(ptr) + 7) / 8 * 8))

void *naive_malloc(size_t size) {
	size_t *chunk;
	void *memory;
	static size_t last_break;

	size = ALIGN(size) + sizeof(size_t);

	if (last_break == 0 || (size_t)sbrk(0) - last_break < size)
	{
		size_t page_size = getpagesize();
		size_t break_size = ((size_t)sbrk(0) + page_size - 1) / page_size * page_size;

		if ((size_t)last_break % page_size + sizeof(size_t) > page_size - size)
		{
			sbrk(page_size - (break_size - (size_t)sbrk(0)) + size);
			last_break = ((size_t)sbrk(0) - size + 7) / 8 * 8;
		} else
		{
			sbrk(size);
			last_break = ((size_t)sbrk(0) - size + 7) / 8 * 8;
		}
	}

	memory = ALIGN_PTR((void *)last_break);
	last_break = (size_t)((char *)memory + size);

	chunk = (size_t *)memory;
	*chunk = size;

	return ((void *)(chunk + 1));
}





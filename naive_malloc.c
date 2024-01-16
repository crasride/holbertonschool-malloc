#include "malloc.h"

#define ALIGN(size) (((size) + 7) / 8 * 8)

void *naive_malloc(size_t size)
{
	size_t *chunk;
	void *memory;
	static void *last_break;

	/* Align size */
	size = ALIGN(size) + sizeof(size_t);

	/* If last break is NULL or not enough space, get more space */
	if (last_break == NULL || (size_t)sbrk(0) - (size_t)last_break < size)
	{
		size_t page_size = getpagesize();
		size_t break_size = ((size_t)sbrk(0) + page_size - 1) / page_size * page_size;

		if ((size_t)last_break % page_size + sizeof(size_t) > page_size - size)
		{
			sbrk(page_size - (break_size - (size_t)sbrk(0)) + size);
		}
		else
		{
			sbrk(size);
		}

		last_break = sbrk(0);
	}

	memory = last_break;
	last_break = (void *)((char *)memory + size);

	chunk = (size_t *)memory;
	*chunk = size;

	return ((void *)(chunk + 1));
}


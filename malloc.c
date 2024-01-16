#include "malloc.h"

#define ALIGN(size) \
	(((size) + sizeof(size_t) - 1) / sizeof(size_t) * sizeof(size_t))

static void *last_break;
static size_t chunks;

void *_malloc(size_t size)
{
	size_t *chunk;
	void *memory;
	size_t unused_space;

	size = ALIGN(size) + sizeof(size_t);

	if (!last_break || (size_t)sbrk(0) - (size_t)last_break < size)
	{
		size_t page_size = getpagesize();
		size_t break_size = ((size_t)sbrk(0) + page_size - 1)
									/ page_size * page_size;

		if ((size_t)last_break % page_size + sizeof(size_t) > page_size - size)
		{
			sbrk(page_size - (break_size - (size_t)sbrk(0)) + size);
			last_break = (void *)(((size_t)sbrk(0) - size + sizeof(size_t) - 1)
									/ sizeof(size_t) * sizeof(size_t));
		}
		else
		{
			sbrk(size);
			last_break = (void *)((size_t)sbrk(0) - size);
		}
	}

	memory = last_break;
	unused_space = (size_t)sbrk(0) - (size_t)last_break;
	last_break = (void *)((char *)memory + size);
	chunk = (size_t *)memory;
	*chunk = size;
	if (unused_space > size + sizeof(size_t))
	{
		*((size_t *)((char *)memory + size)) = unused_space - size;
		chunks++;
	}
	return ((void *)(chunk + 1));
}

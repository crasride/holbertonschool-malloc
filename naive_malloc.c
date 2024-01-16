#include "malloc.h"

void *naive_malloc(size_t size)
{
	size_t *header;
	size_t i;
	static size_t heap_size;
	static size_t used_space;
	static size_t *next_chunk;
	size_t size_in_mem = 0;
	size_t size_page = (size_t)getpagesize();

	printf("size_t size: %lu\n", sizeof(size_t));
	printf("size_page: %lu\n", size_page);
	/* calculate real size in memory */
	for (size_in_mem = 0; size_in_mem < (size + sizeof(size_t));
								size_in_mem += sizeof(size_t))
		;
	if (!next_chunk)
		next_chunk = sbrk(0);
	printf("next_chunk: %p\n", (void *)next_chunk);
	/* check if enough space in heap */
	if (heap_size < (used_space + size_in_mem + sizeof(size_t)))
	{
		for (i = 0; ((size_in_mem - (heap_size - used_space))
					+ sizeof(size_t)) > i;
				i += size_page)
			;
		printf("sbrk(%lu)\n", i);
		if (sbrk(i) == (void *) -1)
			return (NULL);
		heap_size += i; /* - size_page ? */
	}

	used_space += size_in_mem;
	header = next_chunk;
	*header = size_in_mem; /* store size in the header */
	next_chunk += size_in_mem;
	return ((void *)(next_chunk + 1));
}

#include "malloc.h"

void *naive_malloc(size_t size)
{
	size_t *header;
	size_t i;
	static size_t heap_size;
	static size_t used_space;
	static size_t *next_chunk;
	size_t size_in_mem = 0;
	size_t page_size = (size_t)getpagesize();

	/* rounding by multiple of size_t which is bigger than size */
	for (size_in_mem = 0; size_in_mem < size;
								size_in_mem += sizeof(size_t))
		;
	/* add header size */
	size_in_mem += sizeof(size_t);
	/* for first use of this function */
	if (!next_chunk)
		next_chunk = sbrk(0);
	/* check if enough space in heap */
	if (heap_size < (used_space + size_in_mem + sizeof(size_t)))
	{
		/* increase heap by adding multiples of page_size (4096 bytes) */
		for (i = 0; ((size_in_mem - (heap_size - used_space))
					+ sizeof(size_t)) > i;
				i += page_size)
			;
		/* printf("sbrk(%lu)\n", i); */
		if (sbrk(i) == (void *) -1)
			return (NULL);
		heap_size += i;
	}
	/* update used space */
	used_space += size_in_mem;
	/* pass memory address of current chunk to header */
	header = next_chunk;
	/* store size in the header */
	*header = size_in_mem;
	/* change memory address of pointer next_chunk */
	next_chunk += (size_in_mem / sizeof(size_t));
	/* return pointer to start of the future data */
	return ((void *)(header + 1)); /* +1 (byte) to skip header */
}

#include "malloc.h"

/**
* _free - frees memory
* @ptr: pointer to memory to free
*/
void _free(void *ptr)
{
	size_t *chunk_header;

	if (!ptr)
		return;

	chunk_header = (size_t *)ptr - 1;

	/* *chunk_header = *chunk_header & ~1 ;*/
	*chunk_header |= 1;
}

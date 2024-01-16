#include "malloc.h"

void _free(void *ptr)
{
	size_t *chunk_header;

	if (!ptr)
		return;

	chunk_header = (size_t *)ptr - 1;

	*chunk_header = *chunk_header & ~1;
}

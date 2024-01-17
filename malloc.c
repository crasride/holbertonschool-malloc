#include "malloc.h"

#define ALIGN(size) \
	(((size) + sizeof(size_t) - 1) / sizeof(size_t) * sizeof(size_t))

static void *last_break;
static size_t chunks;

/**
* _malloc - allocates memory
* @size: size of memory to allocate
* Return: pointer to allocated memory
*/
void *_malloc(size_t size)
{
	size_t *chunk;
	void *memory;
	size_t aligned_size;

	size = ALIGN(size + sizeof(size_t));

	if (!last_break || (size_t)sbrk(0) - (size_t)last_break < size)
	{
		sbrk(size);
		last_break = (void *)((size_t)sbrk(0) - size);
	}

	memory = (void *)(((size_t)last_break + sizeof(size_t) - 1) / sizeof(size_t) * sizeof(size_t));
	aligned_size = (size_t)sbrk(0) - (size_t)memory;

	if (aligned_size > size)
	{
		*((size_t *)memory) = aligned_size - size;
		chunks++;
		last_break = (void *)((char *)memory + size);
		/* printf("last_break: %p, unused_space: %zu\n", last_break, aligned_size - size);
		printf("Comparando con el bloque liberado de tamaño: %zu\n", *((size_t *)memory)); */
	}

	chunk = (size_t *)memory;
	return ((void *)(chunk + 1));
}

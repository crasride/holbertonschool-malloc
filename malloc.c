#include "malloc.h"

/* Function to align memory size */
#define ALIGN(size) \
	(((size) + sizeof(size_t) - 1) / sizeof(size_t) * sizeof(size_t))
/* Pointer to the end of the allocated memory space */
static void *last_break;
/* Counter for allocated blocks */
static size_t chunks;

/**
* _malloc - allocates memory
* @size: size of memory to allocate
* Return: pointer to allocated memory
*/
void *_malloc(size_t size)
{
	size_t *chunk;	/* Pointer to the header of the allocated memory block */
	void *memory;	/* Pointer to the start of the allocated memory block */
	size_t aligned_size;	/* Actual size of the allocated memory block */

	/* Align the requested size taking into account the block header */
	size = ALIGN(size + sizeof(size_t));
	/*
	* If there is no allocated space or not enough space in the current block,
	* allocate more space
	*/
	if (!last_break || (size_t)sbrk(0) - (size_t)last_break < size)
	{
		/* Increase available space */
		sbrk(size);
		/* Update the pointer to the end of the allocated space */
		last_break = (void *)((size_t)sbrk(0) - size);
	}

	/* Calculate the start of the memory block and its actual size */
	memory = (void *)(((size_t)last_break + sizeof(size_t) - 1)
						/ sizeof(size_t) * sizeof(size_t));
	/* Calculate the actual size of the allocated memory block */
	aligned_size = (size_t)sbrk(0) - (size_t)memory;

	/* If there is enough space, store the unused size in the block */
	if (aligned_size < size)
	{
		/* Store the unused size in the block */
		*((size_t *)memory) = aligned_size - size;
		chunks++;
		/* Update the pointer to the end of the allocated space */
		last_break = (void *)((char *)memory + size);
	}

	/* Update the pointer to the end of the allocated space */
	chunk = (size_t *)memory;
	/* Return a pointer to the start of the block (after the header) */
	return ((void *)(chunk + 1));
}

#include "malloc.h"

#define ALIGN(size) (((size) + sizeof(size_t) - 1) / sizeof(size_t) * sizeof(size_t))

void *naive_malloc(size_t size)
{
	static void *block_zero = NULL;
	static size_t chunks = 0;
	size_t i = 0;
	size_t unused_block_size = 0;
	size_t std_block_size = ALIGN(size) + sizeof(size_t);
	void *next_block = NULL;
	void *block_ptr = NULL;

	if (!block_zero)
	{
		block_zero = sbrk(getpagesize());
		if (block_zero == (void *)-1)
		{
			perror("sbrk error");
			return NULL;
		}
	}

	block_ptr = block_zero;

	for (i = 0; i < chunks; i++)
	{
		size_t block_size = *((size_t *)block_ptr);
		block_ptr = (char *)block_ptr + block_size;
	}


	unused_block_size = chunks ? *((size_t *)block_ptr) : (size_t)getpagesize();

	next_block = (char *)block_ptr + std_block_size;


	while (unused_block_size < std_block_size + sizeof(size_t) * 2)
	{
		if (sbrk(getpagesize()) == (void *)-1)
		{
			perror("sbrk error");
			return NULL;
		}
		unused_block_size += getpagesize();
	}

	*((size_t *)next_block) = unused_block_size - std_block_size;
	*((size_t *)block_ptr) = std_block_size;

	chunks++;

	return (char *)block_ptr + sizeof(size_t);
}





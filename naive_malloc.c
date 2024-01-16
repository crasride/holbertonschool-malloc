#include "malloc.h"

#define ALIGN(size) \
	(((size) + sizeof(size_t) - 1) / sizeof(size_t) * sizeof(size_t))


static void *find_next_block(void *block_ptr, size_t chunks)
{
	size_t i;

	for (i = 0; i < chunks; i++)
	{
		size_t block_size = *((size_t *)block_ptr);

		block_ptr = (char *)block_ptr + block_size;
	}
	return (block_ptr);
}


static void *allocate_new_page(void *block_zero, size_t std_block_size,
								size_t *unused_block_size)
{
	if (sbrk(getpagesize()) == (void *)-1)
	{
		perror("sbrk error");
		return (NULL);
	}
	*unused_block_size += getpagesize();
	return ((char *)block_zero + std_block_size);
}


void *naive_malloc(size_t size)
{
	static void *block_zero;
	static size_t chunks;
	size_t unused_block_size = 0;
	size_t std_block_size = ALIGN(size) + sizeof(size_t);
	void *next_block = NULL, *block_ptr = NULL;

	if (!block_zero)
	{
		block_zero = sbrk(getpagesize());
		if (block_zero == (void *)-1)
		{
			perror("sbrk error");
			return (NULL);
		}
	}

	block_ptr = find_next_block(block_zero, chunks);

	unused_block_size = chunks ? *((size_t *)block_ptr) : (size_t)getpagesize();

	next_block = (char *)block_ptr + std_block_size;

	while (unused_block_size < std_block_size + sizeof(size_t) * 2)
	{
		next_block = allocate_new_page(block_zero, std_block_size,
										&unused_block_size);
		if (!next_block)
			return (NULL);
	}

	*((size_t *)next_block) = unused_block_size - std_block_size;
	*((size_t *)block_ptr) = std_block_size;
	chunks++;

	return ((char *)block_ptr + sizeof(size_t));
}

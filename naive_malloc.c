#include "malloc.h"

#define ALIGN(size) \
	(((size) + sizeof(size_t) - 1) / sizeof(size_t) * sizeof(size_t))


/**
* find_next_block - Find the next available block
* @block_ptr: Pointer to the initial block of memory
* @chunks: Number of allocated chunks
* Return: Pointer to the next available block
*/
static void *find_next_block(void *block_ptr, size_t chunks)
{
	size_t i;

	/* Loop through existing blocks to find the next available block */
	for (i = 0; i < chunks; i++)
	{
		size_t block_size = *((size_t *)block_ptr);

		/*
		* Advances the pointer to the next block by adding the size
		* of the current block
		*/
		block_ptr = (char *)block_ptr + block_size;
	}
	return (block_ptr);
}

/**
* allocate_new_page - Allocate a new page of memory
* @block_zero: Pointer to the initial block of memory
* @std_block_size: Size of the block to allocate
* @unused_block_size: Size of the remaining unused block
*
* Return: Pointer to the allocated block
*/
static void *allocate_new_page(void *block_zero, size_t std_block_size,
								size_t *unused_block_size)
{
	/* Check if it is possible to allocate a new memory page using sbrk */
	if (sbrk(getpagesize()) == (void *)-1)
	{
		perror("sbrk error");
		return (NULL);
	}

	/*
	* Increases the size of the remaining unused block with the size
	* of the new page
	*/
	*unused_block_size += getpagesize();

	/*
	* Returns the pointer to the new allocated block, starting after
	* the original block
	*/
	return ((char *)block_zero + std_block_size);
}

/**
* naive_malloc - Naive malloc implementation
* @size: Size to allocate
*
* Return: Pointer to allocated memory
*/
void *naive_malloc(size_t size)
{
	static void *block_zero;
	static size_t chunks;
	size_t unused_block_size = 0;
	size_t std_block_size = ALIGN(size) + sizeof(size_t);
	void *next_block = NULL, *block_ptr = NULL;

	if (!block_zero)
	{
		/* Allocate the first page if not done already */
		block_zero = sbrk(getpagesize());
		if (block_zero == (void *)-1)
		{
			perror("sbrk error");
			return (NULL);
		}
	}
	/* Find the next available block */
	block_ptr = find_next_block(block_zero, chunks);
	/* Determine the size of the remaining unused block */
	unused_block_size = chunks ? *((size_t *)block_ptr) : (size_t)getpagesize();
	/* Calculate the pointer to the next block */
	next_block = (char *)block_ptr + std_block_size;
	/* Check if there is enough space in the current block */
	while (unused_block_size < std_block_size + sizeof(size_t) * 2)
	{
		/* If not, allocate a new page */
		next_block = allocate_new_page(block_zero, std_block_size,
										&unused_block_size);
		if (!next_block)
			return (NULL);
	}
	/* Update the size of the next block and the current block */
	*((size_t *)next_block) = unused_block_size - std_block_size;
	*((size_t *)block_ptr) = std_block_size;
	/* Increment the number of allocated chunks */
	chunks++;
	/* Return the pointer to the allocated memory */
	return ((char *)block_ptr + sizeof(size_t));
}

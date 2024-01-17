#include "malloc.h"

/**
* _calloc - allocates memory for an array of elements
* @nmemb: number of elements in the array
* @size: size of each element
* Return: pointer to the allocated memory
*/
void *_calloc(size_t nmemb, size_t size)
{
	/* Calculate the total size of the requested memory */
	size_t total_size = nmemb * size;
	/* Pointer to the allocated memory */
	void *ptr;

	/* If the requested memory is 0, return NULL */
	if (nmemb == 0 || size == 0 || total_size / nmemb != size)
	{
		return (NULL);
	}

	/* Allocate memory */
	ptr = _malloc(total_size);

	/* If the allocation fails, return NULL */
	if (ptr != NULL)
	{
		memset(ptr, 0, total_size);
	}

	/* Return a pointer to the allocated memory */
	return (ptr);
}

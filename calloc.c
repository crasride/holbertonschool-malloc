#include "malloc.h"

/**
* _calloc - allocates memory for an array of elements
* @nmemb: number of elements in the array
* @size: size of each element
* Return: pointer to the allocated memory
*/
void *_calloc(size_t nmemb, size_t size)
{
	size_t total_size = nmemb * size;
	void *ptr;

	if (nmemb == 0 || size == 0 || total_size / nmemb != size)
	{
		return (NULL);
	}

	ptr = _malloc(total_size);

	if (ptr != NULL)
	{
		memset(ptr, 0, total_size);
	}

	return (ptr);
}

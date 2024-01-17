#include "malloc.h"


void *_realloc(void *ptr, size_t size)
{
	size_t *chunk_header;
	size_t old_size = 0;
	void *new_ptr;

	if (ptr == NULL)
	{
		return (_malloc(size));
	}
	else if (size == 0)
	{
		_free(ptr);
		return (NULL);
	}
	else
	{
		chunk_header = (size_t *)ptr - 1;
		old_size = *chunk_header & ~1;

		if (size <= old_size)
		{
			return (ptr);
		}
		else
		{

			new_ptr = _malloc(size);

			if (new_ptr != NULL)
			{
				memcpy(new_ptr, ptr, old_size);
				_free(ptr);
			}
			return (new_(ptr));
		}
	}
}

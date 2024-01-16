#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Functions Task 0 */
void *naive_malloc(size_t size);

/* Functions Task 1 */
void *_malloc(size_t size);

/* Functions Task 2 */
void _free(void *ptr);

#endif /* MALLOC_H */

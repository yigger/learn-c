#include <stdio.h>
#include <stdlib.h>
#include "zmalloc.h"

#ifdef HAVE_MALLOC_SIZE
#define PREFIX_SIZE (0)
#else
#define PREFIX_SIZE (sizeof(long long))
#endif

void *zmalloc(size_t size) {
	void *ptr = malloc(size+PREFIX_SIZE);
	if(ptr == NULL) {
		exit(1);
	}
    return ptr;
}

void *zcalloc(size_t size) {
	void *ptr = calloc(1, size+PREFIX_SIZE);
	if(ptr == NULL) {
		exit(1);
	}
	return ptr;
}

void zfree(void *ptr) {
	if(ptr == NULL) return;
	free(ptr);
}

void *zrealloc(void *ptr, size_t size) {
    size_t oldsize;
    void *newptr;
    if (ptr == NULL) return zmalloc(size);
    newptr = realloc(ptr, size);
    return newptr;
}

#ifdef HAVE_MALLOC_SIZE
size_t zmalloc_size(void *ptr) {
    void *realptr = (char*)ptr-PREFIX_SIZE;
    size_t size = *((size_t*)realptr);
    /* Assume at least that all the allocations are padded at sizeof(long) by
     * the underlying allocator. */
    if (size&(sizeof(long)-1)) size += sizeof(long)-(size&(sizeof(long)-1));
    return size+PREFIX_SIZE;
}
#endif

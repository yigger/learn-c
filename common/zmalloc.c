#include <stdio.h>
#include <stdlib.h>
#include "zmalloc.h"

#define PREFIX_SIZE 0

void *zmalloc(size_t size) {
	void *ptr = malloc(size+PREFIX_SIZE);
	if(!ptr) {
		printf("内存不足，分配失败");
		exit(0);
		return NULL;
	}
#ifdef HAVE_MALLOC_SIZE
    return ptr;
#else
    *((size_t*)ptr) = size;
    return (char*)ptr+PREFIX_SIZE;
#endif
}
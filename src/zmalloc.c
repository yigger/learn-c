#include <stdio.h>
#include <stdlib.h>
#include "zmalloc.h"

#define PREFIX_SIZE 0

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
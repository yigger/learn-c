#include <stdio.h>
#include <stdlib.h>
#include "zmalloc.h"

#define PREFIX_SIZE 0

void *zmalloc(size_t size) {
	void *ptr = malloc(size+PREFIX_SIZE);
	if(ptr == NULL) {
		printf("error");
		exit(0);
	}
    return ptr;
}
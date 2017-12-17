#ifndef __ZMALLOC_H
#define __ZMALLOC_H

#define HAVE_MALLOC_SIZE 1

void *zmalloc(size_t size);
void *zcalloc(size_t size);
void zfree(void *ptr);
void *zrealloc(void *ptr, size_t size);
size_t zmalloc_size(void *ptr);

#endif
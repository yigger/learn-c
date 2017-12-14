#ifndef __SDS_H
#define __SDS_H

#include <sys/types.h>

// 最大分配长度
#define SDS_MAX_PREALLOC (1024*1024)

typedef char *sds;

typedef struct sdshdr {
    int len;
    int free;
    char buf[];
} sdshdr;

sds sdsnewlen(const void *init, size_t initlen);
sds sdsnew(const char *init);
sds sdsempty(void);

#endif
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

static inline size_t sdslen(const sds s) {
    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
    return sh->len;
}

static inline size_t sdsavail(const sds s) {
    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
    return sh->free;
}

sds sdsnewlen(const void *init, size_t initlen);
sds sdsnew(const char *init);
sds sdsempty(void);
sds sdsdup(const sds s);
void sdsfree(sds s);
void sdsclear(sds s);
size_t sdsavail(const sds s);
sds sdsgrowzero(sds s, size_t len);

sds sdsMakeRoomFor(sds s, size_t addlen);

#endif
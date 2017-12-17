#include <stdio.h>
#include <string.h>
#include "sds.h"
#include "zmalloc.h"

sds sdsnewlen(const void *init, size_t initlen) {
    struct sdshdr *sh;

    if(init) {
        sh = zmalloc(sizeof(struct sdshdr)+initlen+1);
    } else {
        sh = zcalloc(sizeof(struct sdshdr)+initlen+1);
    }

    if(sh == NULL) return NULL;
    sh->len = initlen;
    sh->free = 0;
    
    if(initlen && init) {
        //从源src所指的内存地址的起始位置开始拷贝n个字节到目标dest所指的内存地址的起始位置中
        memcpy(sh->buf, init, initlen);
    }
    sh->buf[initlen] = '\0';

    return (char*)sh->buf;
}

sds sdsnew(const char *init) {
    size_t initlen = (init == NULL) ? 0 : strlen(init);
    return sdsnewlen(init, initlen);
}

sds sdsempty(void) {
    return sdsnewlen("", 0);
}

sds sdsdup(const sds s) {
    return sdsnewlen(s, strlen(s));
}

void sdsfree(sds s) {
    if (s == NULL) return;
    zfree(s-sizeof(struct sdshdr));
}

void sdsclear(sds s) {
    struct sdshdr *sh = (void*) (s - (sizeof(struct sdshdr)));
    sh->free += sh->len;
    sh->len = 0;
    sh->buf[0] = '\0';
}

/*
 * 将 sds 扩充至指定长度，未使用的空间以 0 字节填充。
 *
 * 返回值
 *  sds ：扩充成功返回新 sds ，失败返回 NULL
 *
 * 复杂度：
 *  T = O(N)
 */
sds sdsgrowzero(sds s, size_t len) {
    struct sdshdr *sh = (void*)(s-sizeof(struct sdshdr));
    size_t totlen, curlen = sh->len;
    if(len <= curlen) return s;

    s = sdsMakeRoomFor(s, len);

    if(s == NULL) return NULL;
    sh = (void*)(s-(sizeof(struct sdshdr)));
    memset(s+curlen, 0, len-curlen+1);
    totlen = sh->len+sh->free;
    sh->len = len;
    sh->free = totlen - sh->len;

    return s;
}

/*
 * 对 sds 中 buf 的长度进行扩展，确保在函数执行之后，
 * buf 至少会有 addlen + 1 长度的空余空间
 * （额外的 1 字节是为 \0 准备的）
 *
 * 返回值
 *  sds ：扩展成功返回扩展后的 sds
 *        扩展失败返回 NULL
 *
 * 复杂度
 *  T = O(N)
 */
sds sdsMakeRoomFor(sds s, size_t addlen) {
    struct sdshdr *sh, *newsh;
    size_t len, newlen;

    size_t free = sdsavail(s);
    if(addlen <= free) return s;

    len = strlen(s);
    newlen = len + addlen;

    if(newlen < SDS_MAX_PREALLOC) {
        newlen *= 2;
    } else {
        newlen += SDS_MAX_PREALLOC;
    }

    sh = (void*)(s-sizeof(struct sdshdr));
    newsh = zrealloc(sh, newlen+1+sizeof(struct sdshdr));
    if(newsh == NULL) return NULL;

    newsh->free = newlen - len;
    return newsh->buf;
}

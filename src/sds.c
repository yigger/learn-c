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
    
    if(initlen && init)
        memcpy(sh->buf, init, initlen);
    
    sh->buf[initlen] = '\0';

    return (char*)sh->buf;
}
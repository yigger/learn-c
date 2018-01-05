#include <stdio.h>

#include "dict.h"
#include "zmalloc.h"


static void _dictReset(dictht *ht) {
    ht->table = NULL;
    ht->size = 0;
    ht->sizemask = 0;
    ht->used = 0;
}

int _dictInit(dict *d, dictType *type, void *privDataPtr) {
    _dictReset(&d->ht[0]);
    _dictReset(&d->ht[1]);

    d->type = type;
    d->privdata = privDataPtr;

    d->rehashidx = -1;
    d->iterators = 0;
    return DICT_OK;
}

dict *dictCreate(dictType *type, void *privDataPtr) {
    dict *d = zmalloc(sizeof(*d));
    _dictInit(d, type, privDataPtr);
    return d;
}

// 把键值对插入 hash
int dictAdd(dict *d, void *key, void *val) {
    dictEntry *entry = dictAddRaw(d, key);

}

dictEntry *dictAddRaw(dict *d, void *key) {
    int index;
    dictEntry *entry;
    dictht *ht;

    // 值已存在
    if((index = _dictKeyIndex(d, key)) == -1) 
        return NULL;

    ht = &d->ht[0];

    entry = zmalloc(sizeof(*entry));
    entry->next = ht->table[index];

}

static int _dictKeyIndex(dict *d, const void *key) {
    unsigned int h, idx, table;
    dictEntry *he;

    h = dictHashKey(d, key);

}
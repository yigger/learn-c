#include <stdint.h>

#ifndef __DICT_H
#define __DICT_H

/*
 * 字典的操作状态
 */
// 操作成功
#define DICT_OK 0
// 操作失败（或出错）
#define DICT_ERR 1

/**
 * 哈希表节点
*/ 
typedef struct dictEntry {
    void *key;
    union {
        void *val;
        uint64_t u64;
        int64_t s64;
    } v;
    struct dictEntry *next;
} dictEntry;

/*
 * 字典类型特定函数
 */
typedef struct dictType {
    // 计算哈希值的函数
    unsigned int (*hashFunction)(const void *key);

    // 复制键的函数
    void *(*keyDup)(void *privdata, const void *key);

    // 复制值的函数
    void *(*valDup)(void *privdata, const void *obj);

    // 对比键的函数
    int (*keyCompare)(void *privdata, const void *key1, const void *key2);

    // 销毁键的函数
    void (*keyDestructor)(void *privdata, void *key);
    
    // 销毁值的函数
    void (*valDestructor)(void *privdata, void *obj);

} dictType;

/**
 * 哈希表
*/ 
typedef struct dictht {
    dictEntry **table;

    unsigned long size;

    // 哈希表大小掩码，用于计算索引值
    // 总是等于 size - 1
    unsigned long sizemask;

    // 该哈希表已有节点的数量
    unsigned long used;
} dictht;

/**
 * 字典 
*/
typedef struct dict {
    dictType *type;
    void *privdata;
    dictht ht[2];
    int rehashidx;
    int iterators;
} dict;

// Api
dict *dictCreate(dictType *type, void *privDataPtr);
int dictAdd(dict *d, void *key, void *val);


//计算给定键的哈希值
#define dictHashKey(d, key) (d)->type->hashFunction(key)

#endif

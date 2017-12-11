#include <stdio.h>
#include <stdlib.h>
#include "zmalloc.h"
#include "adlist.h"

list *listCreate() {
	list *list;
	if((list = zmalloc(sizeof(*list))) == NULL)
		return NULL;
	
	list->head = list->tail = NULL;
    list->len = 0;
    list->free = NULL;
    list->dup = NULL;
    list->match = NULL;
	
	return list;
}

list *listAddNodeHead(list *list, void *value) {
    listNode *node;

    if ((node = zmalloc(sizeof(*node))) == NULL) 
        return NULL;

    node->value = value;
    if (list->len == 0) {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    } else {
        node->prev = NULL;
        node->next = list->head;
        list->head->prev = node;
        list->head = node;
    }
    list->len++;
    return list;
}

list *listAddNodeTail(list *list, void *value) {
    listNode *node;
    if((node = zmalloc(sizeof(*node))) == NULL) 
        return NULL;
    
    node->value = value;
    if(list->len == 0) {
        list->head = list->tail = node;
        node->prev = node->next = NULL;
    } else {
        node->prev = list->tail;
        node->next = NULL;
        list->tail->next = node;
        list->tail = node;
    }

    list->len ++;
    return list;
}

list *listInsertNode(list *list, listNode *old_node, void *value, int after) {
    listNode *node;
    if((node = zmalloc(sizeof(listNode*))) == NULL) {
        return NULL;
    }

    node->value = value;
    if(after) {
        node->prev = old_node;
        node->next = old_node->next;
        // old_node->next = node; // 不能这么写，当 old_node = list->tail 的时候会出错，因为此时 list->tail = NULL
        if(list->tail == old_node) {
            list->tail = node;
        }
    } else {
        node->next = old_node;
        node->prev = old_node->prev;
        // old_node->prev = node; // 不能这么写，当 old_node = list->head 的时候会出错，因为此时 list->head = NULL
        if(list->head == old_node) {
            list->head = node;
        }
    }

    if(node->prev != NULL) {
        node->prev->next = node;
    }

    if(node->next != NULL) {
        node->next->prev = node;
    }

    list->len ++;
    return list;
}

listNode *listSearchKey(list *list, void *key) {
    listIter iter;
    listNode *node;

    listRewind(list, &iter);
    while((node = listNext(&iter)) != NULL) {
        if(list->match) {
            if(list->match(node->value, key)) {
                return node;
            }
        } else {
            if(node->value == key) {
                return node;
            }
        }
    }
    return NULL;
}

void listRewind(list *list, listIter *li) {
    li->next = list->head;
    li->direction = AL_START_HEAD;
}

void listRewindTail(list *list, listIter *li) {
    li->next = list->tail;
    li->direction = AL_START_TAIL;
}

listNode *listNext(listIter *iter) {
    listNode *current_node = iter->next;

    if(current_node != NULL) {
        if(iter->direction == AL_START_HEAD) {
            iter->next = current_node->next;
        } else {
            iter->next = current_node->prev;
        }
    }
    return current_node;
}

void listDelNode(list *list, listNode *node) {
    if(node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    } 

    if(node->next) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }
    if(list->free) list->free(node->value);
    zfree(node);
    list->len--;
}

void printList(list *list) {
    if(list->head != NULL) {
        listNode *node;
        node = list->head;
        printf("Len = %d..\t", (int)listLength(list));
        while(node != NULL) {
            printf("%s", (char*)listNodeValue(node));
            if(node->next != NULL) {
                printf(" -> ");
            }
            node = node->next;
        }
        printf("\n");
    }
}

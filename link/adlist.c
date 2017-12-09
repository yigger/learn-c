#include <stdio.h>
#include <stdlib.h>
#include "../common/zmalloc.h"
#include "adlist.h"

list *listCreate() {
	list *list;
	if((list = (struct list*)zmalloc(sizeof(list))) == NULL) {
		printf("error ");
		exit(0);
		return NULL;
	}
	list->head = list->tail = NULL;
	list->len = 0;
	return list;
}

list *listAddNodeHead(list *list, void *value) {
    listNode *node;

    if ((node = (struct listNode*)zmalloc(sizeof(*node))) == NULL)
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


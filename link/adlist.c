#include <stdio.h>
#include <stdlib.h>
#include "../common/zmalloc.h"
#include "adlist.h"

list *listCreate(void) {
	list *list;
	if((list = zmalloc(sizeof(list))) == NULL) {
		return NULL;
	}

	list->head = NULL;
	list->tail = NULL;
	list->len = 0;
	list->dup = NULL;
	list->free = NULL;
	list->match = NULL;
	return list;
}

list *listAddNodeHead(list *list, void *value) {
	listNode *node;
	if((node = zmalloc(sizeof(*node))) == NULL) {
		return NULL;
	}

	node->value = value;

	if (list->len == 0) {
		node->prev = node->next = NULL;
		list->head = list->tail = node;
	} else {
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
		node->prev = NULL;
	}

	list->len ++;
	return list;
}


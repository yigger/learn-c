#include <stdio.h>
#include <stdlib.h>
#include "src/adlist.h"

int main() {
	list *list;
	printf("Start to create list\n");
	list = listCreate();

	list = listAddNodeHead(list, "cccb");
	printList(list);

	list = listAddNodeTail(list, "ab");
	printList(list);
	
	listInsertNode(list, list->head, "test", AL_START_HEAD);
	printList(list);

	listInsertNode(list, list->head, "addToTail", AL_START_TAIL);
	printList(list);

	listNode *searchNode;
	searchNode = listSearchKey(list, "addToTail");
	if(searchNode != NULL) {
		listInsertNode(list, searchNode, "afterInsertValue", AL_START_TAIL);
		printList(list);
	} else {
		printf("can't search node\n");
	}
	
	listDelNode(list, searchNode);
	printList(list);


	return 0;
}

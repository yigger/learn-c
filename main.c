#include <stdio.h>
#include <stdlib.h>
#include "link/adlist.h"

int main() {
	list *list;
	printf("Start to create list\n");
	list = listCreate();
	// insert a value to list head
	list = listAddNodeHead(list, "cccb");
	printf("%s\n", (char *)list->head->value);

	// output list len
	printf("Len = %d\n", (int)listLength(list));

	// insert a value to tail
	list = listAddNodeTail(list, "ab");
	// printf("%s \n", (char*)list->tail->value);

	printf("%s\n", (char *)listNodeValue(list->tail));

	return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include "link/adlist.h"

int main() {
		list *list;
		printf("Start to create list\n");
		list = listCreate();
		printf("Len = %d\n", (int)listLength(list));

		/*list = listAddNodeHead(list, "cccb");
		printf("create over\n");
		printf("result = %s \n", list->head->value);
		*/
		free(list);
		return 0;
}
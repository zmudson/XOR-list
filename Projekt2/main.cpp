#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

#define MAX_COMMAND_LENGTH 15

int main() {

	char command[MAX_COMMAND_LENGTH];
	int number;
	LinkedList list;

	while (scanf("%s", command) != EOF) {
		if (!strcmp("ADD_BEG", command)) {
			scanf("%d", &number);
			list.addFirst(number);
		}
		else if (!strcmp("ADD_END", command)) {
			scanf("%d", &number);
			list.addLast(number);
		}
		else if (!strcmp("ACTUAL", command)) {
			Node* actual = list.getActual();
			if (actual != nullptr)
				printf("%d\n", actual->getKey());
			else
				printf("NULL\n");
		}
		else if (!strcmp("NEXT", command)) {
			Node* next = list.getNext();
			if (next != nullptr)
				printf("%d\n", next->getKey());
			else
				printf("NULL\n");
		}
		else if (!strcmp("PREV", command)) {
			Node* previous = list.getPrevious();
			if (previous != nullptr)
				printf("%d\n", previous->getKey());
			else
				printf("NULL\n");
		}
		else if (!strcmp("DEL_BEG", command)) {
			list.deleteFirst();
		}
		else if (!strcmp("DEL_END", command)) {
			list.deleteLast();
		}
		else if (!strcmp("DEL_ACT", command)) {
			list.deleteActual();
		}
		else if (!strcmp("PRINT_FORWARD", command)) {
			list.printForward();
		}
		else if (!strcmp("PRINT_BACKWARD", command)) {
			list.printBackward();
		}
		else if (!strcmp("ADD_ACT", command)) {
			scanf("%d", &number);
			list.addActual(number);
		}
		else if (!strcmp("DEL_VAL", command)) {
			scanf("%d", &number);
			list.deleteValues(number);
		}
	}
	return 0;
}
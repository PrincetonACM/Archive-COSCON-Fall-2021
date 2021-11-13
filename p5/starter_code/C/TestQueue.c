#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"
#include "Queue.h"

int main() {
	// Change both these numbers for testing
	int operations = 1000000;
	int reference[1000000];
	Queue_T queue = Queue_new();

	int maxOperationsPer = 0;
	int lastOperationCount = 0;
    int op;
    int item;

	for (op = 0; op < operations; op++) {
		item = rand();
		reference[op] = item;
		Queue_enqueue(queue, &reference[op]);

		maxOperationsPer = (maxOperationsPer > getOperationCount() - lastOperationCount) ? maxOperationsPer : (getOperationCount() - lastOperationCount);
		lastOperationCount = getOperationCount();
	}

	for (op = 0; op < operations; op++) {
		if (*((int*) Queue_dequeue(queue)) != reference[op]) {
			printf("Queue does not work.");
			return 0;
		}

		maxOperationsPer = (maxOperationsPer > getOperationCount() - lastOperationCount) ? maxOperationsPer : (getOperationCount() - lastOperationCount);
		lastOperationCount = getOperationCount();
	}

	printf("Queue operations    : %d\n", 2 * operations);
	printf("Stack operations per: %d\n\n", maxOperationsPer);

	return 0;
}

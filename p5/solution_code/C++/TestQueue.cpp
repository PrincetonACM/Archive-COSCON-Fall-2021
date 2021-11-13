#include <cstdio>
#include "Queue.cpp"

// Compile just TestQueue.cpp, since this directly includes the implementations of Queue.cpp and Stack.cpp

int main() {
	// Change both these numbers for testing
	int operations = 1000000;
	int reference[1000000];
	Queue<int> queue;

	int maxOperationsPer = 0;
	int lastOperationCount = 0;

	for (int op = 0; op < operations; op++) {
		int item = rand();
		reference[op] = item;
		queue.enqueue(item);

		maxOperationsPer = std::max(maxOperationsPer, getOperationCount() - lastOperationCount);
		lastOperationCount = getOperationCount();
	}

	for (int op = 0; op < operations; op++) {
		if (queue.dequeue() != reference[op]) {
			printf("Queue does not work.");
			return 0;
		}

		maxOperationsPer = std::max(maxOperationsPer, getOperationCount() - lastOperationCount);
		lastOperationCount = getOperationCount();
	}

	printf("Queue operations    : %d\n", 2 * operations);
	printf("Stack operations per: %d\n\n", maxOperationsPer);

	return 0;
}

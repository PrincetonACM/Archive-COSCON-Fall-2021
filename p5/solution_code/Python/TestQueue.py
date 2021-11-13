import math
import random
from Stack import Stack
from Queue import Queue

operations = 1000000

reference = []
queue = Queue()

maxOperationsPer = 0
lastOperationCount = 0

for op in range(operations):
    item = math.floor(random.random() * (2**31 - 1))
    reference.append(item)
    queue.enqueue(item)

    maxOperationsPer = max(maxOperationsPer, Stack.ops - lastOperationCount)
    lastOperationCount = Stack.ops

for op in range(operations):
    if (queue.dequeue() != reference[op]):
        print("Queue does not work.")
        exit()

    maxOperationsPer = max(maxOperationsPer, Stack.ops - lastOperationCount)
    lastOperationCount = Stack.ops

print("Queue operations    : " + str(2 * operations))
print("Stack operations per: " + str(maxOperationsPer) + "\n")

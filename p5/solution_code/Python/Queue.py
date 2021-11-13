from Stack import Stack

class Queue:
    def __init__(self):
        self.enqueueingStacks = Stack()
        self.dequeueingStacks = Stack()

        self.flipTo = Stack()
        self.flipFrom = Stack()
        self.enqueueTo = Stack()

        self.dequeueFrom = Stack()
        self.dequeueFromLast = Stack()

        self.stackExponent = 0
        self.dequeueing = False

    def enqueue(self, item):
        if self.flipFrom.size() > 0:
            self.flipTo.push(self.flipFrom.pop())

        self.enqueueTo.push(item)

        if self.enqueueTo.size() == 2**self.stackExponent:
            self.enqueueingStacks.push(self.flipTo)
            self.flipTo = self.flipFrom
            self.flipFrom = self.enqueueTo
            self.enqueueTo = Stack()
            self.stackExponent += 1

    def dequeue(self):
        for _ in range(4):
            if self.enqueueTo.size() > 0:
                self.dequeueFromLast.push(self.enqueueTo.pop())
            elif self.flipTo.size() > 0:
                self.flipFrom.push(self.flipTo.pop())
            elif self.flipFrom.size() > 0:
                self.dequeueFromLast.push(self.flipFrom.pop())

        if not self.dequeueing:
            while self.enqueueingStacks.size() > 0:
                self.dequeueingStacks.push(self.enqueueingStacks.pop())

            self.dequeueFrom = self.dequeueingStacks.pop()
            self.dequeueing = True

        if self.dequeueFrom.size() == 0:
            if self.dequeueingStacks.size() > 0:
                self.dequeueFrom = self.dequeueingStacks.pop()
            else:
                self.dequeueFrom = self.dequeueFromLast

        return self.dequeueFrom.pop()

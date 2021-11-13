class Stack:
    # Note: this variable will have a different name in our version of the testing file, so don't try to change it in your code.
    ops = 0

    def __init__(self):
        self.stack = []

    # Pushes item onto the stack.
    def push(self, item):
        Stack.ops += 1
        self.stack.append(item)

	# Pops and returns the item from the top of the stack.
    def pop(self):
        Stack.ops += 1
        return self.stack.pop()

	# Returns the number of items on the stack. Does not count as an operation.
    def size(self):
        return len(self.stack)

#include <stack>

// Note: this variable will have a different name in our version of the testing file, so don't try to change it in your code.
static int ops;

template <typename Item>
class Stack {
    private:
        std::stack<Item> stack;

    public:
        // Pushes item onto the stack.
        void push(Item item) {
            ops++;
            stack.push(item);
        }

        // Pops and returns the item from the top of the stack.
        Item pop() {
            ops++;
            Item top = stack.top();
            stack.pop();
            return top;
        }

        // Returns the number of items on the stack. Does not count as an operation.
        int size() {
            return stack.size();
        }
};

int getOperationCount() {
    return ops;
}

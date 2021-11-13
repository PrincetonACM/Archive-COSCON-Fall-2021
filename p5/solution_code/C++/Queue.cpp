#include <tgmath.h>
#include "Stack.cpp"

template <typename Item>
class Queue {
    private:
	    Stack<Stack<Item>> enqueueingStacks;
	    Stack<Stack<Item>> dequeueingStacks;

	    Stack<Item> flipTo;
	    Stack<Item> flipFrom;
	    Stack<Item> enqueueTo;

	    Stack<Item> dequeueFrom;
	    Stack<Item> dequeueFromLast;

	    int stackExponent = 0;
        bool dequeueing = false;

    public:
        void enqueue(Item item) {
            if (flipFrom.size() > 0) {
                flipTo.push(flipFrom.pop());
            }

            enqueueTo.push(item);

            if (enqueueTo.size() == pow(2, stackExponent)) {
                enqueueingStacks.push(flipTo);
                flipTo = flipFrom;
                flipFrom = enqueueTo;
                enqueueTo = Stack<Item>();
                stackExponent++;
            }
        }

        Item dequeue() {
            for (int i = 0; i < 4; i++) {
                if (enqueueTo.size() > 0) {
                    dequeueFromLast.push(enqueueTo.pop());
                } else if (flipTo.size() > 0) {
                    flipFrom.push(flipTo.pop());
                } else if (flipFrom.size() > 0) {
                    dequeueFromLast.push(flipFrom.pop());
                }
            }

            if (!dequeueing) {
                while (enqueueingStacks.size() > 0) {
                    dequeueingStacks.push(enqueueingStacks.pop());
                }

                dequeueFrom = dequeueingStacks.pop();
                dequeueing = true;
            }

            if (dequeueFrom.size() == 0) {
                if (dequeueingStacks.size() > 0) {
                    dequeueFrom = dequeueingStacks.pop();
                } else {
                    dequeueFrom = dequeueFromLast;
                }
            }

            return dequeueFrom.pop();
        }
};

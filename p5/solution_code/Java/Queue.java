public class Queue<Item> {
	private Stack<Stack<Item>> enqueueingStacks = new Stack<>();
	private Stack<Stack<Item>> dequeueingStacks = new Stack<>();

	private Stack<Item> flipTo = new Stack<>();
	private Stack<Item> flipFrom = new Stack<>();
	private Stack<Item> enqueueTo = new Stack<>();

	private Stack<Item> dequeueFrom = new Stack<>();
	private Stack<Item> dequeueFromLast = new Stack<>();

	private int stackExponent = 0;
	private boolean dequeueing = false;

	public void enqueue(Item item) {
		if (flipFrom.size() > 0) {
			flipTo.push(flipFrom.pop());
		}

		enqueueTo.push(item);

		if (enqueueTo.size() == Math.pow(2, stackExponent)) {
			enqueueingStacks.push(flipTo);
			flipTo = flipFrom;
			flipFrom = enqueueTo;
			enqueueTo = new Stack<>();
			stackExponent++;
		}
	}

	public Item dequeue() {
		for (int i = 0; i < 4; i++) {
			if (enqueueTo.size() > 0) {
				dequeueFromLast.push(enqueueTo.pop());
			} else if (flipTo.size() > 0) {
				flipFrom.push(flipTo.pop());
			} else if (flipFrom.size() > 0) {
				dequeueFromLast.push(flipFrom.pop());
			}
		}

		if (dequeueing == false) {
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
}

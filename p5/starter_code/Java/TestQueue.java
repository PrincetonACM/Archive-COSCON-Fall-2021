public class TestQueue {
	public static void main(String[] args) {
		int operations = 1000000;

		int[] reference = new int[operations];
		Queue<Integer> queue = new Queue<>();

		int maxOperationsPer = 0;
		int lastOperationCount = 0;

		for (int op = 0; op < operations; op++) {
			int item = (int)(Math.random() * Integer.MAX_VALUE);
			reference[op] = item;
			queue.enqueue(item);

			maxOperationsPer = Math.max(maxOperationsPer, Stack.getOperationCount() - lastOperationCount);
			lastOperationCount = Stack.getOperationCount();
		}

		for (int op = 0; op < operations; op++) {
			if (queue.dequeue() != reference[op]) {
				System.out.println("Queue does not work.");
				return;
			}

			maxOperationsPer = Math.max(maxOperationsPer, Stack.getOperationCount() - lastOperationCount);
			lastOperationCount = Stack.getOperationCount();
		}

		System.out.println(String.format("Queue operations    : %d", 2 * operations));
		System.out.println(String.format("Stack operations per: %d\n", maxOperationsPer));
	}
}

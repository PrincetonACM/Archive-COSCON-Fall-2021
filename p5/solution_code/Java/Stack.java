import java.util.LinkedList;

public class Stack<Item> {
	private static int ops = 0;

	private final LinkedList<Item> stack = new LinkedList<>();

	// Pushes item onto the stack.
	public void push(Item item) {
		ops++;
		stack.addLast(item);
	}

	// Pops and returns the item from the top of the stack.
	public Item pop() {
		ops++;
		return stack.removeLast();
	}

	// Returns the number of items on the stack. Does not count as an operation.
	public int size() {
		return stack.size();
	}

	// For testing purposes.
	public static int getOperationCount() {
		return ops;
	}
}

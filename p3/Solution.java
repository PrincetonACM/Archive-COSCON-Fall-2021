import java.io.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        String[] inputs = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int n = Integer.parseInt(inputs[0]);
        int m = Integer.parseInt(inputs[1]);

        // Set up our data structure, which will consist of an array storing the occupation bits
        // and a Fenwick tree (see the solution for more details on what the Fenwick tree does)
        int[] occBits = new int[n + 1];
        int[] fenwick = new int[n + 1];

        // Process all m queries
        for (int i = 0; i < m; i++) {
            int type; int index;

            // Parse the query
            String[] line = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");
            type = Integer.parseInt(line[0]); index = Integer.parseInt(line[1]);

            index++; // Since we don't use the first element of the fenwick tree
            switch(type) {
                case 1:
                    System.out.println(occBits[index]);
                    break;

                case 2:
                    occBits[index] = 1 - occBits[index];
                    while (index <= n) {
                        fenwick[index] = 1 - fenwick[index];
                        index += index & (-index); // adds the value of the last set bit
                    }
                    break;

                case 3:
                    int sum = 0;
                    while (index > 0) {
                        sum += fenwick[index];
                        sum = sum % 2;
                        index -= index & (-index); // unsets the last set bit
                    }
                
                    System.out.println(sum);
            }
        }
    }
}
import java.io.*;

public class NaiveSolution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        String[] inputs = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int n = Integer.parseInt(inputs[0]);
        int m = Integer.parseInt(inputs[1]);

        // Set up our data structure, which will consist of an array storing the occupation bits
        // and a Fenwick tree (see the solution for more details on what the Fenwick tree does)
        int[] occBits = new int[n];

        // Process all m queries
        for (int i = 0; i < m; i++) {
            int type; int index;

            // Parse the query
            String[] line = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");
            type = Integer.parseInt(line[0]); index = Integer.parseInt(line[1]);

            switch(type) {
                case 1:
                    System.out.println(occBits[index]);
                    break;

                case 2:
                    occBits[index] = 1 - occBits[index];
                    break;

                case 3:
                    int sum = 0;
                    for (int j = 0; j <= index; j++) sum = (sum + occBits[j]) % 2;
                
                    System.out.println(sum);
            }
        }
    }
}
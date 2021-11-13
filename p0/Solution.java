import java.io.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        String[] firstMultipleInput = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");

        int n = Integer.parseInt(firstMultipleInput[0]);
        int m = Integer.parseInt(firstMultipleInput[1]);

        String[] productivitiesTemp = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");
        bufferedReader.close();
      
        int[] productivities = new int[n]; // Technically unnecessary (why?), but it's ok to keep
        for (int i = 0; i < n; i++) {
            productivities[i] = Integer.parseInt(productivitiesTemp[i]);
        }

        int diff = 0; // The total differential in productivity we can attain
        for (int p : productivities) {
            if (m > p) diff += m - p;
        }

        System.out.println(diff);
    }
}

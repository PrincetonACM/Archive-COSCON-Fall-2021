import java.lang.Math;
import java.io.*;

class Solution {

    public static int maximize_cost(int[] costs) {
        int n = costs.length;
        if (n == 1)
            return costs[0];

        int a = costs[0], b = Math.max(costs[0], costs[1]);

        for (int i = 2; i < n; i++)
        {
            int c = Math.max(a + costs[i], b);
            a = b;
            b = c;
        }

        return b;
    }

    public static void main(String[] args) throws IOException {

        // Input is handled for you
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));

        int n = Integer.parseInt(bufferedReader.readLine().trim());
        String[] costsTemp = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");
        bufferedReader.close();

        int[] costs = new int[n];
        for (int i = 0; i < n; i++) costs[i] = Integer.parseInt(costsTemp[i]);

        System.out.println(maximize_cost(costs));
    }
}
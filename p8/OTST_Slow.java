import java.lang.Math;
import java.io.*;

public class OTST_Slow {

    public static long M[][]; // DP Array to store opt
    public static long W[]; // Store partial sums of the weights so we can answer weight queries quickly
    public static boolean ch[][]; // Do we know the solution to the current DP problem already?
    public static int n;

    // Calculate partial sums of weights from index i to j, inclusive
    public static long w(int i, int j)
    {
        if (i > j) return 0;
        if (i == 0) return W[j];
        else return W[j] - W[i - 1];
    }

    // Implementation of DP calculation
    public static long _opt(int i, int j)
    {
        long s = 0xffffff;

        for (int k1 = i; k1 <= j - 1; k1++) {
            for (int k2 = k1 + 1; k2 <= j; k2++) {
                // The cost that we will incur if we choose k1 as the root
                long cost_1 = opt(i, k1 - 1) + opt(k1 + 1, k2) + opt(k2 + 1, j);
                cost_1 += w(i, k1 - 1) + w(k1 + 1, j);

                // The cost that we will incur if we choose k2 as the root
                long cost_2 = opt(i, k1) + opt(k1 + 1, k2 - 1) + opt(k2 + 1, j);
                cost_2 += w(i, k2 - 1) + w(k2 + 1, j);

                s = Math.min(s, cost_1); s = Math.min(s, cost_2);
            }
        }

        return s;
    }

    // Memoizer for opt (makes DP tractable)
    public static long opt(int i, int j)
    {
        if (i < 0 || j < 0 || i >= n || j >= n) return 0;

        if (i >= j) {
            return 0;
        }

        if (ch[i][j])
            return M[i][j];
        else {
            ch[i][j] = true;
            return M[i][j] = _opt(i, j);
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        String[] inputs = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");
        n = Integer.parseInt(inputs[0]);

        M = new long[n][n];
        W = new long[n];
        ch = new boolean[n][n];

        W[0] = Integer.parseInt(inputs[1]);
        for(int i = 1; i < n; ++i) {
            W[i] = Integer.parseInt(inputs[i + 1]);
            W[i] += W[i - 1];
        }

        System.out.println(opt(0, n - 1));
    }
}

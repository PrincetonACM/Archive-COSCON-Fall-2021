import java.lang.Math;
import java.io.*;

public class OBST_Slow {

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
        for (int k = i; k <= j; ++k)
            s = Math.min(s, opt(i, k - 1) + opt(k + 1, j) + w(i, k - 1) + w(k + 1, j));
        return s;
    }

    // Memoizer for opt (makes DP tractable)
    public static long opt(int i, int j)
    {
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
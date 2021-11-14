import java.lang.Math;
import java.io.*;

public class OTST_Fast {

    public static long M[][][]; // DP Array to store opt; M[0] stores opt2, M[1] stores opt3 (see writeup)
    public static long W[]; // Store partial sums of the weights so we can answer weight queries quickly
    public static boolean ch[][][]; // Do we know the solution to the current DP problem already?
    public static int n;

    // Calculate partial sums of weights from index i to j, inclusive
    public static long w(int i, int j)
    {
        if (i > j) return 0;
        if (i == 0) return W[j];
        else return W[j] - W[i - 1];
    }

    // Implementation of opt2 calculation
    public static long _opt2(int i, int j)
    {
        long s = 0xffffff;

        for (int k = i; k <= j; ++k)
            s = Math.min(s, opt3(i, k) + opt3(k + 1, j));

        return s;
    }

    // Memoizer for opt2 calculation
    public static long opt2(int i, int j)
    {
        if (i < 0 || j < 0 || i >= n || j >= n) return 0;

        if (i > j) {
            return 0;
        }

        if (ch[0][i][j])
            return M[0][i][j];
        else {
            ch[0][i][j] = true;
            return M[0][i][j] = _opt2(i, j);
        }
    }

    // Implementation of opt3 calculation
    public static long _opt3(int i, int j)
    {
        long s = 0xffffff;

        for (int k = i ; k <= j; k++) {
            // The cost we incur if we choose the dummy node to be a right child
            long cost_1 = opt3(i, k - 1) + w(i, k - 1) + opt2(k + 1, j) + w(k + 1, j);

            // The cost we incur if we choose the dummy node to be a left child
            long cost_2 = opt2(i, k - 1) + w(i, k - 1) + opt3(k + 1, j) + w(k + 1, j);

            s = Math.min(s, cost_1); s = Math.min(s, cost_2);
        }

        return s;
    }

    // Memoizer for opt3 calculation
    public static long opt3(int i, int j)
    {
        if (i < 0 || j < 0 || i >= n || j >= n) return 0;

        if (i >= j) {
            return 0;
        } 

        if (ch[1][i][j])
            return M[1][i][j];
        else {
            ch[1][i][j] = true;
            return M[1][i][j] = _opt3(i, j);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(System.in));
        String[] inputs = bufferedReader.readLine().replaceAll("\\s+$", "").split(" ");
        n = Integer.parseInt(inputs[0]);

        M = new long[2][n][n];
        W = new long[n];
        ch = new boolean[2][n][n];

        W[0] = Integer.parseInt(inputs[1]);
        for(int i = 1; i < n; ++i) {
            W[i] = Integer.parseInt(inputs[i + 1]);
            W[i] += W[i - 1];
        }

        System.out.println(opt3(0, n - 1));
    }
}

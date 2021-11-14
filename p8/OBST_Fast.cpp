#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <memory.h>

using namespace std;
#define MAXN 3000

long M[MAXN][MAXN]; // DP Array to store opt
long W[MAXN]; // Store partial sums of the weights so we can answer weight queries quickly
long K[MAXN][MAXN]; // Index set (corresponds to K_B in the writeup)
long ch[MAXN][MAXN];
long n;

long opt(long i, long j); // Calculate the DP recurrence

// Calculate partial sums of weights from index i to j, inclusive
long w(long i, long j)
{
  if (i == 0) return W[j];
  else return W[j] - W[i - 1];
}

// Implementation of DP calculation
long _opt(long i, long j)
{
  long s = 0xffffff;

  opt(i, j-1); opt(i+1, j);

  // Calculate left and right endpoints (this takes into account edge cases)
  long L = K[i][j - 1] == -1 ? i : K[i][j - 1],
      R = K[i + 1][j] == -1 ? j : K[i + 1][j];

  for (long k = L, ps; k <= R; ++k)
    if ((ps = opt(i, k - 1) + opt(k + 1, j) + w(i, k - 1) + w(k + 1, j)) <= s) {
      s = ps;
      K[i][j] = k;
    }

  return s;
}

// Memoizer for opt (makes DP tractable)
long opt(long i, long j)
{
  if (i == j || j < i) {
    K[i][j] = -1;
    return 0;
  }

  if (ch[i][j])
    return M[i][j];
  else {
    ch[i][j] = 1;
    return M[i][j] = _opt(i, j);
  }
}

int main()
{
  cin >> n;  
  memset(M, 0, sizeof(M));
  memset(W, 0, sizeof(W));
  memset(K, 0, sizeof(K));
  memset(ch, 0, sizeof(ch));

  // Precompute partial sums of weights
  cin >> W[0];
  for(long i = 1; i < n; ++i) {
    cin >> W[i];
    W[i] += W[i - 1];
  }

  printf("%ld\n", opt(0, n-1));
  return 0;
}


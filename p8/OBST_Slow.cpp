#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <memory.h>

using namespace std;
#define MAXN 4000

long M[MAXN][MAXN]; // DP Array to store opt
long W[MAXN]; // Store partial sums of the weights so we can answer weight queries quickly
long ch[MAXN][MAXN]; // Do we know the solution to the current DP problem already?
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
  for (long k = i; k <= j; ++k)
    s = min(s, opt(i, k - 1) + opt(k + 1, j) + w(i, k - 1) + w(k + 1, j));
  return s;
}

// Memoizer for opt (makes DP tractable)
long opt(long i, long j)
{
  if (i == j || j < i) {
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

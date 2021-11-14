#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <memory.h>

using namespace std;
#define MAXN 500

long M[MAXN][MAXN]; // Stores dynamic programming array for opt
long W[MAXN]; // Stores partial sums of weight function
long ch[MAXN][MAXN];
long n;

long opt(long i, long j); // Calculate the DP recurrence

// Calculate partial sums of weights from index i to j, inclusive
long w(long i, long j)
{
  if (i > j) return 0;
  if (i == 0) return W[j];
  else return W[j] - W[i - 1];
}

// Implementation of opt calculation
long _opt(long i, long j)
{
  long s = 0xffffff;

  for (int k1 = i; k1 <= j - 1; k1++) {
    for (int k2 = k1 + 1; k2 <= j; k2++) {
      // In either case, this is a cost we will have to incur
      long sunk_cost = opt(i, k1 - 1) + opt(k1 + 1, k2 - 1) + opt(k2 + 1, j);

      s = min(s, sunk_cost + w(i, k1 - 1) + w(k1 + 1, j));
      s = min(s, sunk_cost + w(i, k2 - 1) + w(k2 + 1, j));
    }
  }

  return s;
}

// Memoizer for opt calculation
long opt(long i, long j)
{
  if (i >= j) {
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
  memset(M, 0, sizeof(M));
  memset(W, 0, sizeof(W));
  memset(ch, 0, sizeof(ch));

  cin >> n;
  cin >> W[0];

  // Precompute partial sums of weight function
  for(long i = 1; i < n; ++i) {
    cin >> W[i];
    W[i] += W[i - 1];
  }

  printf("%ld\n", opt(0, n - 1));
  return 0;
}

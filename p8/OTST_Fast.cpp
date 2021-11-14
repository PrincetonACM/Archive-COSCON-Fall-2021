#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <memory.h>

using namespace std;
#define MAXN 500

long M[2][MAXN][MAXN]; // M[0] stores opt2, M[1] stores opt3 (see writeup)
long W[MAXN]; // Stores partial sums
long ch[2][MAXN][MAXN]; // Do we know the solution to the current DP problem already?
long n;

// Calculate partial sums of weights from index i to j, inclusive
long w(long i, long j)
{
  if (i > j) return 0;
  if (i == 0) return W[j];
  else return W[j] - W[i - 1];
}

// Function declarations (sibling functions are to implement memoization)
long opt2(long i, long j);
long _opt2(long i, long j);

long opt3(long i, long j);
long _opt3(long i, long j);

// Implementation of opt2 calculation
long _opt2(long i, long j)
{
  long s = 0xffffff;

  for (long k = i; k <= j; ++k)
    s = min(s, opt3(i, k) + opt3(k + 1, j));

  return s;
}

// Memoizer for opt2 calculation
long opt2(long i, long j)
{
  if (i < 0 || j < 0 || i >= n || j >= n) return 0;

  if (i > j) {
    return 0;
  }

  if (ch[0][i][j])
    return M[0][i][j];
  else {
    ch[0][i][j] = 1;
    return M[0][i][j] = _opt2(i, j);
  }
}

// Implementation of opt3 calculation
long _opt3(long i, long j)
{
  long s = 0xffffff;

  for (int k = i ; k <= j; k++) {
    // The cost we incur if we choose the dummy node to be a right child
    long cost_1 = opt3(i, k - 1) + w(i, k - 1) + opt2(k + 1, j) + w(k + 1, j);

    // The cost we incur if we choose the dummy node to be a left child
    long cost_2 = opt2(i, k - 1) + w(i, k - 1) + opt3(k + 1, j) + w(k + 1, j);

    s = min(s, cost_1); s = min(s, cost_2);
  }

  return s;
}

// Memoizer for opt3 calculation
long opt3(long i, long j)
{
  if (i < 0 || j < 0 || i >= n || j >= n) return 0;

  if (i >= j) {
    return 0;
  } 

  if (ch[1][i][j])
    return M[1][i][j];
  else {
    ch[1][i][j] = 1;
    return M[1][i][j] = _opt3(i, j);
  }
}

int main()
{
  memset(M, 0, sizeof(M));
  memset(W, 0, sizeof(W));
  memset(ch, 0, sizeof(ch));

  // Read in arguments
  cin >> n;
  cin >> W[0];

  // Precompute partial sums of the weight function
  for(long i = 1; i < n; ++i) {
    cin >> W[i];
    W[i] += W[i - 1];
  }

  printf("%ld\n", opt3(0, n - 1));
  return 0;
}


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <memory.h>
using namespace std;
#define MAXN 3000
long M[MAXN][MAXN];
long W[MAXN];
long K[MAXN][MAXN];
long ch[MAXN][MAXN];
long n;

long w(long i, long j)
{
  if (i == 0) return W[j];
  else return W[j] - W[i - 1];
}

long opt(long i, long j);
long _opt(long i, long j)
{
  long s = 0xffffff;
  opt(i, j-1); opt(i+1, j);
  long L = K[i][j-1] == -1 ? i : K[i][j-1],
      R = K[i+1][j] == -1 ? j : K[i+1][j];
  for(long k = L, ps; k <= R; ++k)
    if ((ps = opt(i, k-1) + opt(k+1, j) + w(i, k-1) + w(k+1, j)) < s) {
      s = ps;
      K[i][j] = k;
    }
  return s;
}
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
  cin>>n;  
  memset(M, 0, sizeof(M));
    memset(W, 0, sizeof(W));
    memset(K, 0, sizeof(K));
    memset(ch, 0, sizeof(ch));
    cin >> W[0];
    for(long i = 1; i < n; ++i) {
      cin >> W[i];
      W[i] += W[i - 1];
    }
    printf("%ld\n", opt(0, n-1));
  return 0;
}

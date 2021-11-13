// OTST Slow version
// COSCON 21 Problem 8, Ruijie Fang
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <memory.h>
using namespace std;
#define MAXN 500
long M[MAXN][MAXN];
long W[MAXN];
long ch[MAXN][MAXN];
long n;

long w(long i, long j)
{
  if (i>j) return 0;
  if (i == 0) return W[j];
  else return W[j] - W[i - 1];
}

long opt(long i, long j);
long _opt(long i, long j)
{
  long s = 0xffffff;
  // Case 1: (c1, c2, k2=x, c3)
  for (int k2 = i; k2 <= j; ++k2) {
    for (int k1 = i+1; k1 < k2; ++k1) {
      s = min(s, opt(i, k1-1) + opt(k1, k2-1) + opt(k2+1, j) + w(i, k2-1) +w(k2+1,j));
    }
    // k1==k2 - 1: only c1 and c3 exists,
    // this is equal to OBST
    s = min(s, opt(i, k2 - 1) + opt(k2 + 1, j) + w(i,k2-1)+w(k2+1,j));
  }
  // Case 2: (c1, k1=x, c2, c3)
  for (int k1 = i; k1<=j; ++k1) {
    for (int k2 = k1+1; k2 < j; ++k2) {
      s = min(s, opt(i, k1-1) + opt(k1+1, k2) + opt(k2+1,j) + w(i,k1-1) + w(k1+1,j));
    }
    // k2==j: only c1, c2 exists. this is equal to obst
    s = min(s, opt(i, k1-1)+opt(k1+1,j)+w(i,k1-1)+w(k1+1,j));
  }
  return s;
}

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
    memset(M, 0, sizeof(M));
    memset(W, 0, sizeof(W));
    memset(ch, 0, sizeof(ch));
    cin >> n;
    cin >> W[0];
    for(long i = 1; i < n; ++i) {
      cin >> W[i];
      W[i] += W[i - 1];
    }
    printf("%ld\n", opt(0, n-1));
  return 0;
}

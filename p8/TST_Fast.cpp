#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <utility>
#include <memory.h>
using namespace std;
#define MAXN 500

long M[2][MAXN][MAXN]; // M[0]: opt2, M[1]: opt3
long ch[2][MAXN][MAXN];

long W[MAXN];
long n;

long w(long i, long j)
{
  if (i>j) return 0;
  if (i == 0) return W[j];
  else return W[j] - W[i - 1];
}

// Decls 
long opt2(long i, long j);
long _opt2(long i, long j);
long opt3(long i, long j);
long _opt3(long i, long j);

// OBST Part
long _opt2(long i, long j)
{
  long s = 0xffffff;
  for (long k = i ; k <= j; ++k)
    s = min(s, opt3(i, k-1) + opt3(k+1, j) + w(i, k-1) + w(k+1, j));
//  printf("OBST(%ld,%ld) result: %ld\n", i, j, s);
  return s;
}

long opt2(long i, long j)
{

  if (i == j || j < i) {
  //  printf("opt2(%ld,%ld) called\n", i, j);
    return 0;
  }
  if (ch[i][j])
    return M[0][i][j];
  else {
    ch[0][i][j] = 1;
    return M[0][i][j] = _opt2(i, j);
  }
}

// OTST Part
long _opt3(long i, long j)
{
  long s = 0xffffff;
  for (int k = i ; k <= j; ++k) {
    long c = min(opt2(i,k)+opt3(k+1,j), opt3(i,k-1)+opt2(k,j)) + w(i, k-1) + w(k+1,j);
    s = min(s, c);
  }
  return s;
}

long opt3(long i, long j)
{
  if (i == j || j < i) {
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
  cin >> n;
  cin >> W[0];
  for(long i = 1; i < n; ++i) {
    cin >> W[i];
    W[i] += W[i - 1];
  }
   printf("%ld\n", opt3(0, n-1));
  //for (int j = 0; j < n; ++j)
  //  for(int i = 0; i < j; ++i){
    //  printf("opt3(%d,%d)=%ld\n", i,j,opt3(i,j));
    //  printf("opt2(%d,%d)=%ld\n", i,j,opt2(i,j));
   // }
  return 0;
}


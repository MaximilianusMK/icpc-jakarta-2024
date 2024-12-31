#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000;

int N, M, K, Q;
string GRID[MAXN + 5];
long long D[MAXN + 5][MAXN + 5];

inline int f(int r1, int c1, int r2, int c2) {
  char u = GRID[r1][c1], v = GRID[r2][c2];
  int ret = 1;
  for (int i = 0; i < K; i++) ret *= (u - v);
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin >> N >> M >> K;
  for (int i = 0; i < N; i++) cin >> GRID[i];

  bool valid = true;
  for (int i = 1; i < N; i++) {
    for (int j = 1; j < M; j++) {
      if (f(i - 1, j - 1, i - 1, j) + f(i - 1, j, i, j) + f(i, j, i, j - 1) + f(i, j - 1, i - 1, j - 1) != 0) {
        valid = false;
        break;
      }
    }
    if (!valid) break;
  }

  if (valid) {
    D[0][0] = 0;
    for (int i = 1; i < N; i++) D[i][0] = D[i - 1][0] + f(i - 1, 0, i, 0);
    for (int j = 1; j < M; j++) D[0][j] = D[0][j - 1] + f(0, j - 1, 0, j);
    for (int i = 1; i < N; i++) {
      for (int j = 1; j < M; j++) {
        D[i][j] = min(D[i - 1][j] + f(i - 1, j, i, j), D[i][j - 1] + f(i, j - 1, i, j));
      }
    }
  }
  
  cin >> Q;
  for (int i = 0; i < Q; i++) {
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;
    r1--; c1--; r2--; c2--;
    if (!valid) cout << "INVALID" << "\n";
    else cout << D[r2][c2] - D[r1][c1] << "\n";
  }
  return 0;
}
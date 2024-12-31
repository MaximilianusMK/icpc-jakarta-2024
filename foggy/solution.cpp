#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
const int MAXLOG = 16;
const int MOD = 998244353;

int N;
int A[2][MAXN + 5];
int two[MAXN + 5];
int ST[2][MAXLOG + 5][MAXN + 5];
int parent[2][MAXN + 5], L[2][MAXN + 5], R[2][MAXN + 5];
vector<pair<int, int> > V[2];

int lg2(int i) {
  return i ? __builtin_clz(1) - __builtin_clz(i) : -1;
}

int mul(int x, int y) {
  return (1ll * x * y) % MOD;
}

int power(int x, int y) {
  if (y == 0) return 1;
  if (y == 1) return x % MOD;
  int temp = power(x, y / 2);
  temp = mul(temp, temp);
  if (y & 1) return mul(temp, x);
  return temp;
}

int findRoot(int i, int cur) {
  if (parent[i][cur] == cur) return cur;
  return parent[i][cur] = findRoot(i, parent[i][cur]);
}

bool combine(int i, int lo, int hi) {
  int rlo = findRoot(i, lo), rhi = findRoot(i, hi);
  if (rlo == rhi) return false;
  parent[i][rlo] = rhi;
  L[i][rhi] = min(L[i][rhi], L[i][rlo]);
  R[i][rhi] = max(R[i][rhi], R[i][rlo]);
  return true;
}

int query(int i, int jl, int jr) {
  int k = lg2(jr - jl + 1);
  return max(ST[i][k][jl], ST[i][k][jr - (1 << k) + 1]);
}

int left(int i, int j) {
  int l = L[i][j], r = j;
  int idx = -1;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (query(1 - i, mid, j) > A[i][j]) {
      idx = max(idx, mid);
      l = mid + 1;
    }
    else r = mid - 1;
  }
  return idx;
}

int right(int i, int j) {
  int l = j, r = R[i][j];
  int idx = N;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (query(1 - i, j, mid) > A[i][j]) {
      idx = min(idx, mid);
      r = mid - 1;
    }
    else l = mid + 1;
  }
  return idx;
}

int f(int l1, int l2, int r2, int r1) { // l1 <= l2 <= r2 <= r1  
  if (l1 <= l2 && l2 <= r2 && r2 <= r1) {
    int l = 1, r = 1;
    if (l1 > 0) l = mul(two[l2 - l1 + 1] - 1, two[l1 - 1]);
    else l = two[l2];
    if (r1 < N - 1) r = mul(two[r1 - r2 + 1] - 1, two[N - r1 - 2]);
    else r = two[N - 1 - r2];
    return mul(l, r);
  }
  return 0;
}

void precompute() {
  two[0] = 1;
  for (int i = 1; i <= N; i++) two[i] = mul(2, two[i - 1]);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < N; j++) ST[i][0][j] = A[i][j];
    for (int j = 1; j <= MAXLOG; j++) {
      for (int k = 0; k + (1 << j) <= N; k++) {
        ST[i][j][k] = max(ST[i][j - 1][k], ST[i][j - 1][k + (1 << (j - 1))]);
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin >> N;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < N; j++) {
      cin >> A[i][j];
      V[i].push_back({A[i][j], j});
      parent[i][j] = L[i][j] = R[i][j] = j;
    }
    sort(V[i].begin(), V[i].end());
  }
  precompute();
  
  int ans = 0;
  for (int i = 0; i < 2; i++) {
    for (auto &[val, j]: V[i]) {
      if (L[i][j] > 0 && A[i][L[i][j]] >= A[i][L[i][j] - 1]) combine(i, L[i][j] - 1, j);
      if (R[i][j] < N - 1 && A[i][R[i][j]] > A[i][R[i][j] + 1]) combine(i, R[i][j] + 1, j);
      
      int l = left(i, j), r = right(i, j);
      if (l == -1 && r == N) continue;

      int contrib = 0;
      if (l == -1) {
        contrib = f(L[i][j], j, r, R[i][j]);
      } 
      else if (r == N) {
        contrib = f(L[i][j], l, j, R[i][j]);
      }
      else {
        contrib = (contrib + f(L[i][j], l, r, R[i][j])) % MOD;
        contrib = (contrib + f(L[i][j], l, j, r - 1)) % MOD;
        contrib = (contrib + f(l + 1, j, r, R[i][j])) % MOD;
      }
      ans = (ans + mul(contrib, val)) % MOD;
    }
  }
  ans = (1ll * ans * power(two[N], MOD - 2)) % MOD;
  cout << ans << endl;
  return 0;
}
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;
const int MAXLOG = 30;

struct Node {
  Node* c[2];
  int sz;
  Node() {
    c[0] = c[1] = NULL;
    sz = 0;
  }
};

struct Trie {
  Node* root;
  Trie() {
    root = new Node();
  }
  void insert(int x) {
    Node* cur = root;
    for (int i = MAXLOG - 1; i >= 0; i--) {
      int xb = (x >> i) & 1;
      if (cur->c[xb] == NULL) cur->c[xb] = new Node();
      cur = cur->c[xb];
      cur->sz++;
    }
  }
  int count_smaller_xor(int x, int c) {
    Node* cur = root;
    int ret = 0;
    for (int i = MAXLOG - 1; i >= 0; i--) {
      int xb = (x >> i) & 1, cb = (c >> i) & 1;
      if (cb == 1 && cur->c[xb] != NULL) ret += cur->c[xb]->sz;
      if (cur->c[xb ^ cb] != NULL) cur = cur->c[xb ^ cb];
      else return ret;
    }
    return ret + cur->sz;
  }
} T;

int N, M;
int A[MAXN + 5];
int X[MAXN + 5];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> A[i];
  for (int i = 0; i < M; i++) cin >> X[i];
  sort(A, A + N);
  
  int min_xor = A[0] ^ A[1];
  for (int i = 2; i < N; i++) min_xor = min(min_xor, A[i - 1] ^ A[i]);

  long long ans = 0;
  for (int i = 0; i < M; i++) {
    ans += T.count_smaller_xor(X[i], min_xor);
    T.insert(X[i]);
  }

  cout << ans << "\n";
  return 0;
}
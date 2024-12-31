#include<bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int cases;
  cin >> cases;
  while (cases--) {
    int N, M, K;
    cin >> N >> M >> K;
    map<int, int> nimber;
    for (int i = 0; i < M; i++) {
      int x, y, a;
      cin >> x >> y >> a;
      nimber[x % (K + 1)] ^= a % (K + 1);
    }
    bool firstWin = false;
    for (auto &[_, val]: nimber) if (val != 0) {
      firstWin = true;
      break;
    }
    if (firstWin) cout << "Anda" << "\n";
    else cout << "Kamu" << "\n";
  }
  return 0;
}
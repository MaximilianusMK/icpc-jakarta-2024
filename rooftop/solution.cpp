#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main () {
  ll n, d, s;
  cin >> n >> d >> s;

  ll ans = s; // we can reach floor s by default.
  n = min(n, 2 * d) / s * s; // upper bound of the answer.

  while(true) {
    ll previous_floor = s;
    for (ll i = 2; i * i <= n; i++) {
      if (n % i == 0) {
        if (i % s == 0) {
          previous_floor = max(previous_floor, i);
        }
        if (n / i % s == 0) {
          previous_floor = max(previous_floor, n / i);
        }
      }
    }
    if (n - previous_floor <= d) {
      ans = max(ans, n);
      break;
    }
    n -= s; // try s floor below it.
  }
  cout << ans << endl;
}

#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int MOD = 998244353;

int n;
int a[N];

int cntrMul[N];
int mu[N];
bool isPrime[N];

int modPow(int x, int po) {
    int ret = 1;
    while (po) {
        if (po & 1) ret = 1ll * ret * x % MOD;
        po >>= 1;
        x = 1ll * x * x % MOD;
    }
    return ret;
}

void read() {
    scanf("%d", &n);
    for (int i = 1 ; i <= n ; i++) {
        scanf("%d", &a[i]);
    }
}

void prepare() {
    for (int i = 1 ; i <= n ; i++) {
        cntrMul[a[i]]++;
    }

    for (int i = 1 ; i <= n ; i++) {
        for (int j = i+i ; j <= n ; j += i) {
            cntrMul[i] += cntrMul[j];
        }
    }

    for (int i = 1 ; i <= n ; i++) {
        isPrime[i] = true;
        mu[i] = 1;
    }
    for (int i = 2 ; i <= n ; i++) {
        if (!isPrime[i]) continue;
        for (int j = i ; j <= n ; j += i) {
            isPrime[j] = false;
            mu[j] *= -1;
        }
        if (i > n / i) continue;
        for (int j = i*i ; j <= n ; j += i*i) {
            mu[j] = 0;
        }
    }
}

int solveSingle(vector<int> cnt) {
    int maxVal = cnt.size()-1;
    int ret = 0;

    vector<int> contribDivisor(maxVal + 1, 0);
    vector<int> cntWithLcm(maxVal + 1, 0);

    // calc 1st term with lcm <= maxVal
    int allContrib = 0;
    for (int i = maxVal ; i >= 1 ; i--) {
        int a = 1ll * mu[i] * modPow(2, cnt[i]) % MOD;
        allContrib = (allContrib + a) % MOD;
        for (int j = i ; j <= maxVal ; j += i) {
            contribDivisor[j] = (contribDivisor[j] + a) % MOD;
        }
    }

    for (int i = 1 ; i <= maxVal ; i++) {
        int b = 1ll * contribDivisor[i] * contribDivisor[i] % MOD;
        cntWithLcm[i] = (cntWithLcm[i] + b) % MOD;

        for (int j = 2*i ; j <= maxVal ; j += i) {
            cntWithLcm[j] = (cntWithLcm[j] - cntWithLcm[i] + MOD) % MOD;
        }

        int w = cntWithLcm[i];
        w = 1ll * w * modPow(3, cnt[i]) % MOD;
        w = 1ll * w * modPow(modPow(2, 2*cnt[i]), MOD-2) % MOD;
        ret = (ret + w) % MOD;
    }

    // calc 1st term with lcm > maxVal
    allContrib = 1ll * allContrib * allContrib % MOD; 
    for (int i = 1 ; i <= maxVal ; i++) {
        allContrib = (allContrib - cntWithLcm[i]) % MOD;
    }
    allContrib = (allContrib + MOD) % MOD;
    ret = (ret + allContrib) % MOD;

    // 2nd and 3rd term
    int allMu = 0;
    for (int i = 1 ; i <= maxVal ; i++) {
        allMu += mu[i];
    }
    for (int i = 1 ; i <= maxVal ; i++) {
        ret = (ret - 2ll * allMu * modPow(2, cnt[i]) * mu[i]) % MOD;
    }

    // 4th term
    ret = (ret + 1ll * allMu * allMu) % MOD;
    ret = (ret + MOD) % MOD;

    return ret;
}

int nlog2n() {
    int ret = 0;

    for (int i = 1 ; i <= n ; i++) {
        vector<int> cnt(n / i + 1, 0);
        for (int j = i ; j <= n ; j += i) {
            cnt[j / i] = cntrMul[j];
        }
        int w = solveSingle(cnt);
        ret = (ret + 1ll * w * i) % MOD;
    }

    return ret;
}


int main() {
    read();
    prepare();
    cout << nlog2n() << "\n";
    return 0;
}

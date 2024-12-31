#include <bits/stdc++.h>
using namespace std;

string S;
int V, C, Y, N, G;

int main() {
    cin >> S;
    for (char c : S) {
        if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            V++;
        } else if (c == 'N') {
            N++;
        } else if (c == 'G') {
            G++;
        } else if (c == 'Y') {
            Y++;
        } else {
            C++;
        }
    }

    int res = 0;
        
    // brute force the number of syllables
    for (int syllables = 1; syllables <= V+Y; syllables++) {
        int v = V, c = C, y = Y, n = N, g = G;

        // construct the vowels
        int rem_vowels = syllables;

        int used;

        // use original vowels
        used = min(v, rem_vowels);
        v -= used;
        rem_vowels -= used;

        // use Y as vowels
        used = min(y, rem_vowels);
        y -= used;
        rem_vowels -= used;

        // if not enough vowels
        if (rem_vowels) {
            break;
        }

        // current length of the word
        int cur = syllables;

        // construct the consonants
        int rem_consonants = 2*syllables;

        // use N
        int used_n = min(n, rem_consonants);
        cur += used_n;
        rem_consonants -= used_n;

        // use original consonants (but without G) + remaining Y
        used = min(c+y, rem_consonants);
        cur += used;
        rem_consonants -= used;

        // if not enough consonants
        if (rem_consonants) {
            // now add G
            used = min(g, rem_consonants);
            cur += used;
            rem_consonants -= used;
            g -= used;
        }

        // if still not enough consonants
        if (rem_consonants) {
            break;
        }

        // add G to N to make NG
        used = min(g, used_n);
        cur += used;

        res = max(res, cur);
    }

    cout << res << endl;
}
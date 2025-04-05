#include <bits/stdc++.h>

using namespace std;

void pref_func(string s, vector<int> & p) {
    int n = (int)s.size();
    p.assign(n, {});
    p[0] = 0;
    for (int i = 1; i < n; ++i) {
        int k = p[i - 1];
        while (k > 0 && s[i] != s[k]) {
            k = p[k - 1];
        }
        if (s[k] == s[i]) {
            k++;
        }
        p[i] = k;
    }
}

void z_func(string s, vector<int> & z) {
    int n = (int)s.size();
    z.assign(n, {});
    int l = 0, r = 0;
    z[0] = 0;
    for (int i = 1; i < n; ++i) {
        z[i] = min(max(0, r - i), z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > r) {
            r = i + z[i];
            l = i;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << endl;
    return 0;
}

//#pragma GCC optimize("Ofast,unroll-loops,fast-math,inline,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,abm,mmx,popcnt")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
constexpr int MOD = 1e9 + 7;
constexpr int INF = 1e9;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

void buildSuffMas(string s, vector<int> &suff, vector<int> &c, vector<int> &lcp) {
    int n = s.size();
    vector<int> cnt(200);
    for (int i = 0; i < n; i++) {
        cnt[s[i]]++;
    }
    for (int i = 1; i < 200; i++) {
        cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i > -1; i--) {
        cnt[s[i]]--;
        suff[cnt[s[i]]] = i;
    }
    c[suff[0]] = 0;
    int sz = 0;
    for (int i = 1; i < n; i++) {
        if (s[suff[i]] != s[suff[i - 1]]) {
            sz++;
        }
        c[suff[i]] = sz;
    }
    int len = 1;
    while (len < n) {
        vector<int> id(1);
        for (int i = 1; i < n; ++i) {
            if (c[suff[i]] != c[suff[i - 1]]) {
                id.push_back(i);
            }
        }
        vector<int> new_suff(n);
        for (int i : suff) {
            int j = (i - len + n) % n;
            new_suff[id[c[j]]++] = j;
        }
        swap(suff, new_suff);
        vector<int> new_c(n);
        new_c[suff[0]] = 0;
        for (int i = 1; i < n; i++) {
            new_c[suff[i]] = new_c[suff[i - 1]];
            if (c[suff[i]] != c[suff[i - 1]] || c[(suff[i] + len) % n] != c[(suff[i - 1] + len) % n]) {
                new_c[suff[i]]++;
            }
        }
        swap(c, new_c);
        len <<= 1;
    }
    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (c[i] == n - 1) continue;
        int j = suff[c[i] + 1];
        while (i + cur < n && j + cur < n && s[i + cur] == s[j + cur] && s[i + cur] != '$') {
            cur++;
        }
        lcp[c[i]] = cur;
        cur = max(cur - 1, 0);
    }
}

vector<vector<int>> sparce;

void build_sparce(vector<int> &a) {
    int L = 31 - __builtin_clz(a.size());
    sparce.assign(L + 1, vector<int>(a.size()));
    for (int i = 0; i < a.size(); ++i) {
        sparce[0][i] = a[i];
    }
    for (int k = 1; k <= L; ++k) {
        for (int i = 0; i <= a.size() - (1 << k); ++i) {
            sparce[k][i] = min(sparce[k - 1][i], sparce[k - 1][i + (1 << (k - 1))]);
        }
    }
}

int get_sparce(int l, int r) {
    int L = 31 - __builtin_clz(r - l);
    return min(sparce[L][l], sparce[L][r - (1 << L)]);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef vscWisik
    freopen("/Users/nikolay_kh/Documents/vscode_projects/io/input.txt", "r", stdin);
    freopen("/Users/nikolay_kh/Documents/vscode_projects/io/output.txt", "w", stdout);
#endif

    vector<int> suff(n);
    vector<int> c(n);
    vector<int> lcp(n - 1);
    buildSuffMas(s, suff, c, lcp);
    build_sparce(lcp);

    return 0;
}
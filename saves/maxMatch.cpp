/*
#pragma GCC optimize("Ofast,unroll-loops,fast-math,inline,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,abm,mmx,popcnt")
*/
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll
constexpr int MOD = 1e9 + 7;
constexpr int INF = 1e9;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());


vector<vector<int>> g;
vector<int> used, mt;

bool kuhn(int v, int t) {
    if (used[v] == t) return false;
    used[v] = t;
    for (auto to : g[v]) {
        if (mt[to] == -1) {
            mt[to] = v;
            return true;
        }
    }
    for (auto to : g[v]) {
        if (kuhn(mt[to], t)) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
#ifdef vscWisik
    freopen("input.txt", "r", stdin);
#endif

    int n, m, x;
    cin >> n >> m;
    g.assign(n, vector<int>());
    mt.assign(m, -1);
    used.assign(n, 0);
    for (int i = 0; i < n; ++i) {
        cin >> x;
        while (x != 0) {
            g[i].push_back(x - 1);
            cin >> x;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (kuhn(i, i + 1)) ans++;
    }

    cout << ans << "\n";
    for (int i = 0; i < m; ++i) {
        if (mt[i] != -1) {
            cout << mt[i] + 1 << " " << i + 1 << "\n";
        }
    }
    return 0;
}

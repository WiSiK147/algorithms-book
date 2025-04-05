// la O(1). Ladder decomposition
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

vector<vector<int>> g, up, ladder;
vector<int> h, way, num, lg;
int waynum = 0;

int dfs(int v) {
    for (int i = 1; i <= lg.back(); ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    if (g[v].size() == 0) {
        ladder.emplace_back();
        ladder[waynum].push_back(v);
        num[v] = 0;
        way[v] = waynum++;
        return 1;
    }
    int max_to = 0, max_to_id = v;
    for (auto to : g[v]) {
        h[to] = h[v] + 1;
        up[0][to] = v;
        int tmp = dfs(to);
        if (tmp > max_to) {
            max_to = tmp;
            max_to_id = to;
        }
    }
    way[v] = way[max_to_id];
    num[v] = num[max_to_id] + 1;
    ladder[way[v]].push_back(v);
    return max_to + 1;
}

int la(int v, int k) {
    if (k == 0) return v;
    if (lg[k] > lg.back()) return 0;
    v = up[lg[k]][v];
    if (num[v] + k - (1 << lg[k]) >= ladder[way[v]].size()) return ladder[way[v]].back();
    return ladder[way[v]][num[v] + k - (1 << lg[k])];
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
#ifdef vscWisik
    freopen("input.txt", "r", stdin);
#endif
    int n, m, x;
    cin >> n >> m;
    lg.assign(n + 1, 0);
    lg[1] = 0;
    for (int i = 2; i <= n; i++) {
        lg[i] = lg[i >> 1] + 1;
    }
    g.resize(n);
    h.assign(n, 0);
    way.assign(n, 0);
    num.assign(n, 0);
    up.assign(lg[n] + 1, vector<int>(n, 0));
    for (int i = 1; i < n; ++i) {
        cin >> x;
        g[x].push_back(i);
    }
    dfs(0);
    for (int i = 0; i < waynum; ++i) {
        int sz = ladder[i].size(), v = ladder[i].back();
        for (int j = 0; j < sz; ++j) {
            if (v == up[0][v]) break;
            ladder[i].push_back(up[0][v]);
            v = up[0][v];
        }
    }
    long long a1, a2, y, z, v = 0, res = 0;
    cin >> a1 >> a2 >> x >> y >> z;
    while (m--) {
        v = la((int)((a1 + v) % n), (int)a2);
        res += v;
        a1 = (x * a1 + y * a2 + z) % n;
        a2 = (x * a2 + y * a1 + z) % n;
    }
    cout << res << endl;
}

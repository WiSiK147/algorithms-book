//#pragma GCC optimize("Ofast,unroll-loops,fast-math,inline,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,abm,mmx,popcnt")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll
constexpr int MOD = 1e9 + 7;
constexpr int INF = 1e9;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

int timer = 0;
vector<vector<int>> g;
vector<int> tin, euler, h;
vector<vector<pair<int, int>>> lca;
vector<int> lg;

void build_euler(int v) {
    tin[v] = timer++;
    euler.push_back(v);
    for (auto to : g[v]) {
        h[to] = h[v] + 1;
        build_euler(to);
        euler.push_back(v);
    }
    timer++;
}

void build_lca() {
    for (int i = 0; i < (int)euler.size(); ++i) {
        lca[i][0] = {h[euler[i]], euler[i]};
    }
    for (int k = 1; k <= lg[euler.size() - 1]; ++k) {
        for (int i = 0; i <= (int)euler.size() - (1 << k); ++i) {
            lca[i][k] = min(lca[i][k - 1], lca[i + (1 << (k - 1))][k - 1]);
        }
    }
}

int get_lca(int u, int v) {
    if (tin[v] > tin[u]) swap(u, v);
    int k = lg[tin[u] - tin[v]];
    if (lca[tin[v]][k].first < lca[tin[u] - (1 << k) + 1][k].first) {
        return lca[tin[v]][k].second;
    } else {
        return lca[tin[u] - (1 << k) + 1][k].second;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
#ifdef vscWisik
    freopen("input.txt", "r", stdin);
#endif
    long long n, m, x;
    cin >> n >> m;

    lg.resize(2 * n + 1);
    lg[1] = 0;
    for (int i = 2; i <= 2 * n; i++) {
        lg[i] = lg[i >> 1] + 1;
    }

    g.resize(n);
    h.assign(n, 0);
    tin.assign(n, 0);

    for (int i = 0; i < n - 1; ++i) {
        cin >> x;
        g[x].push_back(i + 1);
    }

    build_euler(0);
    lca.assign(euler.size(), vector<pair<int, int>>(lg[euler.size() - 1] + 1, {0, 0}));
    build_lca();
    long long a1, a2, y, z, v = 0, res = 0;
    cin >> a1 >> a2 >> x >> y >> z;
    while (m--) {
        v = get_lca((int)((a1 + v) % n), (int)a2);
        res += v;
        a1 = (x * a1 + y * a2 + z) % n;
        a2 = (x * a2 + y * a1 + z) % n;
    }
    cout << res << endl;
}

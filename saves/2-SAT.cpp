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


vector<int> ans;
vector<vector<int>> g;
vector<int> used;
vector<int> order;

void dfs(int v) {
    used[v] = true;
    for (auto to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
    order.push_back(v);
}

vector<vector<int>> g2;
vector<int> comp;

void dfs2(int v, int col) {
    comp[v] = col;
    for (auto to : g2[v]) {
        if (comp[to] == -1) {
            dfs2(to, col);
        }
    }
}

void add_edge(int v, int u) {
    g[v].push_back(u);
    g2[u].push_back(v);
}


signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
#ifdef vscWisik
    freopen("input.txt", "r", stdin);
#endif

    int n, m;
    while (cin >> n >> m) {
        ans.assign(n, -1);
        comp.assign(2 * n, -1);
        used.assign(2 * n, false);
        g.assign(2 * n, vector<int>());
        g2.assign(2 * n, vector<int>());
        int j1, j2, y1, y2;
        for (int i = 0; i < m; ++i) {
            cin >> j1 >> y1 >> j2 >> y2;
            if (y1 == 0) {
                if (y2 == 0) {
                    add_edge(j1, j2 + n);
                    add_edge(j2, j1 + n);
                } else {
                    add_edge(j1, j2);
                    add_edge(j2 + n, j1 + n);
                }
            } else {
                if (y2 == 0) {
                    add_edge(j2, j1);
                    add_edge(j1 + n, j2 + n);
                } else {
                    add_edge(j1 + n, j2);
                    add_edge(j2 + n, j1);
                }
            }
        }
        for (int i = 0; i < 2 * n; ++i) {
            if (!used[i]) {
                dfs(i);
            }
        }
        reverse(order.begin(), order.end());

        int color = 0;
        for (int i = 0; i < 2 * n; ++i) {
            if (comp[order[i]] == -1) {
                dfs2(order[i], color);
                color++;
            }
        }

        for (int i = 0; i < n; ++i) {
            if (comp[i] < comp[i + n]) {
                ans[i] = 0;
            } else if (comp[i] == comp[i + n]) {
                return 0;
            } else {
                ans[i] = 1;
            }
            cout << ans[i];
        }
        cout << endl;
        order.clear();
    }

    return 0;
}

// Lca ofline O(1). Taryan 

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


long long ans = 0;
vector<vector<long long>> queries;
vector<vector<long long>> g;
vector<char> used;
vector<long long> lcaClass;
vector<long long> lead, sz;

long long getLead(long long v) {
    if (lead[v] == v) return v;
    lead[v] = getLead(lead[v]);
    return lead[v];
}

long long unite(long long a, long long b) {
    a = getLead(a);
    b = getLead(b);
    if (a == b) return a;
    if (sz[a] > sz[b]) swap(a, b);
    lead[a] = b;
    sz[b] += sz[a];
    return b;
}

void dfs(long long v, long long p = -1) {
    lcaClass[v] = v;
    for (auto to : g[v]) {
        if (to != p) {
            dfs(to, v);
            lcaClass[unite(v, to)] = v;
        }
    }
    used[v] = true;
    for (auto to : queries[v]) {
        if (used[to]) {
            ans += lcaClass[getLead(to)];
        }
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
    g.resize(n);
    queries.resize(n);
    lcaClass.resize(n);
    used.assign(n, false);
    lead.assign(n, 0);
    for (long long i = 0; i < n; ++i) lead[i] = i;
    sz.assign(n, 1);
    for (long long i = 1; i < n; ++i) {
        cin >> x;
        g[x].push_back(i);
    }
    long long a1, a2, y, z;
    cin >> a1 >> a2 >> x >> y >> z;
    while (m--) {
        if (a1 == a2) ans += a1;
        else {
            queries[a1].push_back(a2);
            queries[a2].push_back(a1);
        }
        a1 = (x * a1 + y * a2 + z) % n;
        a2 = (x * a2 + y * a1 + z) % n;
    }

    dfs(0);

    cout << ans << endl;
}

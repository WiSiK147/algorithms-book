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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef vscWisik
    freopen("input.txt", "r", stdin);
#endif

    cout << endl;
    return 0;
}

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

const int P = 31;
const int MOD = 1791791791;

int add(int a, int b, int mod) {
    if (a + b >= mod) {
        return a + b - mod;
    }
    return a + b;
}

int sub(int a, int b, int mod) {
    if (a - b < 0) {
        return a - b + mod;
    }
    return a - b;
}

int mul(int a, int b, int mod) {
    return (1ll * a * b) % mod;
}



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef vscWisik
    freopen("input.txt", "r", stdin);
#endif

    vector<pair<long long, long long>> PrimePower;
    PrimePower.assign(MAXN + 1, {});
    PrimePower[0] = {1, 1};
    for (int i = 1; i <= MAXN; ++i) {
        PrimePower[i].first = mul(PrimePower[i - 1].first, P, MOD);
        PrimePower[i].second = mul(PrimePower[i - 1].second, P2, MOD2);
    }

    string a;
    cin >> a;
    int n = (int)a.size();

    vector<long long> hashA(n + 1);
    hashA[0] = 0;
    for (int i = 0; i < n; ++i) {
        hashA[i + 1] = add(mul(hashA[i], P, MOD), a[i] - 'a' + 1, MOD);
    }

    //str hash
    long long hash1 = sub(hashA[l1 + mid], mul(hashA[l1], PrimePower[mid], MOD), MOD);

    cout << endl;
    return 0;
}

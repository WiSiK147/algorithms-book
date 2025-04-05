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

// [l, r)
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


    return 0;
}
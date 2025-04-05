//#pragma GCC optimize("Ofast,unroll-loops,fast-math,inline,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,abm,mmx,popcnt")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
#define all(x) x.begin(), x.end()
#define allr(x) x.rbegin(), x.rend()
#ifdef vscWisik
#define show(x) std::cout << "LINE " << __LINE__ << ": " << #x << "=[" << x << "]" << std::endl;
#else
#define show(x) 179
#endif
constexpr int MOD = 1e9 + 7;
constexpr int INF = 1e18;
//mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

template <typename T>
istream& operator>>(istream& in, pair<T, T>& a) {
    in >> a.first >> a.second;
    return in;
}

template <typename T>
ostream& operator<<(ostream& out, pair<T, T>& a) {
    out << a.begin() << " " << a.end();
    return out;
}

template <typename T>
istream& operator>>(istream& in, vector<T>& a) {
    for (auto& el : a) {
        cin >> el;
    }
    return in;
}

template <typename T>
ostream& operator<<(ostream& out, vector<T>& a) {
    for (auto el : a) {
        out << el << " ";
    }
    return out;
}

#define MULTITEST

void solve() {
    
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef vscWisik
    freopen("/Users/nikolay_kh/Documents/vscode_projects/.io/input.txt", "r", stdin);
    freopen("/Users/nikolay_kh/Documents/vscode_projects/.io/output.txt", "w", stdout);
#endif

    int t = 1;
#ifdef MULTITEST
    cin >> t;
#endif
    while (t--) {
        solve();
    }

    return 0;
}
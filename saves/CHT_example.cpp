//#pragma GCC optimize("Ofast,unroll-loops,fast-math,inline,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,abm,mmx,popcnt")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
constexpr int MOD = 1e9 + 7;
constexpr int INF = 1e9;
//mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Line {
    int k = INF, b = INF;
    
    Line() = default;
    Line(int k, int b): k(k), b(b) {}

    int value(int x) {
        return k * x + b;
    }
};

int intersect(Line a, Line b) {
    if (a.k == b.k) return -INF;
    return (b.b - a.b + a.k - b.k - 1) / (a.k - b.k);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef vscWisik
    freopen("/Users/nikolay_kh/Documents/vscode_projects/io/input.txt", "r", stdin);
    freopen("/Users/nikolay_kh/Documents/vscode_projects/io/output.txt", "w", stdout);
#endif
    
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i].first >> a[i].second;
    sort(a.begin(), a.end());
    vector<pair<int, int>> b;
    b.reserve(n);
    b.push_back(a[0]);
    for (int i = 1; i < n; ++i) {
        while (!b.empty() && a[i].second >= b.back().second) {
            b.pop_back();
        }
        b.push_back(a[i]);
    }
    int m = b.size();

    vector<pair<int, int>> cht;
    cht.push_back({-INF, 0});
    vector<int> dp(m);
    vector<Line> lines(m);
    lines[0] = Line(b[0].second, 0);
    dp[0] = b[0].first * b[0].second;
    for (int i = 1; i < m; ++i) {
        lines[i] = Line(b[i].second, dp[i - 1]);
        while (!cht.empty()) {
            int newx = intersect(lines[cht.back().second], lines[i]);
            if (newx <= cht.back().first) {
                cht.pop_back();
            } else {
                cht.push_back({newx, i});
                break;
            }
        }
        int ind = lower_bound(cht.begin(), cht.end(), make_pair(b[i].first, m)) - cht.begin() - 1;
        dp[i] = lines[cht[ind].second].value(b[i].first);
    }

    cout << dp[m - 1] << "\n";

    return 0;
}
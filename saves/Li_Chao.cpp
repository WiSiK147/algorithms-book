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
    int k, b;

    Line(): k(0), b(INF) {}
    Line(int k, int b): k(k), b(b) {}

    int val(int x) {
        return k * x + b;
    }
};

struct Li_Chao {
    struct Node {
        Line line;
        Node *l, *r;

        Node(Line _line): line(_line), l(nullptr), r(nullptr) {}

        void mk_sons() {
            if (l == nullptr) {
                l = new Node(Line());
            }
            if (r == nullptr) {
                r = new Node(Line());
            }
        }
    };

    Node *root;
    int MIN, MAX;

    Li_Chao(int MIN, int MAX): MIN(MIN), MAX(MAX), root(new Node(Line())) {}
    
    void add(Node* tree, int l, int r, Line line) {
        int m = (l + r) / 2;
        if (line.val(m) < tree->line.val(m)) {
            swap(line, tree->line);
        }
        if (r - l == 1) {
            return;
        }
        tree->mk_sons();
        if (line.k < tree->line.k) {
            add(tree->r, m, r, line);
        } else {
            add(tree->l, l, m, line);
        }
    }

    int get(Node* tree, int l, int r, int pos) {
        int ans = tree->line.val(pos);
        if (r - l == 1) {
            return ans;
        }
        tree->mk_sons();
        int m = (l + r) / 2;
        if (pos < m) {
            return min(ans, get(tree->l, l, m, pos));
        } else {
            return min(ans, get(tree->r, m, r, pos));
        }
    }

    void add(Line line) {
        add(root, MIN, MAX, line);
    }

    int get(int pos) {
        return get(root, MIN, MAX, pos);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef vscWisik
    freopen("/Users/nikolay_kh/Documents/vscode_projects/io/input.txt", "r", stdin);
    freopen("/Users/nikolay_kh/Documents/vscode_projects/io/output.txt", "w", stdout);
#endif

    


    return 0;
}
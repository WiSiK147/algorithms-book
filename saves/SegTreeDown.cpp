#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll
constexpr int MOD = 1e9 + 7;
constexpr int INF = 1e9;


struct SegmentTree {
    struct Node {
        int mx = 0;

        Node() = default;
    };

    int n;
    vector<Node> tree;

    SegmentTree(int _n) {
        tree.assign(2 * _n, {});
        n = _n;
    }

    Node merge(Node left, Node right) {
        Node res;
        res.mx = max(left.mx, right.mx);
        return res;
    }

    void build(const string &s) {
        for (int i = n; i < 2 * n; ++i) {
            tree[i].mx = s[i - n];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = merge(tree[i << 1], tree[(i << 1) + 1]);
        }
    }

    void updatePoint(int pos, int x) {
        int p = pos + n;
        tree[p].mx = x;
        while (p > 1) {
            p >>= 1;
            tree[p] = merge(tree[p << 1], tree[(p << 1) + 1]);
        }
    }

    Node queryPoint(int pos) {
        return tree[n + pos];
    }

    Node querySeg(int ql, int qr) {
        Node ans;
        for (ql += n, qr += n; ql < qr; ql >>= 1, qr >>= 1) {
            if (ql & 1) {
                ans = merge(ans, tree[ql++]);
            }
            if (qr & 1) {
                ans = merge(ans, tree[--qr]);
            }
        }
        return ans;
    }
};


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << endl;
    return 0;
}

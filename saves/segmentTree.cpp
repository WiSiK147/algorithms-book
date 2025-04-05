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
    vector<int> push;
    vector<Node> tree;

    SegmentTree(int _n) {
        tree.assign(4 * _n, {});
        push.assign(4 * _n, {});
        n = _n;
    }
    
    void makePush(int v) {
        if (push[v] == 0) {
            return;
        }
        push[v * 2 + 1] += push[v];
        push[v * 2 + 2] += push[v];
        tree[v * 2 + 1].mx += push[v];
        tree[v * 2 + 2].mx += push[v];
        push[v] = 0;
    }

    Node merge(Node left, Node right) {
        Node res;
        res.mx = max(left.mx, right.mx);
        return res;
    }

    void build(int v, int l, int r, const vector<int> &a) {
        if (l + 1 == r) {
            tree[v].mx = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(v * 2 + 1, l, m, a);
        build(v * 2 + 2, m, r, a);
        tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
    }

    void updatePoint(int v, int l, int r, int pos, int x) {
        if (l + 1 == r) {
            tree[v].mx += x;
            return;
        }
        makePush(v);
        int m = (l + r) / 2;
        if (pos < m) {
            updatePoint(v * 2 + 1, l, m, pos, x);
        } else {
            updatePoint(v * 2 + 2, m, r, pos, x);
        }
        tree[v] = merge(tree[v * 2 + 1], tree[v * 2 + 2]);
    }

    void updateSeg(int v, int l, int r, int ql, int qr, int x) {
        if (l >= qr || r <= ql) {
            return;
        }
        if (l >= ql && r <= qr) {
            tree[v].mx += x;
            push[v] += x;
            return;
        }
        makePush(v);
        int m = (l + r) / 2;
        updateSeg(2 * v + 1, l, m, ql, qr, x);
        updateSeg(2 * v + 2, m, r, ql, qr, x);
        tree[v] = merge(tree[2 * v + 1], tree[2 * v + 2]);
    }

    Node queryPoint(int v, int l, int r, int pos) {
        if (l + 1 == r) {
            return tree[v];
        }
        makePush(v);
        int m = (l + r) / 2;
        if (pos < m) {
            return queryPoint(v * 2 + 1, l, m, pos);
        } else {
            return queryPoint(v * 2 + 2, m, r, pos);
        }
    }

    Node querySeg(int v, int l, int r, int ql, int qr) {
        if (l >= qr || r <= ql) {
            return Node();
        }
        if (l >= ql && r <= qr) {
            return tree[v];
        }
        makePush(v);
        int m = (l + r) / 2;
        return merge(querySeg(v * 2 + 1, l, m, ql, qr), querySeg(v * 2 + 2, m, r, ql, qr));
    }
};


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << endl;
    return 0;
}

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define int ll
constexpr int MOD = 1e9 + 7;
constexpr int INF = 1e9;

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Node {
    long long key;
    long long priority;
    long long sum;
    long long sz;
    long long min;
    int rev;

    Node* l;
    Node* r;

    Node(long long _key) {
        key = _key;
        priority = rnd();
        sum = _key;
        min = _key;
        sz = 1;
        rev = 0;
        l = r = nullptr;
    }
};

long long getSz(Node* t) {
    if (t == nullptr) return 0;
    return t->sz;
}

long long getSum(Node* t) {
    if (t == nullptr) return 0;
    return t->sum;
}

long long getMin(Node* t) {
    if (t == nullptr) return INF;
    return t->min;
}

void upd(Node* t) {
    if (t == nullptr) return;
    t->sz = getSz(t->l) + getSz(t->r) + 1;
    t->sum = getSum(t->l) + getSum(t->r) + t->key;
    t->min = min(t->key, min(getMin(t->l), getMin(t->r)));
}

void push(Node* t) {
    t->rev = 0;
    swap(t->l, t->r);
    if (t->l != nullptr) t->l->rev ^= 1;
    if (t->r != nullptr) t->r->rev ^= 1;
}

/*
// <, >=
// splitEl
pair<Node*, Node*> split(Node* t, int x) {
    if (t == nullptr) return {nullptr, nullptr};

    if (t->key >= x) {
        auto[l1, l2] = split(t->l, x);
        t->l = l2;
        //upd(t);
        return {l1, t};
    } else {
        auto[r1, r2] = split(t->r, x);
        t->r = r1;
        //upd(t);
        return {t, r2};
    }
}
*/

// <, >=
pair<Node*, Node*> splitSz(Node* t, long long x) {
    if (t == nullptr) return {nullptr, nullptr};
    if (t->rev == 1) push(t);

    long long sz = getSz(t->l) + 1;
    if (x >= sz) {
        auto[r1, r2] = splitSz(t->r, x - sz);
        t->r = r1;
        upd(t);
        return {t, r2};
    } else {
        auto[l1, l2] = splitSz(t->l, x);
        t->l = l2;
        upd(t);
        return {l1, t};
    }
}

Node* merge(Node* l, Node* r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;

    if (l->priority < r->priority) {
        if (r->rev == 1) push(r);
        r->l = merge(l, r->l);
        upd(r);
        return r;
    } else {
        if (l->rev == 1) push(l);
        l->r = merge(l->r, r);
        upd(l);
        return l;
    }
}

Node* insert(Node* t, long long x) {
    Node* newNode = new Node(x);
    return merge(t, newNode);
}

Node* getMinimum(Node* t, long long l, long long r) {
    auto[left, tmp] = splitSz(t, l - 1);
    auto[mid, right] = splitSz(tmp, r - l + 1);
    cout << mid->min << "\n";
    return merge(left, merge(mid, right));
}

Node* update(Node* t, long long l, long long r) {
    auto[left, tmp] = splitSz(t, l - 1);
    auto[mid, right] = splitSz(tmp, r - l + 1);
    mid->rev ^= 1;
    return merge(left, merge(mid, right));
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << endl;
    return 0;
}

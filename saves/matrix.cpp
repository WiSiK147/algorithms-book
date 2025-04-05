#include <bits/stdc++.h>

using namespace std;

long long MOD = 0;

struct Matrix {
    long long n = 0, m = 0;
    vector<vector<long long>> v;

    Matrix(long long _n, long long _m) {
        n = _n;
        m = _m;
        v.assign(n, vector<long long>(m, 0));
    }
};

Matrix operator*(Matrix a, Matrix b) {
    if (a.m != b.n) {
        swap(a, b);
    }
    Matrix res(a.n, b.m);
    for (long long i = 0; i < a.m; ++i) {
        for (long long j = 0; j < a.n; ++j) {
            for (long long k = 0; k < b.m; ++k) {
                res.v[j][k] = (res.v[j][k] + (a.v[j][i] * b.v[i][k]) % MOD) % MOD;
            }
        }
    }
    return res;
}

Matrix operator+(Matrix a, Matrix b) {
    Matrix res(a.n, a.m);
    for (long long i = 0; i < a.n; ++i) {
        for (long long j = 0; j < a.m; ++j) {
            res.v[i][j] = (a.v[i][j] + b.v[i][j]) % MOD;
        }
    }
    return res;
}


istream &operator>>(istream &in, Matrix &a) {
    for (long long i = 0; i < a.n; ++i) {
        for (long long j = 0; j < a.m; ++j) {
            in >> a.v[i][j];
        }
    }
    return in;
}

ostream &operator<<(ostream &out, Matrix &a) {
    for (long long i = 0; i < a.n; ++i) {
        for (long long j = 0; j < a.m; ++j) {
            out << a.v[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}

Matrix fastPow(Matrix a, long long pow) {
    Matrix res(a.n, a.m);
    for (long long i = 0; i < a.n; ++i) {
        res.v[i][i] = 1;
    }
    while (pow > 0) {
        if (pow & 1) {
            res = res * a;
            pow--;
        } else {
            a = a * a;
            pow >>= 1;
        }
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    long long n;
    long long m;
    cin >> n >> m >> MOD;
    Matrix a(n, n);
    cin >> a;
    a = fastPow(a, m);
    cout << a;

    cout.flush();
    return 0;
}

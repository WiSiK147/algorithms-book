/*
#pragma GCC optimize("Ofast,unroll-loops,fast-math,inline,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,abm,mmx,popcnt")
*/
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
#define int ll
constexpr int MOD = 1e9 + 7;
constexpr int INF = 1e9;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

struct Pv {
    ld x = 179, y = 179;

    Pv() = default;

    Pv(ld _x, ld _y) {
        x = _x;
        y = _y;
    }

    bool operator==(Pv a) {
        return x == a.x && y == a.y;
    }

    Pv operator+(Pv a) {
        return {a.x + x, a.y + y};
    }

    Pv operator-(Pv a) {
        return {x - a.x, y - a.y};
    }

    long double operator*(Pv a) {
        return a.x * x + a.y * y;
    }

    Pv operator*(const ld a) const {
        return {a * x, a * y};
    }

    long double operator^(Pv a) {
        return x * a.y - a.x * y;
    }

    long long squaredDist() {
        return x * x + y * y;
    }

    double dist() {
        return sqrt(squaredDist());
    }
};

istream &operator>>(istream &in, Pv &a) {
    in >> a.x >> a.y;
    return in;
}

ostream &operator<<(ostream &out, Pv a) {
    out << a.x << " " << a.y;
    return out;
}



struct Line {
    Pv A, v;
    Line() {}
    Line(Pv _A, Pv _B) {
        A = _A;
        v = _B - _A;
    }
    Line(ld _A, ld _B, ld _C) {
        v = {-_B, _A};
        A.x = 0;
        A.y = _B + _C;
    }
    Pv n_vector() {
        return {-v.y, v.x};
    }
};

struct Ray {
    Pv beg, v;
    Ray() {}
    Ray(Pv _A, Pv _B) {
        beg = _A;
        v = _B - _A;
    }
    Pv n_vector() {
        return {-v.y, v.x};
    }
};

struct Seg {
    Pv beg, end, v;
    Seg() {}
    Seg(Pv _A, Pv _B) {
        beg = _A;
        end = _B;
        v = _B - _A;
    }
    Pv n_vector() {
        return {-v.y, v.x};
    }
};

double distPointLine(Pv a, Line l) {
    if (l.v.dist() == 0) {
        return 0;
    }
    return abs((a - l.A) ^ l.v) / l.v.dist();
}

double distPointSegment(Pv a, Seg s) {
    if ((s.n_vector() ^ (a - s.beg)) * ((s.n_vector() ^ (s.v))) < 0) {
        return (a - s.beg).dist();
    }
    if ((s.n_vector() ^ (a - s.end)) * ((s.n_vector() ^ (s.v))) > 0) {
        return (a - s.end).dist();
    }
    return distPointLine(a, Line(s.beg, s.end));
}

double distPointRay(Pv a, Ray r) {
    if ((r.n_vector() ^ (a - r.beg)) * ((r.n_vector() ^ (r.v))) < 0) {
        return (a - r.beg).dist();
    }
    return distPointLine(a, Line(r.beg, r.v + r.beg));
}

double distLineLine(Line l1, Line l2) {
    if ((l1.v ^ l2.v) != 0) {
        return 0;
    }
    return distPointLine(l1.A, l2);
}

double distLineRay(Line l, Ray r) {
    if ((l.v ^ (r.beg - l.A)) * (l.v ^ r.v) < 0) {
        return 0;
    }
    return distPointLine(r.beg, l);
}

double distLineSegment(Line l, Seg s) {
    if ((l.v ^ (s.beg - l.A)) * (l.v ^ (s.end - l.A)) < 0) {
        return 0;
    }
    return min(distPointLine(s.beg, l), distPointLine(s.end, l));
}

double distRayRay(Ray r1, Ray r2) {
    if ((r1.v ^ r2.v) * (r1.v ^ (r2.beg - r1.beg)) < 0 && (r2.v ^ r1.v) * (r2.v ^ (r1.beg - r2.beg)) < 0) {
        return 0;
    }
    return min(distPointRay(r1.beg, r2), distPointRay(r2.beg, r1));
}

double distSegmentSegment(Seg s1, Seg s2) {
    if ((s1.v ^ (s2.beg - s1.beg)) * (s1.v ^ (s2.end - s1.beg)) < 0 && (s2.v ^ (s1.beg - s2.beg)) * (s2.v ^ (s1.end - s2.beg)) < 0) {
        return 0;
    }
    double tmp1 = min(distPointSegment(s1.beg, s2), distPointSegment(s1.end, s2));
    double tmp2 = min(distPointSegment(s2.beg, s1), distPointSegment(s2.end, s1));
    return min(tmp1, tmp2);
}

double distSegmentRay(Seg s, Ray r) {
    if (((s.v ^ r.v) * (s.v ^ (r.beg - s.beg))) < 0 && ((r.v ^ (s.beg - r.beg)) * (r.v ^ (s.end - r.beg))) < 0) {
        return 0;
    }
    double tmp1 = min(distPointRay(s.beg, r), distPointRay(s.end, r));
    return min(tmp1, distPointSegment(r.beg, s));
}

Pv move_to_angle(Pv v, long double cosa, long double sina) {
    return {v.x * cosa - v.y * sina, v.x * sina + v.y * cosa};
}

long double get_angle(Pv v1, Pv v2) {
    return abs(atan2(v1 ^ v2, v1 * v2));
}

int sign(ld x) {
    if (x == 0) {
        return 0;
    }
    if (x > 0) {
        return 1;
    }
    return -1;
}
// convex hull WiSiK
bool operator<(Pv a, Pv b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

vector<Pv> ch;

void buildConvexHull(vector<Pv> &a) {
    int n = (int) a.size();
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    ch.push_back(a[0]);
    int sz = 1;
    for (int i = 1; i < n - 1; ++i) {
        while (sz >= 2 && ((a[i] - ch[ch.size() - 2]) ^ (ch[ch.size() - 1] - ch[ch.size() - 2])) >= 0) {
            ch.pop_back();
            sz--;
        }
        if (((a[i] - ch[ch.size() - 1]) ^ (a[n - 1] - ch[ch.size() - 1])) > 0) {
            ch.push_back(a[i]);
            sz++;
        }
    }
    ch.push_back(a[n - 1]);
    sz = 1;
    for (int i = n - 2; i > 0; --i) {
        while (sz >= 2 && ((a[i] - ch[ch.size() - 2]) ^ (ch[ch.size() - 1] - ch[ch.size() - 2])) >= 0) {
            ch.pop_back();
            sz--;
        }
        if (((a[i] - ch[ch.size() - 1]) ^ (a[0] - ch[ch.size() - 1])) > 0) {
            ch.push_back(a[i]);
            sz++;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(20);
#ifdef vscWisik
    freopen("input.txt", "r", stdin);
#endif


    // polar convex hull
    int n;
    cin >> n;
    vector<Pv> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    Pv firstPoint = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i].y < firstPoint.y || (a[i].y == firstPoint.y && a[i].x < firstPoint.x)) {
            swap(a[i], a[0]);
            firstPoint = a[0];
        }
    }
    sort(a.begin() + 1, a.end(), [&firstPoint](const Pv &lhs, const Pv &rhs) {
        if (((lhs - firstPoint) ^ (rhs - firstPoint)) == 0) {
            return (lhs - firstPoint).squaredDist() < (rhs - firstPoint).squaredDist();
        }
        return ((lhs - firstPoint) ^ (rhs - firstPoint)) > 0;
    });

    vector<Pv> ch;
    ch.push_back(firstPoint);
    int m = 1;
    for (int i = 1; i < n; ++i) {
        while (m >= 2 && ((ch[m - 1] - ch[m - 2]) ^ (a[i] - ch[m - 1])) <= 0) {
            ch.pop_back();
            m--;
        }
        ch.push_back(a[i]);
        m++;
    }

    ch.push_back(ch[0]);

    cout << endl;
    return 0;
}

#include <bits/stdc++.h>

using namespace std;

constexpr int ALPHABET_SIZE = 26;

struct Node {
    array<int, ALPHABET_SIZE> go;
    int par, suf, sup, symb, term;

    Node() {
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            go[i] = -1;
        }
        par = -1;
        suf = 0;
        sup = 0;
        symb = 0;
        term = 0;
    }
};

vector<Node> tr(1);
vector<int> use;
vector<vector<int>> res(1);

void buildTrie(int v, int q, int ind, string &newStr) {
    if (ind == newStr.size()) {
        if (tr[v].term) {
            use[q] = tr[v].term;
        } else {
            tr[v].term = res.size();
            use[q] = tr[v].term;
            res.emplace_back();
        }
        return;
    }
    if (tr[v].go[newStr[ind] - 'a'] == -1) {
        tr[v].go[newStr[ind] - 'a'] = (int)tr.size();
        tr.emplace_back();
        tr[tr.size() - 1].par = v;
        tr[tr.size() - 1].symb = newStr[ind] - 'a';
    }
    buildTrie(tr[v].go[newStr[ind] - 'a'], q, ind + 1, newStr);
}


void buildAXO() {
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (tr[cur].par == -1 || tr[cur].par == 0) {
            tr[cur].suf = 0;
        } else {
            tr[cur].suf = tr[tr[tr[cur].par].suf].go[tr[cur].symb];
        }
        if (tr[cur].term) {
            tr[cur].sup = cur;
        } else {
            tr[cur].sup = tr[tr[cur].suf].sup;
        }

        for (int s = 0; s < ALPHABET_SIZE; ++s) {
            if (tr[cur].go[s] == -1) {
                if (tr[cur].par == -1) {
                    tr[cur].go[s] = 0;
                } else {
                    tr[cur].go[s] = tr[tr[cur].suf].go[s];
                }
            } else {
                q.push(tr[cur].go[s]);
            }
        }
    }
}


void get(string &str) {
    int cur = 0;
    for (int i = 0; i < (int) str.size(); ++i) {
        cur = tr[cur].go[str[i] - 'a'];
        int t = cur;
        while (tr[t].sup != 0) {
            res[tr[tr[t].sup].term].push_back(i);
            t = tr[tr[t].sup].suf;
        }
    }
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, t;
    cin >> t;
    int n;
    cin >> n;
    use.assign(n, {});
    vector<int> sz(n);
    for (int i = 0; i < n; ++i) {
        cin >> s;
        sz[i] = (int)s.size();
        buildTrie(0, i, 0, s);
    }
    buildAXO();
    get(t);

    for (int i = 0; i < n; ++i) {
        cout << res[use[i]].size() << " ";
        for (auto el : res[use[i]]) {
            cout << el - sz[i] + 2 << " ";
        }
        cout << "\n";
    }

    return 0;
}

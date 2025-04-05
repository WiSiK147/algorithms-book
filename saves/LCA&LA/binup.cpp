
constexpr int L = 22;
vector<vector<int>> g;
vector<int> depth;
vector<vector<int>> binup;

void dfs(int v) {
    for (int i = 1; i < L; ++i) {
        binup[v][i] = binup[binup[v][i - 1]][i - 1];
    }
    for (auto to : g[v]) {
        depth[to] = depth[v] + 1;
        binup[to][0] = v;
        dfs(to);
    }
}

int lca(int u, int v) {
    if (depth[u] > depth[v]) swap(u, v);
    for (int l = L - 1; l >= 0; --l) {
        if (depth[binup[v][l]] >= depth[u]) {
            v = binup[v][l];
        }
    }
    if (u == v) return v;
    for (int l = L - 1; l >= 0; --l) {
        if (binup[v][l] != binup[u][l]) {
            v = binup[v][l];
            u = binup[u][l];
        }
    }
    if (u != v) return binup[v][0];
    return v;
}

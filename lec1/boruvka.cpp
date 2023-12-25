#include <bits/stdc++.h>

using namespace std;

struct DSU {
    vector<int> fa;
    int n;
    DSU(int n): n(n) {
        fa.resize(n + 1);
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);

        if (x == y)
            return false;

        fa[x] = y;
        return true;
    }
};

int main() {
    // cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> g(m);

    for (auto &[u, v, w] : g)
        cin >> u >> v >> w;

    long long ans = 0;
    int cnt = 0;
    DSU dsu(n);

    while (true) {
        vector<int> edge(n + 1, (int)1e9);
        vector<int> id(n + 1, m);
        vector<int> used(m + 1, 0);

        for (int i = 0; i < m; ++i) {
            auto [u, v, w] = g[i];
            auto fu = dsu.find(u), fv = dsu.find(v);

            if (fu == fv)
                continue;

            if (w < edge[fu]) {
                used[id[fu]] = 0;
                edge[fu] = w;
                used[i] = 1;
                id[fu] = i;
            }

            if (w < edge[fv]) {
                used[id[fv]] = 0;
                edge[fv] = w;
                used[i] = 1;
                id[fv] = i;
            }
        }

        bool flag = false;

        for (int i = 0; i < m; ++i) {
            if (used[i]) {
                auto [u, v, w] = g[i];
                dsu.merge(dsu.find(u), dsu.find(v));
                ans += w;
                ++cnt;
                flag = true;
            }
        }

        if (!flag)
            break;
    }

    if (cnt == n - 1)
        cout << ans << endl;
    else
        cout << "orz" << endl;

    return 0;
}
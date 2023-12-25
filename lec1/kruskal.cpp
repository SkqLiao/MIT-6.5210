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
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> g(m);

    for (auto &[u, v, w] : g)
        cin >> u >> v >> w;

    long long ans = 0;
    int cnt = 0;
    DSU dsu(n);

    sort(g.begin(), g.end(), [&](auto & x, auto & y) {
        return x[2] < y[2];
    });

    for (auto [u, v, w] : g) {
        if (dsu.merge(u, v)) {
            ans += w;
            ++cnt;
        }
    }

    if (cnt == n - 1)
        cout << ans << endl;
    else
        cout << "orz" << endl;

    return 0;
}
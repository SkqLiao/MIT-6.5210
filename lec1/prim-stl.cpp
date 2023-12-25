#include <bits/stdc++.h>

using namespace std;

int main() {
    // cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n + 1);

    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    long long ans = 0;
    int cnt = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> dis(n + 1, 1e9);
    vector<bool> vis(n + 1);
    dis[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (dis[u] != d)
            continue;

        ans += dis[u];
        vis[u] = 1;
        ++cnt;

        for (auto [v, w] : g[u]) {
            if (!vis[v] && dis[v] > w) {
                dis[v] = w;
                pq.push({w, v});
            }
        }
    }

    if (cnt == n) {
        cout << ans << "\n";
    } else {
        cout << "orz" << "\n";
    }

    return 0;
}
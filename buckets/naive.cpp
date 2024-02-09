#include <bits/stdc++.h>

using namespace std;

struct Bucket {
    vector<list<int>> nodes;
    long long base;
    int num, now;
    Bucket(int n) {
        nodes.resize(n + 1);
        base = 0;
        now = 0;
        num = 0;
    }
    void push(long long dis, int node) {
        ++num;
        int p = dis % nodes.size();
        nodes[p].push_back(node);
    }
    bool empty() {
        return num == 0;
    }
    pair<long long, int> top() {
        int nxt = now;
        --num;

        do {
            if (!nodes[nxt].empty()) {
                now = nxt;
                auto t = nodes[now].back();
                nodes[now].pop_back();
                return make_pair(base + now, t);
            }

            if (++nxt == nodes.size()) {
                base += nodes.size();
                nxt = 0;
            }
        } while (nxt != now);

        return make_pair(-1, -1);
    }
};

int main() {
    cin.tie(NULL)->ios_base::sync_with_stdio(false);
    int n, m, s = 1;
    cin >> n >> m;
    vector<vector<pair<int, int>>> e(n + 1);
    int mxw = 0;

    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        e[u].emplace_back(v, w);
        //e[v].emplace_back(u, w);
        mxw = max(mxw, w);
    }

    Bucket b(mxw);
    vector<long long> dis(n + 1, LLONG_MAX);
    dis[s] = 0;
    b.push(0, s);

    while (!b.empty()) {
        auto [d, u] = b.top();

        if (dis[u] != d)
            continue;

        //cout << "get node " << u << " dis = " << d << endl;

        for (auto [v, w] : e[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                b.push(dis[v], v);
                //cout << "push node " << v << " dis = " << dis[v] << endl;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << dis[i] << " \n"[i == n];
    }

    return 0;
}
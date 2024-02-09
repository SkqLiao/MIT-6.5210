#include <bits/stdc++.h>
#include <climits>

using namespace std;

struct Bucket {
    vector<pair<int, list<pair<long long, list<int>>>>> nodes;
    int nowb, sz, total, num;
    long long base;
    Bucket(int n) {
        total = n + 1;
        sz = max((int)sqrt(n), 1);
        nodes.resize(total / sz + 1);
        nowb = base = num = 0;
    }
    void push(long long dis, int node) {
        ++num;
        int p = dis % total;
        auto &np = nodes[p / sz];
        np.first++;
        auto &v = np.second;

        if (v.empty() || v.back().first != dis) {
            v.push_back({dis, list<int>{node}});
        } else {
            v.back().second.push_back(node);
        }
    }
    bool empty() {
        return num == 0;
    }
    pair<long long, int> top() {
        --num;
        int nxtb = nowb;

        for (int i = 0; i <= nodes.size(); ++i) {
            if (nodes[nxtb].first && nodes[nxtb].second.front().first < base + (nxtb + 1) * sz) {
                nowb = nxtb;
                nodes[nxtb].first--;
                auto &v = nodes[nxtb].second;
                auto & [val, l] = v.front();
                auto res = make_pair(val, l.back());
                l.pop_back();

                if (l.empty()) {
                    v.pop_front();
                }

                return res;
            }

            if (++nxtb == nodes.size()) {
                base += total;
                nxtb = 0;
            }
        }

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

        //cerr << "get node " << u << " dis = " << d << endl;

        for (auto [v, w] : e[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                b.push(dis[v], v);
                //cerr << "push node " << v << " dis = " << dis[v] << endl;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << dis[i] << " \n"[i == n];
    }

    return 0;
}

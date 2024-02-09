#include <bits/stdc++.h>

using namespace std;

struct Bucket {
    vector<int> size;
    vector<list<int>> nodes;
    int nowb, nown, sz, tmpsz, num;
    long long base;
    bool first_push;
    Bucket(int n) {
        sz = max((int)sqrt(n), 1);
        size.resize((n + sz) / sz);
        nodes.resize(n + 1);
        base = nowb = nown = tmpsz = num = 0;
        first_push = true;
    }
    void push(long long dis, int node) {
        ++num;
        int p = dis % nodes.size();

        if (p < nown && p / sz == nowb && !first_push) {
            ++tmpsz;
        } else {
            ++size[p / sz];
        }

        first_push = false;

        nodes[p].push_back(node);
    }
    bool empty() {
        return !num;
    }
    pair<long long, int> top() {
        --num;
        int nxtb = nowb;

        for (int i = 0; i <= nodes.size(); ++i) {
            if (size[nxtb]) {
                for (; ; ++nown) {
                    if (nodes[nown].empty()) {
                        continue;
                    }

                    auto t = nodes[nown].back();
                    nodes[nown].pop_back();
                    nowb = nxtb;
                    assert(nown / sz == nowb);
                    --size[nowb];
                    //cout << "get " << base + nown << endl;
                    return make_pair(base + nown, t);
                }
            }

            if (nxtb == nowb) {
                size[nowb] = tmpsz;
                tmpsz = 0;
            }

            if (++nxtb == size.size()) {
                base += nodes.size();
                nxtb = 0;
            }

            nown = nxtb * sz;
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

    // assert(mxw <= 5e6);

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
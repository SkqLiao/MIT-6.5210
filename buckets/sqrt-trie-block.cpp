#include <bits/stdc++.h>

using namespace std;

#define OUT cout

struct Trie {
    int C, k, delta;
    struct Pair {
        long long oval;
        int val, node;
        Pair() {
            oval = val = node = -1;
        }
        Pair(long long oval, int val, int node): oval(oval), val(val), node(node) {}
    };
    struct Info {
        int node, ch;
        list<Pair>::iterator it;
        Info() {
            node = ch = -1;
            it = list<Pair>::iterator();
        }
        Info(int node, int ch, list<Pair>::iterator it): node(node), ch(ch), it(it) {}
    };
    vector<Info> info;
    struct Node {
        int depth, val, fa, id, size, tag;
        vector<int> ch;
        vector<list<Pair>> nodes;
        Node() {}
        Node(int delta) {
            depth = val = fa = size = tag = 0;
            id = -1;
            ch.resize(delta);
            nodes.resize(delta);
        }
    };
    vector<int> pw, active;
    vector<Node> v;
    int num, cnt, pre;
    long long base, lastans;
    Trie() {}
    Trie(int n, int C): C(C) {
        info.resize(n + 1, Info());

        if (C <= 2)
            k = 2;
        else
            k = ceil(2 * log2(C) / log2(log2(C)));

        delta = ceil(pow(C, 1.0 / k));
        cnt = 1;
        pre = num = 0;
        lastans = base = 0;
        v.push_back(Node(delta));
        v.push_back(Node(delta));
        pw.push_back(1);

        while (1ll * pw.back() * delta <= C) {
            pw.push_back(pw.back() * delta);
        }

        k = pw.size();
        reverse(pw.begin(), pw.end());
        pw.push_back(1);
        active.resize(k);

        // for (auto x : pw) {
        //     OUT << x << " ";
        // }

        // OUT << endl;
        // OUT << "C = " << C << " k = " << k << " delta = " << delta << endl;
    }
    int newNode() {
        if (++cnt >= v.size()) {
            v.resize(cnt * 2, Node(delta));
        }

        return cnt;
    }
    void move(int x, int o, int depth) {
        if (v[x].nodes[o].empty())
            return ;

        auto y = v[x].ch[o];

        for (auto [oval, val, node] : v[x].nodes[o]) {
            info[node] = Info(y, val / pw[depth], v[y].nodes[val / pw[depth]].insert(v[y].nodes[val / pw[depth]].end(),
                              Pair(oval, val % pw[depth], node)));
        }

        v[y].size += v[x].nodes[o].size();
        v[x].nodes[o].clear();
    }
    void newNode(int fa, int o, int depth) {
        int x = newNode();
        v[x].val = v[fa].val + pw[depth] * o;
        v[x].fa = fa;
        v[x].id = o;
        v[fa].ch[o] = x;
        v[x].depth = v[fa].depth + 1;
        move(fa, o, depth + 1);
    }
    void add(int now, int o, Pair p) {
        auto it = v[now].nodes[o].insert(v[now].nodes[o].end(), p);
        info[p.node] = Info(now, o, it);
    }
    void push(long long val, int node) {
        auto vval = val;
        val %= C;

        if (info[node].node == -1) {
            ++num;

            if (val < lastans) {
                ++v[1].size;
                add(1, val / pw[0], Pair(vval, val % pw[0], node));
                return ;
            }

            insert(vval, val, node);
        } else {
            auto [now, ch, it] = info[node];
            auto [rval, oval, _] = *it;
            --v[now].size;
            v[now].nodes[ch].erase(it);

            if (now == 1 && rval % C < lastans) {
                if (val < lastans) {
                    ++v[1].size;
                    add(1, val / pw[0], Pair(vval, val % pw[0], node));
                    return ;
                } else {
                    insert(vval, val, node);
                }
            } else {
                if (v[now].depth > 0) {
                    insert(vval, val % pw[v[now].depth - 1], node, now);
                } else {
                    insert(vval, val, node, now);
                }
            }
        }
    }
    void insert(long long vval, long long val, int node, int now = 1) {
        for (int i = v[now].depth; i < k; ++i) {
            ++v[now].size;
            int o = val / pw[i];
            val %= pw[i];

            if (active[i] != o) {
                add(now, o, Pair(vval, val, node));
                return ;
            }

            if (!v[now].ch[o]) {
                newNode(now, o, i);
            }

            now = v[now].ch[o];
        }

        ++v[now].size;
        add(now, val, Pair(vval, val, node));
    }
    pair<long long, int> pop(int now) {
        if (v[now].nodes[0].empty()) {
            return make_pair(-1, -1);
        }

        auto [rval, val, node] = v[now].nodes[0].front();
        v[now].nodes[0].pop_front();
        --num;
        --v[now].size;
        --v[now].tag;
        pre = now;
        lastans = v[now].val;
        return make_pair(base + v[now].val, node);
    }
    pair<long long, int> query(int node, int depth, int firo) {
        for (int d = depth; d < k; ++d) {
            for (int i = (d == depth ? firo : 0); i < delta; ++i) {
                auto ch = v[node].ch[i];

                if ((ch && v[ch].size) || v[node].nodes[i].size()) {
                    active[d] = i;

                    if (!ch) {
                        newNode(node, i, d);
                    } else {
                        move(node, i, d + 1);
                    }

                    node = v[node].ch[i];
                    break;
                }
            }
        }

        return pop(node);
    }
    pair<long long, int> queryMin() {
        if (!pre) {
            return query(1, 0, 0);
        }

        auto res = pop(pre);

        if (res.first != -1) {
            return res;
        }

        int node = pre;

        for (int i = k - 1; i >= 0; --i) {
            auto fa = v[node].fa;
            v[fa].tag += v[node].tag;
            v[fa].size += v[node].tag;
            v[node].tag = 0;

            for (int j = v[node].id + 1; j < delta; ++j) {
                auto ch = v[fa].ch[j];

                if ((ch && v[ch].size) || v[fa].nodes[j].size()) {
                    return query(fa, i, j);
                }
            }

            node = v[node].fa;
        }

        base += C;
        return query(1, 0, 0);
    }
};

struct Bucket {
    Trie t;
    int C;
    Bucket(int n, int C) {
        t = Trie(n, C + 1);
    }
    void push(long long dis, int node) {
        t.push(dis, node);
    }
    pair<long long, int> top() {
        return t.queryMin();
    }
    bool empty() {
        return t.num == 0;
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
        mxw = max(mxw, w);
    }

    Bucket b(n, mxw);
    vector<long long> dis(n + 1, LLONG_MAX);
    dis[s] = 0;
    b.push(0, s);

    while (!b.empty()) {
        auto [d, u] = b.top();
        //OUT << "get node " << u << " dis = " << d << endl;
        //OUT << dis[u] << endl;
        //assert(dis[u] == d);

        for (auto [v, w] : e[u]) {
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                //OUT << "push node " << v << " dis = " << dis[v] << endl;
                b.push(dis[v], v);
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << dis[i] << " \n"[i == n];
    }

    return 0;
}
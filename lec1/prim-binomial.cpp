#include <bits/stdc++.h>

using namespace std;

template<class T>
struct BinomialHeap {
    struct Node {
        T key;
        int degree;
        Node *parent, *child, *prv, *nxt;
        Node() {
            degree = 0;
            parent = child = prv = nxt = nullptr;
        }
        Node(T x): key(x) {
            degree = 0;
            parent = child = prv = nxt = nullptr;
        }
    } *head;
    vector<Node *> v;
    int n;
    BinomialHeap() {
        n = 0;
        head = nullptr;
    }
    void alloc() {
        if (n == (int)v.size()) {
            for (int i = 0; i < n; ++i)
                v.push_back(new Node());
        }
    }
    bool empty() {
        return n == 0;
    }
    // add t to head double-linked list
    void link(Node *head, Node *t) {
        if (!t)
            return ;

        if (!head) {
            head = t;
            t->prv = t->nxt = t;
        } else {
            t->prv = head;
            t->nxt = head->nxt;
            head->nxt = t;
            head = head->key < t->key ? head : t;
        }
    }
    // O(1)
    typename vector<Node *>::iterator push(T x) {
        ++n;
        link(head, v[n]);
        return v.begin() + n;
    }
    // O(1)
    T top() {
        assert(n > 0 && head);
        return head->key;
    }
    // O(t+log(n))
    void coalesce() {
        vector<Node *> b(ceil(log(n)), nullptr);
        Node *p = head;

        do {
            Node *q = p->nxt;

            while (b[p->degree]) {
                if (p->key > b[p->degree])
                    swap(p, b[p->degree]);

                p->degree++;

                if (p->child == nullptr) {
                    p->child = b[p->degree];
                    p->child->nxt = p->child->prv = p->child;
                } else {
                    p->child->prev = b[p->degree];
                    b[p->degree]->nxt = p->child;
                }

                b[p->degree]->parent = p;
            }

            b[p->degree] = p;
            p = q;
        } while (p != head);

        head = nullptr;

        for (auto p : b) {
            link(head, p);
        }
    }
    void pop() {
        --n;
        Node *p = head->child;
        Node *nh = head->nxt;

        if (nh == head) {
            nh = p;
        } else {
            do {
                link(nh, p);
                p = p->nxt;
            } while (p != head->child);
        }

        head = p = nh;

        do {
            if (p->key < head->key)
                head = p;

            p = p->nxt;
        } while (p != nh);
    }
    void decrease(typename vector<Node *>::iterator it, T x) {
        Node *p = *it;
        assert(p && x < p->key);
        p->key = x;

        while (p->parent && p->parent->key > x) {
            swap(p->parent, p);
        }
    }
};

int main() {
    freopen("in.txt", "r", stdin);
    cin.tie(nullptr)->sync_with_stdio(false);
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

    BinomialHeap<pair<int, int>> pq;
    cout << "???" << endl;
    return 0;
    vector<optional<vector<decltype(pq)::Node *>::iterator>> it(n + 1);
    vector<int> dis(n + 1, 1e9);
    vector<bool> vis(n + 1);
    dis[1] = 0;
    it[1] = pq.push({0, 1});
    return 0;

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        ans += dis[u];
        vis[u] = 1;
        ++cnt;

        for (auto [v, w] : g[u]) {
            if (!vis[v] && dis[v] > w) {
                dis[v] = w;

                if (it[v] != nullopt)
                    pq.decrease(it[v].value(), {w, v});
                else
                    it[v] = pq.push({w, v});
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
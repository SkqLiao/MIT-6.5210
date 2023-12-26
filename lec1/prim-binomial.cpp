// C++ program for the above approach
#include <bits/stdc++.h>

using namespace std;

#define DEBUG cout << "[" << __FUNCTION__ << "] " << endl;

template<typename T, typename G>
ostream &operator<<(std::ostream &os, const std::pair<T, G> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<class T>
struct BinomialHeap {
    struct Node {
        T key;
        int degree;
        shared_ptr<Node> parent, child, prev, next;
        Node(T val): key(val), degree(0) {
            parent = child = prev = next = nullptr;
        }
    };
    friend ostream &operator<<(std::ostream &os, shared_ptr<Node> &p) {
        if (p == nullptr)
            os << "[nullptr]";
        else
            os << "[key = " << p->key << ", degree = (" << p->degree << ")" << ", parent = (" << p->parent << ")]";

        return os;
    }
    shared_ptr<Node> head;
    size_t n;
    BinomialHeap() {
        n = 0;
        head = nullptr;
    }
    // O(1) empty
    bool empty() {
        return n == 0;
    }
    // O(1) size
    size_t size() {
        return n;
    }
    // O(1) push
    shared_ptr<Node> push(T x) {
        ++n;
        auto t = make_shared<Node>(x);
        t->prev = t->next = t;
        _link(head, t);

        if (t->key <= head->key)
            head = t;

        return std::move(t);
    }
    // O(1) top
    T top() {
        assert(n);
        return head->key;
    }
    // O(logn) pop
    void pop() {
        assert(n > 0);
        --n;

        if (!n) {
            head = nullptr;
            return ;
        }

        if (head->child) {
            _link(head, head->child);
            _consolidate();
        }

        auto p = head->next;
        _remove(head);
        head = p;

        do {
            if (p->key <= head->key)
                head = p;

            p = p->next;
        } while (p != head);
    }
    // O(logn) decrease
    void decrease(shared_ptr<Node> &p, T x) {
        assert(x < p->key);
        p->key = x;

        while (p->parent && p->parent->key > p->key) {
            _swapParent(p);
        }

        if (head->key > x) {
            head = p;
        }
    }
private:
    // remove a from its double-linked list
    void _remove(shared_ptr<Node> &a) {
        auto pa = a->prev, na = a->next;
        pa->next = na;
        na->prev = pa;

        if (a->parent && a->parent->child == a) {
            if (na != a)
                a->parent->child = na;
            else
                a->parent->child = nullptr;
        }
    }
    // merge double-linked list b into a
    void _merge(shared_ptr<Node> &a, shared_ptr<Node> &b) {
        if (!b)
            return ;

        if (!a) {
            a = b;
            return ;
        }

        auto tailA = a->prev, tailB = b->prev;
        tailA->next = b;
        b->prev = tailA;
        tailB->next = a;
        a->prev = tailB;
    }
    void _setParent(shared_ptr<Node> &a, shared_ptr<Node> parent) {
        auto p = a;

        do {
            p->parent = parent;
            p = p->next;
        } while (p != a);
    }
    // merge double-linked b into a and set parent
    void _link(shared_ptr<Node> &a, shared_ptr<Node> &b) {
        if (!a) {
            a = b;
            _setParent(a, nullptr);
        } else {
            _setParent(b, a->parent);
            _merge(a, b);
        }
    }
    void _consolidate() {
        int m = static_cast<int>(ceil(log2(n)));
        vector<shared_ptr<Node>> a(m + 1, nullptr);
        auto p = head;

        do {
            auto np = p->next;

            while (a[p->degree]) {
                auto q = a[p->degree];

                if (p->key > q->key)
                    swap(p, q);

                _remove(q);
                _link(p->child, q);
                a[p->degree] = nullptr;
                ++p->degree;
            }

            a[p->degree] = p;
            p = np;
        } while (p != head);

        head = nullptr;

        for (auto &x : a) {
            if (!x)
                continue;

            _link(head, x);

            if (x->key <= head->key)
                head = x;
        }
    }
    void _swapParent(shared_ptr<Node> &x) {
        auto y = x->parent;
        auto z = y->parent;
        _setParent(x, x);
        _setParent(x->child, y);
        _remove(x);
        _link(y, x); // already set x->parent to y->parent
        _remove(y); // if z->child = y, then set z->child to others
        _link(x->child, y);
        y->parent = x; // x->child may be nullptr
        swap(x->key, y->key);
        swap(x->degree, y->degree);
    }
    void _print(shared_ptr<Node> &x) {
        auto p = x;

        do {
            cout << p->key << "(" << p->degree << ") -> ";
            p = p->next;
        } while (p != x);

        cout << endl;
    }
};

int main() {
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
    vector<shared_ptr<decltype(pq)::Node>> it(n + 1, nullptr);
    vector<int> dis(n + 1, 1e9);
    vector<bool> vis(n + 1);
    dis[1] = 0;
    it[1] = pq.push({0, 1});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        ans += dis[u];
        vis[u] = 1;
        ++cnt;

        for (auto [v, w] : g[u]) {
            if (!vis[v] && dis[v] > w) {
                dis[v] = w;

                if (it[v]) {
                    pq.decrease(it[v], {dis[v], v});
                } else {
                    it[v] = pq.push({dis[v], v});
                }
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
#include <bits/stdc++.h>

using namespace std;

class Splay {
    struct Node {
        int val, cnt, sz;
        bool lazy;
        shared_ptr<Node> ch[2], fa;
        Node() {
            val = cnt = sz = 0;
            lazy = false;
            ch[0] = ch[1] = fa = nullptr;
        }
        Node(int x): Node() {
            cnt = sz = 1;
            val = x;
        }
    };
    shared_ptr<Node> rt;
    vector<shared_ptr<Node>> v;
    int n, cnt = 0;
    shared_ptr<Node> newNode(int val) {
        if (++cnt >= v.size()) {
            v.resize(cnt * 2, make_shared<Node>());
        }

        return v[cnt] = make_shared<Node>(val);
    }
    bool get(shared_ptr<Node> t) {
        return t->fa->ch[1] == t;
    }
    void maintain(shared_ptr<Node> t) {
        t->sz = t->cnt;

        if (t->ch[0])
            t->sz += t->ch[0]->sz;

        if (t->ch[1])
            t->sz += t->ch[1]->sz;
    }
    void rotate(shared_ptr<Node> x) {
        auto y = x->fa, z = y->fa;
        bool chk = get(x);
        y->ch[chk] = x->ch[chk ^ 1];

        if (x->ch[chk ^ 1])
            x->ch[chk ^ 1]->fa = y;

        x->ch[chk ^ 1] = y;
        y->fa = x;
        x->fa = z;

        if (z)
            z->ch[y == z->ch[1]] = x;

        maintain(y);
        maintain(x);
    }
    void splay(shared_ptr<Node> x, shared_ptr<Node> goal = nullptr) {
        if (!goal)
            rt = x;

        while (x->fa != goal) {
            auto f = x->fa, g = f->fa;

            if (g != goal) {
                if (get(f) == get(x))
                    rotate(x);
                else
                    rotate(f);
            }

            rotate(x);
        }
    }
    void tagrev(shared_ptr<Node> x) {
        swap(x->ch[0], x->ch[1]);
        x->lazy ^= 1;
    }

    void pushdown(shared_ptr<Node> x) {
        if (x->lazy) {
            if (x->ch[0])
                tagrev(x->ch[0]);

            if (x->ch[1])
                tagrev(x->ch[1]);

            x->lazy = 0;
        }
    }
    shared_ptr<Node> build(int l, int r, shared_ptr<Node> f, vector<int> &a) {
        if (l > r)
            return nullptr;

        int mid = (l + r) / 2;
        auto t = newNode(a[mid - 1]);
        t->fa = f;
        t->ch[0] = build(l, mid - 1, t, a);
        t->ch[1] = build(mid + 1, r, t, a);
        maintain(t);
        return t;
    }
    shared_ptr<Node> getKth(int k) {
        auto t = rt;

        while (true) {
            assert(t);
            pushdown(t);

            if (t->ch[0] && k <= t->ch[0]->sz) {
                t = t->ch[0];
            } else {
                k -= 1 + (t->ch[0] ? t->ch[0]->sz : 0);

                if (k <= 0) {
                    splay(t);
                    break;
                }

                t = t->ch[1];
            }
        }

        return t;
    }
public:
    void build(vector<int> &a) {
        n = a.size() - 2;
        rt = build(1, a.size(), nullptr, a);
    }
    void reverse(int l, int r) {
        ++l, ++r;
        auto L = getKth(l - 1);
        auto R = getKth(r + 1);
        splay(L);
        splay(R, L);
        tagrev(L->ch[1]->ch[0]);
    }
    void print() {
        print(rt);
        cout << '\n';
    }
    void print(shared_ptr<Node> t) {
        pushdown(t);

        if (t->ch[0]) {
            print(t->ch[0]);
        }

        if (t->val >= 1 && t->val <= n)
            cout << t->val << ' ';

        if (t->ch[1]) {
            print(t->ch[1]);
        }
    }
};

int main() {
    cin.tie(NULL)->ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    Splay t;
    vector<int> a(n + 2);
    iota(a.begin(), a.end(), 0);

    t.build(a);

    while (m--) {
        int l, r;
        cin >> l >> r;
        t.reverse(l, r);
    }

    t.print();

    return 0;
}
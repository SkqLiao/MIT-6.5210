#include <bits/stdc++.h>

using namespace std;

class Splay {
    struct Node {
        int val, cnt, sz;
        shared_ptr<Node> ch[2], fa;
        Node() {
            val = cnt = sz = 0;
            ch[0] = ch[1] = fa = nullptr;
        }
        Node(int x): Node() {
            cnt = sz = 1;
            val = x;
        }
    };
    shared_ptr<Node> rt;
    vector<shared_ptr<Node>> v;
    int cnt = 0;
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
    void splay(shared_ptr<Node> x) {
        for (shared_ptr<Node> y; x->fa; rotate(x)) {
            if ((y = x->fa)->fa) {
                //cout << "rotate " << x->val << " " << y->val << endl;
                rotate(get(x) == get(y) ? y : x);
            }
        }

        rt = x;
    }
    shared_ptr<Node>pre() {
        auto t = rt->ch[0];

        if (!t)
            return t;

        while (t->ch[1]) {
            t = t->ch[1];
        }

        splay(t);
        return t;
    }
    shared_ptr<Node> nxt() {
        auto t = rt->ch[1];

        if (!t)
            return nullptr;

        while (t->ch[0]) {
            t = t->ch[0];
        }

        splay(t);
        return t;
    }
public:
    Splay() {}
    void insert(int key) {
        if (!rt) {
            rt = newNode(key);
            return ;
        }

        shared_ptr<Node> t = rt, f = nullptr;

        while (true) {
            if (t->val == key) {
                t->cnt++;
                maintain(t);
                break;
            }

            f = t;
            t = f->ch[key > f->val];

            if (!t) {
                t = newNode(key);
                t->fa = f;
                f->ch[key > f->val] = t;
                maintain(f);
                maintain(t);
                break;
            }
        }

        splay(t);
    }
    int getRank(int key) {
        auto t = rt;
        int ans = 0;

        while (t) {
            if (t->val == key) {
                ans += t->ch[0] ? t->ch[0]->sz : 0;
                splay(t);
                break;
            }

            if (t->val < key) {
                ans += t->ch[0] ? t->ch[0]->sz : 0;
                ans += t->cnt;
                t = t->ch[1];
            } else {
                t = t->ch[0];
            }
        }

        return ans + 1;
    }
    int getKth(int k) {
        auto t = rt;

        while (t) {
            if (t->ch[0] && t->ch[0]->sz >= k) {
                t = t->ch[0];
            } else {
                k -= t->ch[0] ? t->ch[0]->sz : 0;

                if (k <= t->cnt) {
                    splay(t);
                    return t->val;
                }

                k -= t->cnt;
                t = t->ch[1];
            }
        }

        assert(0);
    }
    void remove(int key) {
        getRank(key);

        if (rt->cnt > 1) {
            rt->cnt--;
            rt->sz--;
            return ;
        }

        if (!rt->ch[0] && !rt->ch[1]) {
            rt = nullptr;
            return ;
        }

        for (int i = 0; i <= 1; ++i) {
            if (!rt->ch[i]) {
                rt = rt->ch[i ^ 1];
                rt->fa = nullptr;
                return ;
            }
        }

        auto cur = rt;
        auto x = pre();

        cur->ch[1]->fa = x;

        if (x)
            x->ch[1] = cur->ch[1];

        maintain(rt);
    }
    int getPre(int key) {
        insert(key);
        auto t = pre();
        remove(key);
        return t->val;
    }
    int getNxt(int key) {
        insert(key);
        auto t = nxt();
        remove(key);
        return t->val;
    }
    void print() {
        if (rt)
            print(rt);

        cerr << endl;
    }
    void print(shared_ptr<Node> t) {
        if (t->ch[0]) {
            assert(t->ch[0]->fa == t);
            assert(t->ch[0]->val < t->val);
            print(t->ch[0]);
        }

        cerr << t->val << ' ';

        if (t->ch[1]) {
            assert(t->ch[1]->fa == t);
            assert(t->ch[1]->val > t->val);
            print(t->ch[1]);
        }
    }
};

int main() {
    cin.tie(NULL)->ios::sync_with_stdio(false);
    int n;
    cin >> n;
    Splay t;

    while (n--) {
        int op, x;
        cin >> op >> x;
        // cerr << "op: " << op << " x: " << x << endl;

        if (op == 1) {
            t.insert(x);
        } else if (op == 2) {
            t.remove(x);
        } else if (op == 3) {
            cout << t.getRank(x) << '\n';
        } else if (op == 4) {
            cout << t.getKth(x) << '\n';
        } else if (op == 5) {
            cout << t.getPre(x) << '\n';
        } else {
            cout << t.getNxt(x) << '\n';
        }

        // t.print();
    }

    return 0;
}
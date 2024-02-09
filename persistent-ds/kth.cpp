#include <bits/stdc++.h>

using namespace std;

struct SegmentTree {
    struct Node {
        Node *l, *r;
        int siz;
        Node(): l(nullptr), r(nullptr), siz(0) {}
    } t[200000 * 25];
    int cnt, root;
    SegmentTree(): root(0), cnt(0) {}
    void build(Node *&rt, int l, int r) {
        rt = t + ++cnt;

        if (l == r) {
            return ;
        }

        int m = (l + r) >> 1;
        build(rt->l, l, m);
        build(rt->r, m + 1, r);
    }
    Node *update(Node *pre, int l, int r, int x) {
        Node *rt = t + ++cnt;
        *rt = *pre;
        ++rt->siz;

        if (l == r) {
            return rt;
        }

        int m = (l + r) >> 1;

        if (x <= m) {
            rt->l = update(pre->l, l, m, x);
        } else {
            rt->r = update(pre->r, m + 1, r, x);
        }

        return rt;
    }
    int query(Node *&a, Node *&b, int l, int r, int k) {
        if (l == r) {
            return l;
        }

        int m = (l + r) >> 1;
        int cnt = a->l->siz - b->l->siz;

        if (k <= cnt) {
            return query(a->l, b->l, l, m, k);
        } else {
            return query(a->r, b->r, m + 1, r, k - cnt);
        }
    }
} tree;

int main() {
    cin.tie(nullptr)->ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> v;
    v.resize(n + 1);

    for (int i = 1; i <= n; ++i)
        cin >> v[i];

    vector<int> t(v);
    sort(t.begin(), t.end());
    t.erase(unique(t.begin(), t.end()), t.end());
    auto getId = [&](int x) {
        return lower_bound(t.begin(), t.end(), x) - t.begin() + 1;
    };
    int nn = t.size();

    for (int i = 1; i <= n; ++i) {
        v[i] = getId(v[i]);
    }

    vector<SegmentTree::Node *> rt(n + 1);
    tree.build(rt[0], 1, nn);

    for (int i = 1; i <= n; ++i) {
        rt[i] = tree.update(rt[i - 1], 1, nn, v[i]);
    }

    for (int i = 1; i <= m; ++i) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << t[tree.query(rt[r], rt[l - 1], 1, nn, k) - 1] << "\n";
    }

    return 0;
}
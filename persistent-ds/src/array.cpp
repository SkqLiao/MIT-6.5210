#include <bits/stdc++.h>
#include <chrono>

using namespace std;

struct Node {
    int l, r, val;
};

vector<Node> t;

int newNode() {
    t.emplace_back();
    return t.size() - 1;
}

int build(int l, int r, const vector<int> &v) {
    int rt = newNode();

    if (l == r) {
        t[rt].val = v[l];
        return rt;
    }

    int m = (l + r) / 2;
    t[rt].l = build(l, m, v);
    t[rt].r = build(m + 1, r, v);
    return rt;
}

int query(int rt, int l, int r, int p) {
    if (l == r) {
        return t[rt].val;
    }

    int m = (l + r) / 2;
    return p <= m ? query(t[rt].l, l, m, p) : query(t[rt].r, m + 1, r, p);
}

int modify(int rt, int l, int r, int p, int x) {
    int nrt = newNode();
    t[nrt] = t[rt];
    int m = (l + r) / 2;

    if (l == r) {
        t[nrt].val = x;
        return nrt;
    }

    if (p <= m)
        t[nrt].l = modify(t[rt].l, l, m, p, x);
    else
        t[nrt].r = modify(t[rt].r, m + 1, r, p, x);

    return nrt;
}

int main() {
    auto start = chrono::steady_clock::now();
    cin.tie(NULL)->ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 1);
    vector<int> root(m + 1);

    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }

    root[0] = build(1, n, v);

    for (int i = 1; i <= m; ++i) {
        int ver, opt, pos, val;
        cin >> ver >> opt >> pos;

        if (opt == 1) {
            cin >> val;
            root[i] = modify(root[ver], 1, n, pos, val);
        } else {
            root[i] = root[ver];
            cout << query(root[ver], 1, n, pos) << '\n';
        }
    }

    auto end = chrono::steady_clock::now();
    cerr << "Elapsed time in seconds : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " millisec" << endl;
    return 0;
}
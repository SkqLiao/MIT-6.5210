#include <bits/stdc++.h>

using namespace std;

struct DSU {
    vector<int> fa, rank;
    int n;
    DSU(int n): n(n) {
        fa.resize(n + 1);
        rank.resize(n + 1);
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    bool merge(int x, int y) {
        x = find(x), y = find(y);

        if (x == y)
            return false;

        if (rank[x] < rank[y])
            swap(x, y);

        fa[x] = y;
        rank[x] += rank[x] == rank[y];
        return true;
    }
};

struct LeftistTree {
    struct Node {
        int val, dist;
        Node *l, *r;
        Node(int val): val(val), dist(0), l(nullptr), r(nullptr) {}
    };
    Node *root;
    LeftistTree(): root(nullptr) {}
    Node *merge(Node *a, Node *b) {
        if (!a || !b)
            return a ? a : b;

        if (a->val > b->val)
            swap(a, b);

        a->r = merge(a->r, b);

        if (!a->l || a->l->dist < a->r->dist)
            swap(a->l, a->r);

        a->dist = a->r ? a->r->dist + 1 : 0;
        return a;
    }
    void insert(int val) {
        root = merge(root, new Node(val));
    }
    int top() {
        return root->val;
    }
    void pop() {
        Node *tmp = root;
        root = merge(root->l, root->r);
        delete tmp;
    }
} T;

int main() {

    return 0;
}
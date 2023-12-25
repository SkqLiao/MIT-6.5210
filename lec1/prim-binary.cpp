#include <bits/stdc++.h>

using namespace std;

template<class T>
struct BinaryHeap {
    struct Iterator {
        int *id;
        Iterator() {
            id = new int;
            *id = -1;
        }
        void setid(int loc) {
            *id = loc;
        }
        bool empty() {
            return *id == -1;
        }
    };
    int n;
    vector<T> v;
    vector<Iterator> p;

    BinaryHeap() {
        n = 0;
        v.resize(1);
        p.emplace_back();
    }

    // allocate more(double) space, O(n)
    void alloc() {
        if (n >= (int)v.size()) {
            v.resize(v.size() * 2);
            p.resize(p.size() * 2);
        }
    }

    // push an element, O(log(n))
    Iterator push(T x) {
        ++n;
        alloc();
        v[n] = x;
        p[n].setid(n);
        return heapifyUp(n);
    }

    // return whether the heap is empty, O(1)
    bool empty() {
        return n == 0;
    }

    // return the top element, O(1)
    T top() {
        assert(n > 0);
        return v[1];
    }

    // pop the top element, O(log(n))
    void pop() {
        assert(n > 0);
        v[1] = v[n];
        swap(p[1], p[n]);
        p[1].setid(1);
        p[n].setid(-1);
        --n;
        heapifyDown(1);
    }

    // decrease the value of an element, O(log(n))
    void decrease(Iterator it, T x) {
        int i = *it.id;
        v[i] = x;
        heapifyUp(i);
    }
private:
    // swap two elements, O(1)
    void _swap(int i, int j) {
        swap(v[i], v[j]);
        swap(p[i], p[j]);
        p[i].setid(i), p[j].setid(j);
    }
    // heapify up, O(log(n))
    Iterator heapifyUp(int i) {
        while (i > 1 && v[i] < v[i >> 1]) {
            _swap(i, i >> 1);
            i >>= 1;
        }

        return p[i];
    }
    // heapify down, O(log(n))
    void heapifyDown(int i) {
        while (i << 1 <= n) {
            int j = i << 1;

            if (j < n && v[j + 1] < v[j])
                ++j;

            if (v[i] <= v[j])
                break;

            _swap(i, j);
            i = j;
        }
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

    BinaryHeap<pair<int, int>> pq;
    vector<decltype(pq)::Iterator> it(n + 1);
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

                if (!it[v].empty())
                    pq.decrease(it[v], {w, v});
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
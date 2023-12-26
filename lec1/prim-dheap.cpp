#include <bits/stdc++.h>

using namespace std;

template<class T>
struct DHeap {
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
    int n, d;
    vector<T> v;
    vector<Iterator> p;

    DHeap(int d = 4): d(d) {
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
    int parent(int i) {
        return (i - 2) / d + 1;
    }
    // heapify up, O(log_d(n))
    Iterator heapifyUp(int i) {
        while (i > 1 && v[i] < v[parent(i)]) {
            _swap(i, parent(i));
            i = parent(i);
        }

        return p[i];
    }
    // heapify down, O(d*log_d(n))
    void heapifyDown(int i) {
        while ((i - 1) * d + 2 <= n) {
            int j = (i - 1) * d + 2;

            for (int k = j + 1, _kend = min(j + d - 1, n); k <= _kend; ++k)
                if (v[k] < v[j])
                    j = k;

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

    DHeap<pair<int, int>> pq((m + n - 1) / n);
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
                    pq.decrease(it[v], {dis[v], v});
                else
                    it[v] = pq.push({dis[v], v});
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
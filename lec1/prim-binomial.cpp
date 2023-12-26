#include <bits/stdc++.h>

using namespace std;

template<class T>
struct Heap {
    struct Node {
        T key;
        int degree;
        shared_ptr<Node> parent, child, prv, nxt;
        Node() : key(0), degree(0) {}
        Node(T x) : key(x), degree(0) {}
    };
    shared_ptr<Node> head;
    int n;
    Heap() {
        n = 0;
    }
    bool empty() {
        return n == 0;
    }
    void link(shared_ptr<Node> &head, shared_ptr<Node> &t) {
        // link t to the right side of head
        if (!t)
            return ;

        if (!head) {
            head = t;
            head->prev = head->next = head;
        } else if (head->next == head) {
            head->next = t;
            head->prev = t;
            t->prev = head;
            t->next = head;
            head = head->key < head->next->key ? head : head->next;
        } else {
            t->prev = head;
            t->next = head->next;
            head->next = t;
            head = head->key < head->next->key ? head : head->next;
        }
    }
    // O(1)
    shared_ptr<Node> push(T x) {
        ++n;
        auto t = make_shared<Node>(x);
        link(head, t);
        return std::move(t);
    }
    // O(1)
    T top() {
        assert(!empty());
        return head->key;
    }
    // O(logn+t)
    void pop() {
        assert(n > 0);
        auto t = head->child;

        if (t) {
            do {
                t->parent = nullptr;
                t = t->next;
            } while (t != head->child);

            if (head->next == head) {
                head = t;
            } else {
                auto nh = head->next;
                nh->prev = head->prev;
                nh->prev->next = nh;
                head = nh;
                nh = head->next;
                head->next = t;
                t->prev->next = nh;
                nh->prev = t->prev;
                t->prev = head;
            }
        }

        consolidate();
    }
    void consolidate() {
        vector<shared_ptr<Node>> a;
        shared_ptr<Node> t = head;
        int d = 0;

        do {
            d = max(d, t->degree);
            t = t->next;
        } while (t != head);

        a.resize(d + 2, nullptr);

        do {
            while (a[t->degree]) {
                auto x = a[t->degree];
                a[t->degree] = nullptr;

                if (t->key > x->key) {
                    swap(t, x);
                }

                t->degree++;
                x->parent = t;
                link(t->child, x);
            }

            a[t->degree] = t;
        } while (t != head);

        auto p = head;

        do {
            if (t->key < head->key) {
                head = t;
            }

            t = t->next;
        } while (t != head);
    }
};

int main() {

    return 0;
}

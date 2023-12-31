#include <bits/stdc++.h>
#include <chrono>
#include <random>

using namespace std;

auto seed = chrono::system_clock::now().time_since_epoch().count();
mt19937 rd(seed);

int main() {
    int n = 1e6, m = 1e6;
    cout << n << " " << m << endl;
    uniform_int_distribution<int> dv(-1e9, 1e9);
    uniform_int_distribution<int> dn(1, n);

    for (int i = 1; i <= n; ++i) {
        cout << dv(rd) << " \n"[i == n];
    }

    for (int i = 1; i <= m; ++i) {
        int op = dn(rd) % 2 + 1;
        int pos = dn(rd);
        int val = dv(rd);
        int ver = dn(rd) % i;

        if (op == 1) {
            cout << ver << " " << 1 << " " << pos << " " << val << "\n";
        } else {
            cout << ver << " " << 2 << " " << pos << "\n";
        }
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(2e9) + int(1e8);
const ll infl = ll(2e18) + ll(1e10);

const int base = 1 << 17;

ll func(int p, int q) {
    if (p >= 0)
        return p / q;
    return -((-p + q - 1) / q);
}

int iter;

struct Tree {
    ll sum[base * 2];
    int vmin[base * 2];
    int vmax[base * 2];
    int add[base * 2];

    void update(int u) {
        vmin[u] = min(vmin[u * 2], vmin[u * 2 + 1]);
        vmax[u] = max(vmax[u * 2], vmax[u * 2 + 1]);
        sum[u] = sum[u * 2] + sum[u * 2 + 1];
    }

    void _put(int u, int val, int len) {
        add[u] += val;
        vmin[u] += val;
        vmax[u] += val;
        sum[u] += val * len;
    }

    void push(int u, int cl, int cr) {
        if (add[u]) {
            int len = (cr - cl) / 2;
            _put(u * 2, add[u], len);
            _put(u * 2 + 1, add[u], len);
            add[u] = 0;
        }
    }

    ll getSum(int l, int r, int v = 1, int cl = 0, int cr = base) {
        if (l <= cl && cr <= r)
            return sum[v];
        if (r <= cl || cr <= l)
            return 0;
        int cc = (cl + cr) / 2;
        push(v, cl, cr);
        return getSum(l, r, v * 2, cl, cc) + getSum(l, r, v * 2 + 1, cc, cr);
    }

    int getMax(int l, int r, int v = 1, int cl = 0, int cr = base) {
        if (l <= cl && cr <= r)
            return vmax[v];
        if (r <= cl || cr <= l)
            return -inf;
        int cc = (cl + cr) / 2;
        push(v, cl, cr);
        return max(getMax(l, r, v * 2, cl, cc), getMax(l, r, v * 2 + 1, cc, cr));
    }

    int getMin(int l, int r, int v = 1, int cl = 0, int cr = base) {
        if (l <= cl && cr <= r)
            return vmin[v];
        if (r <= cl || cr <= l)
            return inf;
        int cc = (cl + cr) / 2;
        push(v, cl, cr);
        return min(getMin(l, r, v * 2, cl, cc), getMin(l, r, v * 2 + 1, cc, cr));
    }

    void put(int l, int r, int delta, int v = 1, int cl = 0, int cr = base) {
        if (l <= cl && cr <= r) {
            _put(v, delta, cr - cl);
            return;
        }
        if (r <= cl || cr <= l)
            return;
        int cc = (cl + cr) / 2;
        push(v, cl, cr);
        put(l, r, delta, v * 2, cl, cc);
        put(l, r, delta, v * 2 + 1, cc, cr);
        update(v);
    }

    void divide(int l, int r, int x, int v = 1, int cl = 0, int cr = base) {
        ++iter;
        if (x == 1)
            return;
        if (l <= cl && cr <= r) {
            int d1 = func(vmin[v], x) - vmin[v];
            int d2 = func(vmax[v], x) - vmax[v];
            if (d1 == d2) {
                _put(v, d1, cr - cl);
                return;
            }
        }
        if (r <= cl || cr <= l)
            return;
        int cc = (cl + cr) / 2;
        push(v, cl, cr);
        divide(l, r, x, v * 2, cl, cc);
        divide(l, r, x, v * 2 + 1, cc, cr);
        update(v);
    }

    void build(int n) {
        forn (i, 2 * base)
            add[i] = 0;
        for (int i = n + base; i < 2 * base; ++i)
            sum[i] = 0, vmin[i] = inf, vmax[i] = -inf;
        for (int i = base - 1; i > 0; --i)
            update(i);
    }
} t;

int main() {

    int n, q;
    scanf("%d%d", &n, &q);
    forn (i, n) {
        int a;
        scanf("%d", &a);
        t.sum[i + base] = t.vmin[i + base] = t.vmax[i + base] = a;
    }
    t.build(n);
    forn (i, q) {
        int op, l, r, x;
        scanf("%d%d%d", &op, &l, &r);
        l++;
        r++;
        if (op == 1 || op == 2)
            scanf("%d", &x);
        --l;
        if (op == 1)
            t.put(l, r, x);
        else if (op == 2)
            t.divide(l, r, x);
        else if (op == 3)
            cout << t.getMin(l, r) << '\n';
        else if (op == 4)
            cout << t.getSum(l, r) << '\n';
        else
            assert(false);
    }
    cerr << iter << " iterations\n";
    cerr << "time: " << clock() / 1000 << "ms\n";
}
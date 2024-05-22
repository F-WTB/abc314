#include <bits/stdc++.h>
#include <atcoder/all>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace atcoder;
using ll = long long;
using bint = boost::multiprecision::cpp_int;
using mint = modint998244353;
using pr = pair<int, int>;
ostream &operator<<(ostream &os, const mint &x) {
    os << x.val();
    return os;
}
template <class T>
inline bool chmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
template <class T>
inline bool chmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
struct fast {
    fast() {
        cin.tie(0);
        ios::sync_with_stdio(0);
    }
} fast;

int N, p, q;

vector<int> g[400000];
int a[200000], s[400000];
mint ans[400000];

void dfs(int v) {
    for (int nv : g[v]) {
        dfs(nv);
        s[v] += s[nv];
    }
}

void dfs2(int v) {
    for (int nv : g[v]) {
        for (int nv : g[v]) ans[nv] = mint(s[nv]) / s[v] + ans[v];
        dfs2(nv);
    }
}

int main() {
    cin >> N;
    fill(s, s + N, 1);
    dsu d(N);
    for (int i = 0; i < N; ++i) a[i] = i;

    for (int i = 0; i < N - 1; ++i) {
        cin >> p >> q;
        --p, --q;
        int x = a[d.leader(p)];
        int y = a[d.leader(q)];
        g[N + i].push_back(x);
        g[N + i].push_back(y);
        int z = d.merge(p, q);
        a[z] = N + i;
    }

    dfs(2 * N - 2);
    dfs2(2 * N - 2);

    for (int i = 0; i < N; ++i) cout << ans[i] << (i < N - 1 ? '\t' : '\n');
}

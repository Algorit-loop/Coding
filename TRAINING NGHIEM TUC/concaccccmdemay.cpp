#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#include <chrono>
#include <random>
#include <set>
#include <unordered_set>
#include <bitset>
#include <map>
#include <unordered_map>
#include <queue>
#include <deque>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <stack>

using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define int long long
#define ld long double
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define ii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define plii pair<ll,pair<int,int>>
#define heapmax(type) priority_queue<type>
#define heapmin(type) priority_queue<type,vector<type>,greater<type>>
#define ordered_multiset  tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_set       tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define FASTIO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define sz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
#define getbit(mask,i) ((mask >> i) & 1)

template<typename T> bool maximize(T &res, const T &val) { if (res <  val) { res = val; return true; } return false; }
template<typename T> bool minimize(T &res, const T &val) { if (res >  val) { res = val; return true; } return false; }
template<typename T> ll rv_num(T x){
    ll res = 0;
    while (x > 0) res = res*10 + x % 10 , x/=10;
    return res;
}
const ll mod = 1e9 + 7;
const ld PI = acos(-1);
const int N = 1e6 + 100;
const int N_Trie = 1e5;
const int N_ST = 2e5 + 10;
const int N_BIT = 2e5 + 10;
const int ooint = (1LL << 31) - 1;
const int LIM = 1e7;
const int N_MST = 1e5;
const int N_Hash = 2e6 + 10;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}

ll power(ll a,ll b,ll c){
    ll res = 1;
    a = a % c;
    for (; b > 0; b >>= 1 , a = a * a % c)
        if (b & 1) res = res * a % c;
    return res;
}

int n , q, a[N],b[N];
struct matcher {
    const int oo = 100000000;
    int m, n;
    vector<int> mx, my, dist;
    vector<vector<int>> ke;
    int matched;

    matcher(int m, int n):
        m(m), n(n),
        mx(m+1, 0), my(n+1, 0), dist(m+1),
        ke(m+1),
        matched(0) {}

    void add_edge(int u, int v) {
        ke[u].push_back(v);
    }

    bool bfs() {
        queue<int> Q;
        for (int u=1; u<=m; u++) {
            if (!mx[u]) {
                dist[u] = 0;
                Q.push(u);
            } else {
                dist[u] = oo;
            }
        }

        bool found = false;
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            for (int v: ke[u]) {
                if (!my[v]) {
                    found = true;
                } else if (dist[my[v]] == oo) {
                    dist[my[v]] = dist[u] + 1;
                    Q.push(my[v]);
                }
            }
        }

        return found;
    }

    bool dfs(int u) {
        if (dist[u] == oo) return false;
        for (int v: ke[u]) {
            if (!my[v] || (dist[my[v]]==dist[u]+1 && dfs(my[v]))) {
                mx[u] = v;
                my[v] = u;
                return true;
            }
        }
        return false;
    }

    void match() {
        while(bfs()) {
            for (int u=1; u<=m; u++) if (!mx[u]) matched += dfs(u);
        }
    }
};


void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];
    int l = 1, r = 1e6, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        matcher z(n,n);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i] % b[j] == 0 &&a[i] / b[j] >=mid) z.add_edge(i,n+j);
            }
        }

        for (int j = 1; j <= n; j++) {
            for (int i = 1; i <= n; i++) {
                z.add_edge(n+j,i);
            }
        }
         z.match();
        bool check = false;
        if (z.matched == 2*n) check = true;
        if (check) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans << "\n";
}

signed main() {
    FASTIO;
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}

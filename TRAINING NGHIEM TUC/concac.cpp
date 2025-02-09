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
#define FASTIO ios::sync_with_stdio(NULL); cin.tie(NULL); cout.tie(NULL);
#define sz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
#define getbit(mask,i) ((mask >> i) & 1)

template<typename T> bool maximize(const T &res, const T &val) { if (res <  val) { res = val; return true; } return false; }
template<typename T> bool minimize(const T &res, const T &val) { if (res >  val) { res = val; return true; } return false; }
template<typename T> ll rv_num(T x){
    ll res = 0;
    while (x > 0) res = res*10 + x % 10 , x/=10;
    return res;
}
const ll mod = 1e9 + 7;
const ld PI = acos(-1);
const int N = 2e5 + 100;
const int N_Trie = 1e5;
const int N_ST = 2e5 + 10;
const int N_BIT = 2e5 + 10;
const int ooint = (1LL << 31) - 1;
// const ll ooll = (1LL << 63) - 1;
const int LIM = 1e7; // N_Prime
const int N_MST = 1e5; // N of Merge Sort Tree
const int N_Hash = 2e6 + 10;

        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void file(const string FILE){
    if (fopen((FILE + ".INP").c_str(),"r")){
        freopen((FILE + ".INP").c_str(), "r", stdin);
        freopen((FILE + ".OUT").c_str(), "w", stdout);
    }
}
ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}

ll power(ll a,ll b,ll c){ // O(log(b))
    ll res = 1;
    a = a % c;
    for (; b > 0; b >>= 1 , a = a * a % c)
        if (b & 1) res = res * a % c;
    return res;
}

int n , m;
vector <plii> adj[N];
int d[N];
int bfs_uu_tien(int x){
    heapmin(plii) heap;
    heap.push({0,{0,x}});
    for (int i = 1; i <= n; i++) d[i] = 1e18;
    d[x] = 0;
    while (!heap.empty()){
        auto f = heap.top(); heap.pop();
        int u = f.se.se , t = f.se.fi;
        if (d[u] != f.fi) continue;
        for (auto p : adj[u]){
            int v = p.fi , c = p.se.fi , dc = p.se.se;
            int F = sqrt(dc) - 1;
            F = max(F,d[u]);
            int cost = d[u] + c + (F - d[u]) + dc / (F + 1);
            if (d[v] > cost){
                d[v] = cost;
                heap.push({d[v],{0,v}});
            }
        }
        for (auto p : adj[u]){
            int v = p.fi , c = p.se.fi , dc = p.se.se;
            int F = sqrt(dc) - 2;
            F = max(F,d[u]);
            int cost = d[u] + c + (F - d[u]) + dc / (F + 1);
            if (d[v] > cost){
                d[v] = cost;
                heap.push({d[v],{0,v}});
            }
        }
        for (auto p : adj[u]){
            int v = p.fi , c = p.se.fi , dc = p.se.se;
            int F = sqrt(dc);
            F = max(F,d[u]);
            int cost = d[u] + c + (F - d[u]) + dc / (F + 1);
            if (d[v] > cost){
                d[v] = cost;
                heap.push({d[v],{0,v}});
            }
        }
    }
    // for (int i = 1; i <= n; i++) cout << d[i] << " "; cout << "\n";
    return d[n];
}
int a[N];
void solve(){
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) d[a[i]] = i;
    set <int> s;
    for (int i = n; i >= 1; i--){
        auto F = s.lower_bound(-a[i]);
        s.insert(-a[i]);
        if (F == s.end()) continue;
        int c = d[- *F];
        // cout << a[i] << " " << a[c] << " ? \n";
        swap(a[i],a[c]);
        sort(a + i + 1,a + n + 1, greater<int>());
        break;
    }
    for (int i = 1; i <= n; i++) cout << a[i] <<  " ";
}
signed main()
{
    FASTIO;
    file("cccc");
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}

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
int dx[8] = {-1,-1,-1,0,1,1,1,0};
int dy[8] = {-1,0,1,1,1,0,-1,-1};
int n,q;
int par[N + 10][25];
vector<vector<int>> adj(N + 10,vector<int>(0));
int depth[N + 10];
bool vis[N];
void dfs(int u,int pos){
    vis[u] = 1;
    for(auto i : adj[u]){
        if(i != pos && vis[i] == 0){
            par[i][0] = u;
            depth[i] = depth[u] + 1;
            dfs(i,u);
        }
    }
}
int get_par(int u,int ra){
    int p = u;
    for(int i = 0 ; i < 24 ; i ++){
        if((1 << i) & ra){
            p = par[p][i];
        }
    }
    return p;
}
int lca(int u,int v){
    if(depth[u] > depth[v]) swap(u,v);
    v = get_par(v,depth[v] - depth[u]);
    if(u == v) return u;
    for(int i = 20 ; i >= 0 ; i --){
        if(par[u][i] != par[v][i]){
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}
void solve(){

    cin >> n >> q;
    for(int i = 1 ; i < n ; i ++){
        int u,v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(1,0);
    for(int i = 1 ; i <= 23 ; i ++){
        for(int j = 1 ; j <= n ; j ++){
            par[j][i] = par[par[j][i - 1]][i - 1];
        }
    }
    while(q --){
        int x,y,z;
        cin >> x >> y >> z;
        int u = lca(x,z);
        int v1 = lca(x,y);
        int v2 = lca(y,z);
        // cout << u << " " << v1 << " " << v2 << "\n";
        if ((v1 == y && depth[v1] >= depth[u])
            || ((v2 == y && depth[v2] >= depth[u]))) cout << "YES\n";
                else cout << "NO\n";
    }

}
signed main()
{
    FASTIO;
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}

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
vector <int> adj[N];
int low[N], num[N], joint[N], tail[N], depth[N];
int par[N][22];
int timeDFS = 0;
void calPar(){
    par[1][0] = 1;
    for (int j = 1; j <= 20; j++){
        for (int i = 1; i <= n; i++){
            par[i][j] = par[par[i][j - 1]][j - 1];
        }
    }
}
void dfs(int previous, int u){
    timeDFS++;
    int child = 0;
    num[u] = low[u] = timeDFS;
    for (auto v : adj[u]){
        if (v == previous) continue;
        if (!num[v]){
            child++;
            par[v][0] = u;
            depth[v] = depth[u] + 1;
            dfs(u,v);
            low[u] = min(low[u], low[v]);
            if (u == previous){
                if (child > 1) joint[u] = 1;
            }
            else if (low[v] >= num[u]) joint[u] = 1;
        }
        else low[u] = min(low[u], num[v]);
    }
    tail[u] = timeDFS;
}
bool check_insubtree(int a, int par){
    return num[par] <= num[a] && num[a] <= tail[par];
}
int findpar(int u, int p){
    for (int i = 20; i >= 0; i--)
        if (depth[par[u][i]] > depth[p]) u = par[u][i];
    return u;
}
bool checkquery1(int A, int B, int G1, int G2){
    if (num[G1] > num[G2]) swap(G1,G2);
    if (low[G2] != num[G2]) return true;
    if (check_insubtree(A,G2) && !check_insubtree(B,G2)) return false;
    if (check_insubtree(B,G2) && !check_insubtree(A,G2)) return false;
    return true;
}
bool checkquery2(int A, int B, int C){
    if (joint[C] == 0){
        return true;
    } else {
        int pa = 0 , pb = 0;
        if (check_insubtree(A,C)) pa = findpar(A,C);
        if (check_insubtree(B,C)) pb = findpar(B,C);
        if (!pa && !pb) return true;
        if (pa == pb) return true;
        if (pa == 0 && low[pb] < num[C]) return true;
        if (pb == 0 && low[pa] < num[C]) return true;
        if (pa && pb && low[pa] < num[C] && low[pb] < num[C]) return true;
        return false;
    }
}
int main()
{
    FASTIO;
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        int u , v; cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    depth[1] = 1;
    dfs(1,1);
    calPar();
    int q; cin >> q;
    while (q--){
        int ty; cin >> ty;
        if (ty == 1){
            int A,B,G1,G2;
            cin >> A >> B >> G1 >> G2;
            bool cc = checkquery1(A,B,G1,G2);
            if (cc) cout << "yes\n"; else cout << "no\n";
        }
        else{
            int A,B,C;
            cin >> A >> B >> C;
            bool cc = checkquery2(A,B,C);
            if (cc) cout << "yes\n"; else cout << "no\n";
        }
    }
    return 0;
}

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
const int N = 3e5 + 100;
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
const int lg = 18;
int n, a[N];
int f[N][lg+1] , g[N][lg+1];
int lg2[N];
void builtRMQ(){
    for (int i = 1; i <= n; i++){
        f[i][0] = a[i];
        g[i][0] = a[i];
    }
    for (int x = 1; x <= lg; x++){
        for (int i = 1; i + (1 << x) - 1 <= n; i++){
            f[i][x] = max(f[i][x-1],f[i+(1<<(x-1))][x-1]);
            g[i][x] = min(g[i][x-1],g[i+(1<<(x-1))][x-1]);
        }
    }
}
int getmax(int x, int y){
    if (x > y) return -1e9;
    int u = lg2[y - x + 1];
    return max(f[x][u], f[y - (1<<u)+1][u]);
}
int getmin(int x, int y){
    if (x > y) return 1e9;
    int u = lg2[y - x + 1];
    return min(g[x][u], g[y - (1<<u)+1][u]);
}
void solve(){
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    if (n == 1){
        cout << "0\n";
        return;
    }
    builtRMQ();
    int res = 1e18;
    for (int i = 1; i <= n; i++){
        int l = 1 , r = i, pos = -1;
        int sufmax = getmax(i+1,n) , sufmin = getmin(i+1,n);
        while (l <= r){
            int mid = (l + r) >> 1;
            int premax = getmax(1,mid-1) , premin = getmin(1,mid-1);
            int zmax = max(premax,sufmax) , zmin = min(premin,sufmin);
            int cmax = getmax(mid,i) , cmin = getmin(mid,i);
            if (zmax - zmin >= cmax - cmin){
                pos = mid;
                r = mid - 1;
            } else l = mid + 1;
        }
        if (pos != -1){
            int pmax = getmax(1,pos-1) , pmin = getmin(1,pos-1);
            int zmax = max(pmax,sufmax) , zmin = min(pmin,sufmin);
            res = min(res,zmax - zmin);
        }
    }
    for (int i = 1; i <= n; i++){
        int l = 1 , r = i, pos = -1;
        int sufmax = getmax(i+1,n) , sufmin = getmin(i+1,n);
        while (l <= r){
            int mid = (l + r) >> 1;
            int premax = getmax(1,mid-1) , premin = getmin(1,mid-1);
            int zmax = max(premax,sufmax) , zmin = min(premin,sufmin);
            int cmax = getmax(mid,i) , cmin = getmin(mid,i);
            if (zmax - zmin <= cmax - cmin){
                pos = mid;
                l = mid + 1;
            } else r = mid - 1;
        }
        if (pos != -1){
            int zmax = getmax(pos,i) , zmin = getmin(pos,i);
            res = min(res,zmax - zmin);
        }
    }
    cout << res << "\n";
}
signed main()
{
    FASTIO;
    for (int i = 1; i <= 2e5 + 100; i++) lg2[i] = __lg(i);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}

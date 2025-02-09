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
const int N = 1e6 + 100;
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
ll a[N], n , m , k;
ll getRes(ll x){
    int l = upper_bound(a + 1,a + 1 + n,x) - a - 1;
    int r = lower_bound(a + 1,a + 1 + n,x) - a - 1;
    ll u = 0 , v = m;
    if (l - k + 1 > 0) u = (x + a[l - k + 1]) / 2 + 1;
    if (r + k <= n){
        if ((a[r + k] + x) % 2 == 1) v = (a[r + k] + x) / 2;
        else v = (a[r + k] + x) / 2 - 1;
    }
    return max(0LL,v - u + 1);
}
void solve(){
    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(a + 1, a + 1 + n);
    ll res = 0 , pos = 0;
    for (int i = 1; i <= n; i++){
        for (ll p = max(0LL,a[i] - 2); p <= min(m,a[i] + 2); p++){
            ll z = getRes(p);
            if (z > res){
                res = z;
                pos = p;
            } else {
                if (z == res) pos = min(pos,p);
            }
        }
    }
    for (ll p = 0; p <= min(m,2LL); p++){
        ll z = getRes(p);
        if (z > res){
            res = z;
            pos = p;
        } else {
            if (z == res) pos = min(pos,p);
        }
    }
    for (ll p = max(0LL,m - 2); p <= m; p++){
        ll z = getRes(p);
        if (z > res){
            res = z;
            pos = p;
        } else {
            if (z == res) pos = min(pos,p);
        }
    }
    cout << res << " " << pos << "\n";
    return;
}
int main()
{
    FASTIO;
    int t = 1;
    while (t--){
        solve();
    }
    return 0;
}

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
const int LIM = 1e6 + 10; // N_Prime
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
int pr[LIM + 10] , lp[LIM + 10] , cnt = 0;
void sieve(int lim){
    for (int i = 2; i <= lim; i++){
        if (!lp[i]) lp[i] = pr[++cnt] = i;
        int j = 1;
        while (j <= cnt && pr[j] <= lp[i] && pr[j] * i <= lim){
            lp[pr[j] * i] = pr[j];
            j++;
        }
    }
}
ll mul(ll a, ll b, ll c){
    ll res = 0;
    if (a < b) swap(a,b);
    for (; b > 0; b >>= 1, a = (a + a) % c)
        if (b & 1) res = (res + a) % c;
    return res;
}
ll power_mul(ll a,ll b,ll c){
    ll res = 1;
    a = a % c;
    for (; b > 0; b >>= 1 , a = mul(a,a,c))
        if (b & 1) res = mul(res,a,c);
    return res;
}
ll prime_ar[9] = {2,3,5,7,11,13,17,19,23};
pll factor(ll x){
    ll p = 0;
    while ((x & 1) == 0){
        p++;
        x >>= 1;
    }
    return make_pair(p,x);
}
bool Test_prime(ll p, ll x, ll n, ll _prime){
    if (n == _prime) return true;
    ll c = power_mul(_prime,x,n);
    if (c == 1) return true;
    for (; p > 0; p--){
        if (c == n - 1) return true;
        c = mul(c,c,n);
    }
    return false;
}
bool Miller(ll n){
    if (n < 2) return false;
    if ((n & 1) == 0) return (n == 2);
    auto [p,x] = factor(n - 1);
    bool res = true;
    for (int i = 0; i < 9; i++){
        res = res & Test_prime(p,x,n,prime_ar[i]);
    }
    return res;
}
bool chinhphuong(ll x){
    if (x < 0) return false;
    ll u = sqrt(x);
    return u * u == x;
}
bool lapphuong(ll x){
    ll u = cbrt(x);
    if (u * u * u == x) return true;
    if ((u + 1) * (u + 1) * (u + 1) == x) return true;
    return false;
}
void solve(){
    int n;
    cin >> n;
    vector <int> v;
    for (int i = 1; i <= cnt; i++){
        if (pr[i] * pr[i] * pr[i] > n) break;
        int d = 0;
        while (n % pr[i] == 0){
            d++;
            n /= pr[i];
        }
        if (d > 0) v.push_back(d);
    }
    if (n > 1){
        if (Miller(n)) v.push_back(1);
        else if (chinhphuong(n)) v.push_back(2);
        else v.push_back(1) , v.push_back(1);
    }
    int res = 1;
    for (int i = 0; i < v.size(); i++) res *= (v[i] + 1);
    int ernot = 1 , c2 = 0;
    for (int i = 0; i < v.size(); i++){
        ernot *= ((v[i]/2) + 1);
        if (v[i]%2==0) c2++;
    }
    // cout << "res = " << res << "\n";
    // cout << "not = " << ernot << "\n";
    if (c2 != v.size()) cout << (res-2*ernot+1)/2 << "\n";
    else cout << (res-ernot+1)/2 << "\n";
}
signed main()
{
    FASTIO;
    sieve(1e6);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}

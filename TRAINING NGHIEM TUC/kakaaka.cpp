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
const int N = 2e6 + 100;
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
const ll modp = 998244353;
ll g[N], m;
ll C(ll n, ll k){
    if (n < k) return 0;
    return g[n] * power(g[k], modp-2, modp)%  modp * power(g[n-k], modp-2, modp) %  modp;
}
const ll base = 23;
int lp[LIM + 2],pr[LIM],cnt= 0;
int n;
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
int ds[N];
void solve(int n){
    // cin >> n;
    ll sum = 0;
    for (int i = 1; i <= n; i++) sum += pr[i] , ds[i] = 0;
    ll g = sum/2 + (sum%2);
    ll ss = 0;
    if (sum % 2 == 1){
        for (int i = n; i >= 1;){
            if (g >= pr[i]){
                g = g - pr[i];
                ds[i]=1;
                ss += pr[i];
                // i -= 2;
                i--;
            } else i--;
        }
    }
    else{
        //sum -= 5;
        ll g = sum/2 + (sum%2);
        for (int i = n; i >= 1;){
            if (g >= pr[i]){
                g = g - pr[i];
                ds[i]=1;
                ss += pr[i];
                // i -= 2;
                i--;
            } else i--;
        }
        ll ccc = abs(ss-(sum-ss));
        if (ccc == 2){
            for (int i = 1; i < n; i++){
                if (pr[i + 1] - pr[i] == 2 && ds[i] != ds[i + 1]){
                    ll u = ss;
                    if (ds[i] == 1) u += 2; else u -= 2;
                    if (abs(u-(sum-u)) == 4) swap(ds[i],ds[i+1]) , ss = u;
                }
            }
        }
        cout << abs(ss-(sum-ss)) << "\n";
        // for (int i = 1; i <= n; i++) if (ds[i]==0) cout << 'A'; else cout << 'B'; cout << "\n";
    }
    // cout << "\n" << ss << " " << sum-ss;

}
signed main()
{
    sieve(1e7);
    //cout << "cnt = " << cnt << "\n";
    FASTIO;
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++){
        solve(i);
    }
    return 0;
}

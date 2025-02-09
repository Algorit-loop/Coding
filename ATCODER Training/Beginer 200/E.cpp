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

#define ll __int128
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
ll C(ll n, ll k){
    if (n < k) return 0;
    ll res = 1;
    for (ll i = 0; i < k; i++){
        res = res * (n - i);
        res = res / (i + 1);
    }
    return res;
}
ll get(ll s, ll n){
    ll u = C(s - 3 + 3,3);
    ll u1 = C(s - n - 2 + 3,3);
    ll u2 = C(s - 2*n - 1 + 3,3);
    ll u3 = C(s - 3*n + 3,3);
    return u - (3*u1 - 3*u2 + u3);
}
int brute(ll s, ll n){
    int d = 0;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            for (int k = 1; k <= n; k++){
                if (i + j + k <= s) d++;
            }
        }
    }
    return d;
}
int brute2(ll s, ll n){
    int d = 0;
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            if (i + j == s) d++;
        }
    }
    return d;
}
ll getequal(ll s, ll n){
    ll u = C(s - 2 + 1,1);
    ll v = C(s - n - 1 + 1,1);
    ll uu = C(s - 2*n + 1,1);
    return u - 2*v + uu;
}
int main()
{
    FASTIO;
    long long n,k; cin >> n >> k;
    // cout << get(124,61) << " " << brute(124,60);
    // cout << getequal(1234,801) << " " << brute2(1234,800) << "\n";
    ll l = 1, r = 3*n, ps = -1;
    while (l <= r){
        ll mid = (l + r) >> 1;
        if (get(mid, n + 1) < k){
            l = mid + 1;
            ps = mid;
        } else r = mid - 1;
    }
    // cout << "ps = " << ps << "\n";
    assert(ps > -1);
    k = k - get(ps,n+1);
    ps++;
    ll ps2 = -1;
    int r1 = -1, r2 = -1, r3 = -1;
    for (int i = 1; i <= n; i++){
        if (k > getequal(ps - i,n + 1)){
            k = k - getequal(ps - i, n + 1);
        } else {
            ps2 = ps - i;
            r1 = i;
            break;
        }
    }
    for (int i = 1; i <= n; i++){
        if (k > 0 && ps2 - i <= n && ps2 - i >= 1){
            k -= 1;
            if (k == 0){
                r2 = i;
                r3 = ps2 - i;
                break;
            }
        }
    }
    cout << r1 << " " << r2 << " " << r3;
    return 0;
}

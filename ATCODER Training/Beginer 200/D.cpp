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
int n;
const int w = 200;
//vector<int> trace(int q,const vector<vector<int>> &dp, int state, const vector<int> &a){
//    vector <int> r1;
//    int z = q;
//    for (int i = n; i >= 1; i--){
//        int u = ((z - a[i]) % w + w) % w;
//        if (dp[i - 1][u] == 1){
//            if (state == 0) r1.pb(i); else r1.pb(n-i+1);
//            z = u;
//        }
//    }
//    return r1;
//}
bool solve(const vector<int> &a, int t){
    vector <vector<int>> dp(210,vector<int>(200,0));
    auto pd = dp;
    vector <int> f(w,0);
    f[0] = -1;
    dp[0] = f;
    int rr = -1, pos = -1;
    for (int i = 1; i <= n; i++){
        auto g = f;
        for (int x = 0; x < w; x++){
            if (f[x] != 0){
                g[(x + a[i]) % w] = i;
                if (f[(x + a[i]) % w] > 0) rr = (x + a[i]) % w;
            }
        }
        f = g;
        dp[i] = f;
        if (rr != -1){
            pos = i;
            break;
        }
    }
    if (rr == -1) return false;
    vector <int> r1;
    int z = rr;
    for (int i = pos; i >= 1; i--){
        int u = ((z - a[i]) % w + w) % w;
        if (dp[i - 1][u] != 0){
            if (t == 0) r1.pb(i); else r1.pb(n - i + 1);
            z = u;
        }
    }
    vector <int> r2;
    z = rr;
    for (int i = pos-1; i >= 1; i--){
        int u = ((z - a[i]) % w + w) % w;
        if (dp[i - 1][u] != 0){
            if (t == 0) r2.pb(i); else r2.pb(n - i + 1);
            z = u;
        }
    }
    sort(all(r1)); sort(all(r2));
    assert(r1 != r2);
    cout << "Yes\n";
    cout << r1.size() << " "; for (auto x : r1) cout << x <<  " "; cout << "\n";
    cout << r2.size() << " "; for (auto x : r2) cout << x <<  " "; cout << "\n";
    return true;
}
int main()
{
    FASTIO;
    cin >> n;
    vector<int> a(n+1), b(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i], b[n - i + 1] = a[i];
    // find set B
    bool u = solve(a,0);
    if (u == true) return 0;
    reverse(a.begin()+1,a.end());
    u = solve(a,1);
    if (u == true) return 0;
    cout << "No\n";
    return 0;
}

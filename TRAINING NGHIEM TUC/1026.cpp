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
int a[N], b[N];
int n , m;
int dp[N] , sl[N];

void solve(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];
    int k = 1;
    for (int i = 1; i <= n; i++) dp[i] = 1e18;
    dp[0] = 0;
    sl[0] = 1;
    for (int i = 1; i <= m; i++){
        int e = 1 , s = 0;
        set <ii> st;
        st.insert({dp[0],sl[0]});
        st.insert({1e18,100});
        map <int,int> dem;
        dem[dp[0]]++;
        for (int j = 1; j <= n; j++){
            s += a[j];
            while (s > b[i] && e <= j){
                s -= a[e];
                assert(!st.empty());
                auto f = st.lower_bound({dp[e-1],-1e9});
                auto g = *f; st.erase(f);
                assert(g.fi == dp[e-1]);
                g.se = (g.se - sl[e-1] + mod * mod) % mod;
                dem[dp[e-1]]--;
                if (dem[dp[e-1]] > 0) st.insert(g);
                e++;
            }
            if (!st.empty()){
                auto g = st.begin();
                auto f = *g;
                if (f.fi + m - i < dp[j]){
                    dp[j] = f.fi + m - i;
                    sl[j] = f.se;
                }
                else if (f.fi + m - i == dp[j]){
                    sl[j] = (sl[j] + f.se) % mod;
                }
            }
            // insert j
            dem[dp[j]]++;
            if (!st.empty()){
                auto f = st.lower_bound({dp[j],-1e9});
                auto g = *f;
                if (g.fi == dp[j]){
                    g.se = (g.se + sl[j]) % mod;
                    st.erase(f);
                    st.insert(g);
                } else st.insert({dp[j],sl[j]});
            } else st.insert({dp[j],sl[j]});
        }
    }
    // for (int i = 1; i <= n; i++) cout << dp[i] << " "; cout << "\n";
    if (dp[n] >= 1e16) cout << "-1\n";
    else cout << dp[n] << " " << sl[n] << "\n";
}
signed main()
{
     FASTIO;
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}

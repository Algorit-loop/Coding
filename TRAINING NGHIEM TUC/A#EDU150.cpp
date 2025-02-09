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
int n , a[N], d[8], ct[N], gmax[N];
string s;
int v[6][8];
ll suf[N];
void solve(){
    cin >> s;
    n = s.size();
    s = "!" + s;
    suf[n + 1] = 0;
    int u = 0;
    ll ans = -1e18;
    for (int i = 1; i <= n + 1; i++) ct[i] = 0, gmax[i] = 0;
    for (int j = 0; j <= 4; j++) d[j] = v[0][j] = v[1][j] = 0;
    for (int i = n; i >= 1; i--){
        if (u > s[i] - 'A') suf[i] = - (ll)pow(10,s[i] - 'A') + suf[i + 1];
        else suf[i] = (ll)pow(10,s[i] - 'A') + suf[i + 1];
        u = max(u, s[i] - 'A');
        gmax[i] = u;
        d[s[i] - 'A']++;
        int r = 0;
        for (int j = s[i] - 'A' + 1; j <= 4; j++){
            r = r + d[j];
        }
        ct[i] = r;
    }
    // for (int i = 1; i <= n; i++) cout << suf[i] << " "; cout << "\n";
    //cout << "suf = " << suf[1] << "\n";
    for (int i = 1; i <= n; i++){
        for (int j = 0; j <= 4; j++){
            ll res = suf[i + 1] + (suf[1] - suf[i]);

            ll np1 = 0;
            if (j < s[i] - 'A'){
                for (int r = j; r < s[i] - 'A'; r++){
                    np1 = np1 + v[1][r] * (ll)pow(10,r);
                }
            }
            ll np2 = 0;
            if (j > s[i] - 'A'){
                for (int r = s[i] - 'A'; r < j; r++){
                    np2 = np2 + v[0][r] * (ll)pow(10,r);
                }
            }

            res = res + 2*np1 - 2*np2;

            if (gmax[i + 1] > j) res = res - (ll)pow(10,j);
            else res = res + (ll)pow(10,j);

            ans = max(ans,res);
            // cout << i << " " << j << " " << np1 << " " << np2 << " " << res << "\n";
        }
        if (ct[i] == 0) v[0][s[i] - 'A']++;
        if (ct[i] == 1) v[1][s[i] - 'A']++;
    }
    cout << max(ans,suf[1]) << "\n";
    return;
}
int main()
{
    FASTIO;
    int t = 1; cin >> t;
    while (t--){
        solve();
    }
    return 0;
}

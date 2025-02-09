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
ll n , f[N], a[N], fp[N];
ll pre[N], suf[N];
ll dp[2004][2004];
void cachdp(){
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= n; j++){
            dp[i][j] = -1e18;
        }
    }
    for (int i = 0; i <= n; i++) dp[i][0] = 0;
    for (int i = 1; i <= n; i++) dp[i][1] = max(dp[i - 1][1], 1LL * a[i]);
    for (int k = 2; k <= n / 2; k++){
        for (int i = 2; i <= n; i++){
            dp[i][k] = max(dp[i - 2][k - 1] + a[i],dp[i][k]);
            dp[i][k] = max(dp[i][k], dp[i - 1][k]);
        }
    }
    cout << dp[n][n / 2] << "\n";
    return;
}
ll k;
string s;
void solve(){
    cin >> k;
    cin >> s;
    vector <char> vc;
    vector <long long> vs;

    ll d = 0;
    s = s + 'a';
    for (int i = 0; i < s.size(); i++){
        if (s[i] >= 'a' && s[i] <= 'z'){
            vc.push_back(s[i]);
            if (d != 0) vs.push_back(d);
            d = 0;
        } else {
            d = d * 10 + (s[i] - 48);
        }
    }
    vc.pop_back();

    vector <char> vc2 = vc;
    vector <ll> vs2 = vs;
    ll k2 = k;
    /*while (k > 0){
        ll ss = 0;
        for (int i = 0; i < vs.size(); i++) ss = vs[i]
        if (ss == 0) break;*/
        for (int i = 0; i < vc.size() - 1; i++){
            if (i < 0) continue;
            if (vc[i] < vc[i + 1]){
                ll p = min(vs[i], k);
                k -= p;
                vs[i] -= p;
                if (vs[i] == 0){
                    vc.erase(vc.begin() + i);
                    vs.erase(vs.begin() + i);
                    i = max(i - 2,-1);
                }
                // break;
            }
        }
    //}
    for (int i = vs.size() - 1; i >= 0; i--){
        ll p = min(vs[i], k);
        k -= p;
        vs[i] -= p;
    }
    /*while (k2 > 0){
        ll ss = 0;
        for (int i = 0; i < vs2.size(); i++) ss = vs2[i];
        if (ss == 0) break;*/
        for (int i = 0; i < vc2.size() - 1; i++){
            if (i < 0) continue;
            if (vc2[i] > vc2[i + 1]){
                ll p = min(vs2[i], k2);
                k2 -= p;
                vs2[i] -= p;
                if (vs2[i] == 0){
                    vc2.erase(vc2.begin() + i);
                    vs2.erase(vs2.begin() + i);
                    i = max(i - 2,-1);
                }
                //break;
            }
        }
    //}
    for (int i = vs2.size() - 1; i >= 0; i--){
        ll p = min(vs2[i], k2);
        k2 -= p;
        vs2[i] -= p;
    }
    vector <char> gminc , gmaxc;
    vector <ll> gmins , gmaxs;
    for (int i = 0; i < vc.size(); i++){
        if (gmaxc.size() == 0 && vs[i] > 0){
            gmaxc.push_back(vc[i]);
            gmaxs.push_back(vs[i]);
            continue;
        }
        if (vc[i] == gmaxc.back()) gmaxs[gmaxs.size() - 1] += vs[i];
        else if (vs[i] > 0){
            gmaxc.push_back(vc[i]);
            gmaxs.push_back(vs[i]);
        }
    }
    for (int i = 0; i < gmaxc.size(); i++) cout << gmaxc[i] << gmaxs[i]; cout << "\n";
    //for (int i = 0; i < vc2.size(); i++) cout << vc2[i] << " " << vs2[i] << "\n";
    for (int i = 0; i < vc2.size(); i++){
        if (gminc.size() == 0 && vs2[i] > 0){
            gminc.push_back(vc2[i]);
            gmins.push_back(vs2[i]);
            continue;
        }
        if (vc2[i] == gminc.back()) gmins[gmins.size() - 1] += vs2[i];
        else if (vs2[i] > 0){
            gminc.push_back(vc2[i]);
            gmins.push_back(vs2[i]);
        }
    }
    for (int i = 0; i < gminc.size(); i++) cout << gminc[i] << gmins[i];
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

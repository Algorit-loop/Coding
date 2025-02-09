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
int er = 0;
void query(int x, int y, int u, int v){
    if (x == u && y == v) assert(0);
    cout << "query " << x << " " << y << " " << u << " " << v << "\n";
    er++;
    if (er >= 1000) assert(0);
}
int main()
{
    // FASTIO;
    int limit = 1e5;
    int l = 90 , r = limit - 90;
    // cout << fixed << setprecision(7);
    while ((r-l) >= 100){
        int kc = (r-l)/3;
        int mid1 = l + kc , mid2 = r - kc;
        query(mid1,0,mid1,limit);
        double getmid1; cin >> getmid1;
        query(mid2,0,mid2,limit);
        double getmid2; cin >> getmid2;
        if (getmid1 < getmid2){
            l = mid1;
        } else r = mid2;
    }
    int x = 0;
    double dx = 0;
    for (int i = l; i <= r; i++){
        query(i,0,i,limit);
        double di; cin >> di;
        if (di > dx){
            x = i;
            dx = di;
        }
    }
    int p = 0, q = 1e5;
    while (p <= q){
        int mid = (p + q) / 2;
        query(0,0,limit,mid);
        double c; cin >> c;
        if (c
    }
    l = 90; r = limit-90;
    while ((r-l) >= 100){
        int kc = (r-l)/3;
        int mid1 = l + kc , mid2 = r - kc;
        query(0,mid1,limit,mid1);
        double getmid1; cin >> getmid1;
        query(0,mid2,limit,mid2);
        double getmid2; cin >> getmid2;
        if (getmid1 < getmid2){
            l = mid1;
        } else r = mid2;
    }
    int y = 0;
    double dy = 0;
    for (int i = l; i <= r; i++){
        query(0,i,limit,i);
        double di; cin >> di;
        if (di > dy){
            y = i;
            dy = di;
        }
    }

    cout << "answer " << x << " " << y << " " << (ll)(dx+1)/2;
    /*double d; cin >> d;
    y += d / 2;
    cout << "answer " << x << " " << y << " " << d/2 << "\n";*/
    return 0;
}

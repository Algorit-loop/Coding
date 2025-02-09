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
ll suma1 = 0 , sumb1 = 0;
ll suma2 = 0 , sumb2 = 0;
vector <pll> v1, v2;
int cnt1 = 0 , cnt2 = 0;
ll a[100] , b[100], n, D;
void xay(int x){
    for (int i = 1; i <= 3; i++){
        if (i == 1){
            suma1 += a[x];
            sumb1 += b[x];
        }
        if (i == 2){
            suma2 += a[x];
            sumb2 += b[x];
        }
        if (x < n / 2){
            xay(x + 1);
        }
        if (x == n / 2){
//            cnt1++;
//            v1[cnt1] = {suma1 - suma2, sumb1 - sumb2};
            v1.pb({suma1 - suma2, sumb1 - sumb2});
        }
        if (i == 1){
            suma1 -= a[x];
            sumb1 -= b[x];
        }
        if (i == 2){
            suma2 -= a[x];
            sumb2 -= b[x];
        }
    }
}

void xay2(int x){
    for (int i = 1; i <= 3; i++){
        if (i == 1){
            suma1 += a[x];
            sumb1 += b[x];
        }
        if (i == 2){
            suma2 += a[x];
            sumb2 += b[x];
        }
        if (x < n){
            xay2(x + 1);
        }
        if (x == n){
//            cnt2++;
//            v2[cnt2] = {suma1 - suma2, sumb1 - sumb2};
            v2.pb({suma1 - suma2, sumb1 - sumb2});
        }
        if (i == 1){
            suma1 -= a[x];
            sumb1 -= b[x];
        }
        if (i == 2){
            suma2 -= a[x];
            sumb2 -= b[x];
        }
    }
}
int main()
{
    FASTIO;
    /*cin >> n >> D;
    for (int i = 1; i <= n; i++) cin >> a[i] >> b[i];
    if (n >= 20){
        cout << "adsamaisjlilas\n";
        return 0;
    }*/
    n = 30;
    D = range(0,1e10);
    for (int i = 1; i <= n; i++) a[i] = range(1,1e10) , b[i] = range(1,1e10);
    v1.pb({-1e18,-1e18});
    v2.pb({1e18,1e18});
    xay(1);
    suma1 = 0;
    suma2 = 0;
    sumb1 = 0;
    sumb2 = 0;
    xay2(n / 2 + 1);
    cnt1 = v1.size() - 1;
    cnt2 = v2.size() - 1;
    // sort(v1 + 1, v1 + cnt1 + 1);
    // sort(v2 + 1, v2 + cnt2 + 1, greater <pll> ());
    sort(all(v1));
    sort(all(v2),greater<pll>());
//    for (int i = 1; i <= cnt1; i++) cout << v1[i].fi << " "; cout << "\n";
//    for (int i = 1; i <= cnt1; i++) cout << v1[i].se << " "; cout << "\n";
//    for (int i = 1; i <= cnt2; i++) cout << v2[i].fi << " "; cout << "\n";
//    for (int i = 1; i <= cnt2; i++) cout << v2[i].se << " "; cout << "\n";
    multiset <ll> s;
    int j1 = 1, j2 = 1;
    ll ans = 0;
    for (int i = 1; i <= cnt2; i++){
        while (j2 <= cnt1 && v2[i].fi + v1[j2].fi <= D){
            s.insert(v1[j2].se);
            j2++;
        }
        while (j1 < j2 && v2[i].fi + v1[j1].fi < -D){
            auto it = s.find(v1[j1].se);
            if (it != s.end()) s.erase(s.find(v1[j1].se));
            j1++;
        }
        if (!s.empty()){
            ll u1 = *s.begin() , u2 = *s.rbegin();
            ans = max(ans,max(abs(v2[i].se + u1) , abs(v2[i].se + u2)));
        }
    }
    cout << ans;
    return 0;
}

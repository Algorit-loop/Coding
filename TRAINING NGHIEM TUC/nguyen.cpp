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
const int N = 5e5 + 100;
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
int choose[N], a[N], da = 0;
vector <vector<int>> res;
// quaylui(x,n) -> tương ứng với chọn giá trị cho ô thứ x
int e[101];
void check(int n){
//    for (int i = 1; i < n; i++){
//        if (e[a[i] + a[i + 1]] == 1) return;
//    }
    if (e[a[1] + a[n]] == 1) return;
    da++;
    vector <int> u;
    for (int i = 1; i <= n; i++) u.push_back(a[i]);
    if (da <= 10000) res.push_back(u);
}
void sieve(int lim){
    // e[i] = 0 voi moi i
    e[1] = 1;
    for (int i = 2; i * i <= lim; i++){
        if (e[i] == 0){
            for (int j = i * i; j <= lim; j += i)
                e[j] = 1;
        }
    }
}
void quaylui(int x, int n){
    for (int i = 2; i <= n; i++)
        if (choose[i] == 0){
            // kiem tra i da duoc chon hay chua ?
            a[x] = i;
            choose[i] = 1;
            if (x < n && e[a[x] + a[x - 1]] == 0) quaylui(x + 1,n);
            if (x == n && e[a[x] + a[x - 1]] == 0){
                check(n);
            }
            choose[i] = 0; // why ?
            // code
        }
}
int n , m;
void solve(){
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector <int> v;
    for (int i = 1; i <= n; i++){
        if (a[i] == 0) continue;
        if (a[i] == 1){
            v.push_back(a[i]);
            continue;
        }
        int x = a[i];
        if (x % 2 == 0){
            while (x % 2 == 0) x /= 2;
            if (x == 1) v.push_back(a[i]);
        } else
        if (x % 3 == 0){
            while (x % 3 == 0) x /= 3;
            if (x == 1) v.push_back(a[i]);
        }
        else
        if (x % 5 == 0){
            while (x % 5 == 0) x /= 5;
            if (x == 1) v.push_back(a[i]);
        }
    }
    // trong V la nhung thang ly tuong
    sort(v.begin(),v.end());
    for (int i = 1; i <= m; i++){
        int l , r;
        cin >> l >> r;
        // 1 2 3 4 5 6 7 8 9 10
        // tim <= 7
        // di tim > 7 sau do em lay chi so - 1
        int ux = lower_bound(v.begin(),v.end(),l) - v.begin(); // >= l
        int vx = upper_bound(v.begin(),v.end(),r) - v.begin() - 1;
        cout << vx - ux + 1 << "\n";
    }
    return;
}
signed main()
{
    FASTIO;
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}

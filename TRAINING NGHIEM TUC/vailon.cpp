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
int a[N], n, x, mps[2*N],m,q,b[N];
int tr[4*N];
void update(int k, int l, int r, int pos, int val){
    if (l == r){
        tr[k] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(k<<1,l,mid,pos,val);
    else update(k<<1|1,mid+1,r,pos,val);
    tr[k] = max(tr[k<<1],tr[k<<1|1]);
}
int query(int k, int l, int r, int u, int v){
    if (l > v || r < u) return 0;
    if (l >= u && r <= v) return tr[k];
    int mid = (l + r) >> 1;
    return max(query(k<<1,l,mid,u,v) , query(k<<1|1,mid+1,r,u,v));
}
void solve(){
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= m; i++) cin >> b[i];
    vector <int> gg(n+10,0) , v;
    auto pos = gg;
    for (int i = 0; i <= n; i++) pos[i] = -1;
    for (int i = 1; i <= n; i++){
        if (gg[a[i]] == 0){
            gg[a[i]] = 1;
            v.pb(a[i]);
            pos[a[i]] = v.size()-1;
        }
    }
    for (int i = 0; i < v.size(); i++) cout << v[i] << " "; cout << "\n";
    for (int i = 0; i < v.size(); i++) cout << pos[v[i]] << " "; cout << "\n";
    set <int> ss[n + 2];
    for (int i = 1; i <= n; i++) ss[i].insert(1e9);
    for (int i = 1; i <= m; i++){
        ss[b[i]].insert(i);
    }
    for (int i = 1; i <= 4*n; i++) tr[i] = 0;
    for (int i = 0; i < v.size(); i++){
        cout << *(ss[v[i]].begin()) << " ";
        update(1,0,v.size(),i,*(ss[v[i]].begin()));
    }
    cout << "\n";
    int ok = 0;
    vector <int> status(m + 10,0);
    for (int i = 1; i <= m; i++){
        int u = pos[b[i]];
        cout << u << "\n";
        if (u == -1) continue;
        if (u == 0){
            ok++;
            status[i] = 1;
            continue;
        }
        int rr = query(1,0,v.size(),0,u - 1);
        cout << rr << " ? " << i << "\n";

        if (rr < i) ok++ , status[i] = 1;
    }
    if (ok == m) cout << "YA\n"; else cout << "TIDAK\n";
    while (q--){
        int x,y; cin >> x >> y;
        ok -= status[x];
        ss[b[x]].erase(x);
        b[x] = y;
        ss[b[x]].insert(x);
        if (pos[b[x]] == -1) status[x] = 0;
        else{
            int u = pos[b[x]];
            update(1,0,v.size(),u,*(ss[v[u]]).begin());
            if (u == 0) status[x] = 1;
            else status[x] = (query(1,0,v.size(),0,u-1) < x);
        }
        ok += status[x];
        if (ok == m) cout << "YA\n"; else cout << "TIDAK\n";
    }
}
signed main()
{
    FASTIO;
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}

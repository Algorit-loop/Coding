#include <bits/stdc++.h>
#include <random>
#include <time.h>
#define int long long 
#define ll long long 
#define fi first 
#define se second
#define ii pair<int,int>
using namespace std;
void file(string f){
    if (fopen((f + ".INP").c_str(),"r")){
        freopen((f + ".INP").c_str(),"r",stdin);
        freopen((f + ".OUT").c_str(),"w",stdout);
    }
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}
const int mod = 1e9 + 7;
const int N = 2e5 + 10;
ll power(ll a, ll b, ll c){
    ll res = 1;
    a = a % c;
    for (; b > 0; b >>= 1 , a = a * a % c){
        if (b & 1) res = res * a % c;
    }
    return res;
}
struct node{
    int L, V, pos;
};
int n, m;
node a[N];
int dp[N];
bool cmp(const node &u, const node &v){
    return u.L < v.L;
}
struct segtree{
    vector <int> st;
    segtree(int n){
        st.assign(4 * n, 1e18);
    }
    void update(int k, int l, int r, int pos, int val){
        if (l == r && r == pos){
            st[k] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(k << 1,l,mid,pos,val);
        else update(k<<1|1,mid+1,r,pos,val);
        st[k] = min(st[k<<1],st[k<<1|1]);
    }
    int query(int k, int l, int r, int u, int v){
        if (l > v || r < u) return 1e18;
        if (l >= u && r <= v) return st[k];
        int mid = (l + r) >> 1;
        return min(query(k<<1,l,mid,u,v), query(k<<1|1,mid+1,r,u,v));
    }
    void update(int pos, int val){
        update(1,1,n,pos,val);
    }
    int query(int u, int v){
        return query(1,1,n,u,v);
    }
};
vector <int> ad[N];
bool ok[N];
void solve(){
    clock_t st = clock();
    // n = 100000;
    // m = 100;
    // int cs = 1000;
    // for (int i = 1; i <= n; i++){
    //     a[i].L = ((i - 1) / cs + 1);
    //     a[i].V = range(1,1000);
    //     a[i].pos = i;
    // }
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i].L;
    for (int i = 1; i <= n; i++) cin >> a[i].V , a[i].pos = i;
    sort(a + 1,a + 1 + n,cmp);
    segtree f1(n) , f2(n);
    int res = 1e18;
    for (int i = 1; i <= n; i++){
        ad[a[i].L].push_back(i);
        dp[i] = 1e18;
        if (a[i].L == 1){
            dp[i] = a[i].V;
            if (a[i].L == m) res = min(res, dp[i]);
            continue;
        }
        if (ok[a[i].L - 2] == true){
            int x = a[i].L - 2;
            for (int j = 0; j < ad[x].size(); j++){
                f1.update(a[ad[x][j]].pos, 1e18);
                f2.update(a[ad[x][j]].pos, 1e18);
            }
            ok[x] = false;
        }
        if (ok[a[i].L - 1] == false){
            int x = a[i].L - 1;
            for (int j = 0; j < ad[x].size(); j++){
                f1.update(a[ad[x][j]].pos, dp[ad[x][j]] - a[ad[x][j]].pos);
                f2.update(a[ad[x][j]].pos, dp[ad[x][j]] + a[ad[x][j]].pos);
            }
            ok[x] = true;
        }
        dp[i] = min(f1.query(1,a[i].pos) + a[i].pos, f2.query(a[i].pos,n) - a[i].pos) + a[i].V;
        if (a[i].L == m) res = min(res, dp[i]);
    }
    cout << res << "\n";
    clock_t en = clock();
    // cout << "Time: " << (double)(en-st)/CLOCKS_PER_SEC;
    return;
}
signed main(){
    srand(time(NULL));
    ios::sync_with_stdio(false); cin.tie(NULL);
    file("txt");    
    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; _++){
        solve();
    }
    return 0;
}
    
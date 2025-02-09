#include <bits/stdc++.h>
#include <random>
#include <time.h>
#define int long long
#define ll long long 
#define fi first 
#define se second
#define ii pair<int,int>
using namespace std;
void __file(){
    if (fopen("input.txt","r")){
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    }
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}
const int N = 1e5 + 100;
const int mod = 1e9 + 7;
int dist(ii a, ii b){
    int f = (a.fi - b.fi); f = f * f;
    int g = (a.se - b.se); g = g * g;
    return f + g;
}

bool cphuong(ll x){
    int u = sqrt(x);
    return u * u == x;
}
int power(int a, int b, int c){
    int res = 1;
    a = a % c;
    for (; b > 0; b >>= 1 , a = a * a % c){
        if (b & 1) res = res * a % c;
    }
    return res;
}
bool check(int x){
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++){
        int d = 0;
        while (x % i == 0) d++ , x /= i;
        if (d > 1) return false;
    }
    return true;
}
int n , k , a[N];
int d[N];
int kq[N] , pos[N], choose[N];
struct BIT_TREE{
    int n = 0;
    vector <int> bit;
    BIT_TREE (int x){
        n = x;
        bit.assign(x + 10,0);
    }
    void update(int x, int val){
        for (; x > 0; x -= x&(-x)){
            bit[x] += val;
        }
    }
    int get(int x){
        if (x <= 0) return 0;
        int res = 0;
        for (; x <= n; x += x&(-x))
            res += bit[x];
        return res;
    }
};
struct SegTree{
    int n = 0;
    vector <pair<int,int>> st;
    SegTree (int x){
        n = x;
        st.assign(4*n + 1,{1e9,1e9});
    }
    void update(int k, int l, int r, int pos, pair<int,int> val){
        if (l == r && l == pos){
            st[k] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(k<<1,l,mid,pos,val);
        else update(k<<1|1,mid+1,r,pos,val);
        st[k] = min(st[k<<1],st[k<<1|1]);
    }
    void update(int pos, pair<int,int> val){
        update(1,1,n,pos,val);
    }
    pair<int,int> query(int k, int l, int r, int u, int v){
        if (l > v || r < u) return {1e9,1e9};
        if (l >= u && r <= v) return st[k];
        int mid = (l + r) >> 1;
        return min(query(k<<1,l,mid,u,v) , query(k<<1|1,mid+1,r,u,v));
    }
    pair<int,int> query(int u, int v){
        return query(1,1,n,u,v);
    }
};
vector <int> adj[N];
void solve(){
    cin >> n >> k;
    for (int i = 1; i <= k; i++) adj[i].clear();
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        pos[i] = 0;
        d[i] = 0;
        adj[a[i]].push_back(i);
    }
    for (int i = n; i >= 1; i--){
        if (pos[a[i]] == 0) pos[a[i]] = i , d[i] = 1;
    }
    BIT_TREE bt(n);
    SegTree st(n);
    // cout << "bt.n = " << bt.n << "\n";
    // cout << "st.n = " << st.n << "\n";
    for (int i = 1; i <= n; i++) bt.update(i,d[i]);
    // for (int i = 1; i <= n; i++) cout << bt.bit[i] << " "; cout << "\n";
    for (int i = 1; i <= n; i++) st.update(i,{a[i],i});
    
    // for (int i = 1; i <= n; i++) cout << bt.get(i) << " "; cout << "\n";
    int moc = 0;
    for (int z = k; z >= 1; z--){
        int l = 1 , r = n;
        int vt = -1;
        while (l <= r){
            int mid = (l + r) >> 1;
            if (bt.get(mid) == z){
                vt = mid;
                l = mid + 1;
            } else r = mid - 1;
        }
        assert(vt != -1);
        auto f = st.query(1,vt);
        kq[z] = f.first;
        for (int i = moc + 1; i <= f.second; i++) st.update(i,{1e9,1e9});
        moc = f.second;
        int x = kq[z];
        bt.update(pos[x],-1);
        for (auto w : adj[x]){
            st.update(w,{1e9,1e9});
        }
    }
    for (int i = k; i >= 1; i--) cout << kq[i] << " "; cout << "\n";

}
signed main(){
    srand(time(NULL));
    ios::sync_with_stdio(false); cin.tie(NULL);
    __file();       
    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; _++) solve();
    return 0;
}
    // int n = 1000000;
    // int ok = 0;
    // for (int T = 1; T <= n; T++){
    //     for (int i = 1; i <= 3; i++) d[i] = 0;
    //     // int x = rand() % 3 + 1;
    //     // vector <int> v;
    //     // d[x] = 1;
    //     // int choose = rand() % 3 + 1;
    //     // for (int i = 1; i <= 3; i++){
    //     //     if (d[i] == 0 && i != choose) v.push_back(i);
    //     // }
    //     // int open = v[rand() % (int)v.size()];
    //     // // cout << v.size() << "\n";
    //     // for (int i = 1; i <= 3; i++){
    //     //     if (i != choose && i != open) choose = i;
    //     // }
    //     // if (d[choose] == 1) ok++;
    //     int x = rand() % 3 + 1;
    //     d[x] = 1;
    //     int choose = rand() % 3 + 1;
    //     if (d[choose] == 0) ok++;
    // }
    // cout << ok << " / " << n << "\n";
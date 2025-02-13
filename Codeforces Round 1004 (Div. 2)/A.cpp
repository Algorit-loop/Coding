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

struct segtree{
    int n;
    vector <int> st;
    segtree(int Nsize){
        n = Nsize;
        st.assign(4 * Nsize, 1e18);
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

int n , a[N], f[N];
bool check(int x){
    while (x > 0){
        if (x % 10 == 7) return true;
        x /= 10;
    }
    return false;
}
vector <int> v;
void solve(){
    cin >> n;
    queue <ii> q;
    q.push({n,0});
    int res = 7;
    bitset <1000000001> bs;
    while (!q.empty()){
        auto f = q.front(); q.pop();
        bs[f.first] = true;
        if (check(f.first)){
            res = f.second;
            break;
        }
        if (f.second >= 6 || f.first > 1e9) continue;
        for (int i = 0; i < v.size(); i++){
            ii c = make_pair(f.first + v[i], f.second + 1);
            if (c.first < 1e9 && bs[c.first] == false){
                // cout << c.first << " " << c.second << "\n";
                q.push(c);
            }
        }
    }
    // cout << q.size() << "size <\n";
    cout << res << "\n";
    return;
}
signed main(){
    srand(time(NULL));
    ios::sync_with_stdio(false); cin.tie(NULL);
    file("txt");    
    int r = 0;
    for (int i = 1; i <= 9; i++){
        r = r * 10 + 9;
        v.push_back(r);
    }
    // for (auto x : v) cout << x << "\n";
    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; _++){
        solve();
    }
    return 0;
}
    
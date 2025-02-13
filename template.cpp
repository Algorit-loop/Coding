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


void solve(){
    
    return;
}
signed main(){
    srand(time(NULL));
    ios::sync_with_stdio(false); cin.tie(NULL);
    file("txt");    
    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; _++){
        solve();
    }
    return 0;
}
    
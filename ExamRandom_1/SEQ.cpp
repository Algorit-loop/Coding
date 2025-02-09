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
int n , f[N];
ll power(ll a, ll b, ll c){
    ll res = 1;
    a = a % c;
    for (; b > 0; b >>= 1 , a = a * a % c){
        if (b & 1) res = res * a % c;
    }
    return res;
}
void solve(){
    cin >> n;
    f[1] = 2;
    // for (int i = 2; i <= n; i++){
    //     f[i] = (f[i - 1] + i * (i + 1)) % mod;
    // }
    // for (int i = 1; i <= n; i++) cout << f[i] << " "; cout << "\n";
    // cout << f[n] << "\n";
    ll res = n * (n + 1) % mod * (n + 2) % mod;
    res = res * power(3,mod-2,mod) % mod;
    cout << res;
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
    
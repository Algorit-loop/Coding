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
const int N = 5e3 + 10;
int n , x;
int v[N],a[N],c[N];
tuple<int,int,int> dp[N];
void solve(){
    
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
    
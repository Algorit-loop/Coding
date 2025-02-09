#include <bits/stdc++.h>
#define int long long 
#include <random>
#include <time.h>
#define ll long long 
#define fi first 
#define se second
#define ii pair<int,int>
using namespace std;
void __file(){
    if (fopen("card.inp","r")){
        freopen("card.inp","r",stdin);
        freopen("card.out","w",stdout);
    }
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}
const int mod = 1e9 + 7;
int dist(ii a, ii b){
    int f = (a.fi - b.fi); f = f * f;
    int g = (a.se - b.se); g = g * g;
    return f + g;
}
const int N = 2e5 + 100;
int n, d[N], dp[N];
void solve(){
    cin >> n;
    int r = 0;
    for (int i = 1; i <= n; i++){
        int x; cin >> x;
        d[x]++;
        r = max(r,x);
    }
    dp[0] = 0 * d[0];
    dp[1] = 1 * d[1];
    int get = dp[0];
    for (int i = 2; i <= r; i++){
        dp[i] = get + i * d[i];
        get = max(get, dp[i - 1]);
    }
    cout << *max_element(dp,dp + r + 1);
}
signed main(){
    srand(time(NULL));
    ios::sync_with_stdio(false); cin.tie(NULL);
    __file();       
    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; _++) solve();
    return 0;
}
    
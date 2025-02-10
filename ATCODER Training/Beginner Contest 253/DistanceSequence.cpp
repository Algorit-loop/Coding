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
const int mod = 998244353;
const int N = 5e3 + 10;
ll power(ll a, ll b, ll c){
    ll res = 1;
    a = a % c;
    for (; b > 0; b >>= 1 , a = a * a % c){
        if (b & 1) res = res * a % c;
    }
    return res;
}
int n,m,k;
int dp[N][N], pre[N][N];
void solve(){
    cin >> n >> m >> k;
    if (k == 0){
        cout << power(m,n,mod);
        return;
    }
    for (int i = 1; i <= m; i++) dp[i][1] = 1;
    for (int i = 1; i <= m; i++) pre[i][1] = (pre[i - 1][1] + dp[i][1]) % mod;
    for (int p = 2; p <= n; p++){
        for (int i = 1; i <= m; i++){
            int u = max(0LL,i - k) , v = min(m + 1,i + k);
            dp[i][p] = (pre[u][p - 1] + (pre[m][p - 1] - pre[v - 1][p - 1] + mod)) % mod;
            pre[i][p] = (pre[i - 1][p] + dp[i][p]) % mod;
            // cout << dp[i][p] << " "; cout << '\n';
        }
    }
    cout << pre[m][n];
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
    
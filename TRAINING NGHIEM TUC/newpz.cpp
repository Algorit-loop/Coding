#include <bits/stdc++.h>
#define int long long
#define ll long long 
using namespace std;
void file(string f){
    if (fopen((f + ".INP").c_str(),"r")){
        freopen((f + ".INP").c_str(),"r",stdin);
        freopen((f + ".OUT").c_str(),"w",stdout);
    }
}
const int N = 1e6 + 100;
const int mod = 1e9 + 7;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}
int f[N];
int F(int x){
    for (int i = 1; i <= x; i++){
        if (x % i != 0){
            return f[i] + 1;
        }
    }
}
int bru(int l, int r){
    int res = 0;
    for (int i = l; i <= r; i++) res += f[i];
    return res;
}
int t(int x){
    return x / 2 + (x % 2);
}
int kf(int x){
    return x / 2;
}
int get(int l, int r){
    int c1 = t(r) - t(l - 1);
    int c2 = kf(r) - kf(l - 1);
    int pl = l / 6; if (l % 6 > 0) pl++;
    int pr = r / 6;
    int c3 = t(pr) - t(pl - 1);
    return c1 + (c2 - c3) * 2 + c3 * 3;
}
int n , k;
int a[N] , dp[N], c[N], sum[N];
void solve(){
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];

    int j = 1 , s = 0;
    for (int i = 1; i <= n; i++){
        c[a[i]]++;
        if (c[a[i]] == 1) s++;
        while (j < i && s == k && c[a[j]] > 1){
            c[a[j]]--;
            if (c[a[j]] == 0) s--;
            j++; 
        }
        if (s == k) f[i] = j; else f[i] = -1;
    }
    // for (int i = 1; i <= n; i++) cout << f[i] << " "; cout << "\n";
    dp[0] = 1;
    sum[0] = 1;
    for (int i = 1; i <= n; i++){
        sum[i] = sum[i - 1];
        if (f[i] == -1) continue;
        dp[i] = sum[f[i] - 1];
        sum[i] = (sum[i] + dp[i]) % mod;
    }
    cout << dp[n] << "\n";
}
signed main(){
    file("txt");
    int t = 1;
    // cin >> t;
    while (t--){
        solve();
    }
    return 0;
}

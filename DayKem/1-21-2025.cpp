#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 2e5 + 100;
int n , P;
void file(string f){
    if (fopen((f + ".inp").c_str(),"r")){
        freopen((f + ".inp").c_str(),"r",stdin);
        freopen((f + ".out").c_str(),"w",stdout);
    }
}
int a[N], d[N], dp[N], pmax[N];
void solve(){
    cin >> n;
    int valuemax = 0;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        d[a[i]]++; // 1 <= a[i] <= 2e5
        valuemax = max(valuemax, a[i]);
    }
    // quy hoach dong
    dp[0] = 0;
    dp[1] = 1 * d[1];
    // prefix max 
    pmax[0] = dp[0];
    pmax[1] = max(dp[0],dp[1]);
    for (int i = 2; i <= valuemax; i++){
        dp[i] = pmax[i - 2] + i * d[i];
        // pmax[i - 1] = max(dp[0],dp[1],...,dp[i-1])
        pmax[i] = max(pmax[i - 1], dp[i]);
    }
    // cout << max(dp[0],dp[1],...,dp[valuemax);
    cout << pmax[valuemax];
}
signed main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    file("txt");
    int t = 1;
    // cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
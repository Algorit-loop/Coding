#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 6e5 + 100;

int n , a[N], m;
int dp[N] , smax[N] , k;
int sum[N], cnt[N];
signed main(){
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++){
        sum[a[i]] += a[i];
        cnt[a[i]]++;
    }
    int mxa = *max_element(a + 1,a + 1 + n);
    for (int i = 1; i <= mxa + mxa; i++) sum[i] = sum[i - 1] + sum[i] , cnt[i] = cnt[i-1] + cnt[i];
    int res = 1;
    for (int p = 2; p <= mxa; p++){
        int cost = 0;
        for (int i = p; i <= mxa + p; i += p){
            // cout << i << " " << (cnt[i] - cnt[i - p]) << " " << sum[i] - sum[i - p] << "\n";
            cost += i * (cnt[i] - cnt[i - p]) - (sum[i] - sum[i - p]);
        }
        if (cost <= k){
            // cout << "cost " << p << " = " << cost << "\n";
            res = p;
        }
    }
    int u = 0 , rr = 0;
    for (int i = 1; i <= n; i++) u += mxa - a[i];
    if (u <= k) rr = mxa , k -= u;
    rr += k / n;
    cout << max(rr,res);
    return 0;
}
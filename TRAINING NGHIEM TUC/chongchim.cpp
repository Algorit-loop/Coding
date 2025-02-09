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
int n, pre[N], dp[N];
pair <int,int> a[N];

void solve(){
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i].first;
    for (int i = 1; i <= n; i++) cin >> a[i].second;
    sort(a + 1,a  + 1 + n);
    pre[0] = 0;
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i].second;
    vector<int> v;
    a[0] = {-1,1e9};
    v.push_back(0);
    dp[0] = 0;
    for (int i = 1; i <= n; i++){
        while (a[v.back()].second < a[i].second){
            v.pop_back();
        }
        int pos = v.back();
        dp[i] = dp[pos] + a[i].second * (a[i].first - a[pos].first - 1) 
                                        - (pre[i - 1] - pre[pos]);
        v.push_back(i);
    }
    // for (int i = 1; i <= n; i++){
    //     cout << dp[i] << " ";
    // } cout << "\n";
    int q; cin >> q;
    while (q--){
        int x; cin >> x;
        int l = 0, r = n, res = -1;
        while (l <= r){
            int mid = (l + r) >> 1;
            if (dp[mid] < x){
                res = mid;
                l = mid + 1;
            } else r = mid - 1;
        }
        assert(res != -1);
        cout << res << "\n";
    }
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

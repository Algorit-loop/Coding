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
const int N = 1e3 + 10;
ll power(ll a, ll b, ll c){
    ll res = 1;
    a = a % c;
    for (; b > 0; b >>= 1 , a = a * a % c){
        if (b & 1) res = res * a % c;
    }
    return res;
}
int n , t , k , a[N];
void solve(){
    cin >> n >> t >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    if (t == 2){
        multiset <int> s;
        int l = 0 , r = 1e9, res = -1;
        while (l <= r){
            int mid = (l + r) >> 1;
            multiset <int> s;
            int total = 0;
            for (int i = 1; i <= n; i++){
                int cnt = distance(s.begin(),s.upper_bound(mid - a[i]));
                // cout << cnt << "\n";
                total += cnt;
                s.insert(a[i]);
            }
            if (total >= k){
                res = mid;
                r = mid - 1;
            } else l = mid + 1;
        }
        cout << res << "\n";
    }
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
    
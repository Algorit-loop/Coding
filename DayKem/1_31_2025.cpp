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

int cnt(int n, int k, int sum){
    int res = 0;
    for (int a = 1; a <= n; a++){
        int f = k / __gcd(a,k);
        // (a + f * x) <= sum 
        int x = min(n,(sum - a)) / f;
        x = max(x,0LL);
        res += x;
    }
    return res;
}
void solve(int n, int k, int v){
    // int n , k , v;
    // cin >> n >> k >> v;
    int l = 0 , r = 4e6, p = 0;
    while (l <= r){
        int mid = (l + r) >> 1;
        int f = cnt(n,k,mid);
        if (f < v){
            p = mid;
            l = mid + 1;
        } else r = mid - 1;
    }
    v = v - cnt(n,k,p);
    p++;
    for (int a = 1; a <= n; a++){
        int c = p - a;
        if (a * c % k == 0 && c <= n){
            v--;
            if (v == 0){
                cout << a << " " << c << "\n";
                return;
            }
        }
    }
}
map <pair<int,int>,bool> mps;
signed main(){
    srand(time(NULL));
    ios::sync_with_stdio(false); cin.tie(NULL);
    file("txt");    
    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; _++){
        cin >> n >> k >> v;
        solve(n,k,v);
        // for (int i = 1; i <= v; i++){
        //     solve(n,k,i);
        // }
    }
    return 0;
}
    
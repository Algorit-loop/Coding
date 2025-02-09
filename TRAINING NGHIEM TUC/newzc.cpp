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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}
int f[10000];
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
int k(int x){
    return x / 2;
}
int get(int l, int r){
    int c1 = t(r) - t(l - 1);
    int c2 = k(r) - k(l - 1);
    int pl = l / 6; if (l % 6 > 0) pl++;
    int pr = r / 6;
    int c3 = t(pr) - t(pl - 1);
    return c1 + (c2 - c3) * 2 + c3 * 3;
}
void solve(){
    f[1] = 0;
    f[2] = 0;
    f[3] = 1;
    for (int i = 4; i <= 10000; i++) f[i] = F(i);
    cout << *max_element(f + 3, f + 1 + 10000) << "\n";
    int u = 10;
    while (u--){
        int l = range(3,5000) , r = range(l + 1, 10000);
        cout << l << " " << r << "\n";
        cout << "bru = " << bru(l,r) << "\n";
        cout << "get = " << get(l,r) << "\n";
        if (bru(l,r) != get(l,r)) cout << "error\n";
    }
}
signed main(){
    file("txt");
    int t = 1;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}

#include <bits/stdc++.h>
#include <random>
#include <chrono>
#define int long long 
#define ll long long 
using namespace std;
const int N = 6e5 + 100;
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}
int a , b , n;
int f(int x, int a, int b){
    int bcnn = a * b / __gcd(a,b);
    return x / a + x / b - x / bcnn;
}
signed main(){
    if (fopen("custom.inp","r")){
        freopen("custom.inp","r",stdin);
        freopen("custom.out","w",stdout);
    }
    int a,b;
    cin >> n;
    int u = range(0,n) , v = n - u;
    cout << u << " zhaha " << v;
    return 0;
}
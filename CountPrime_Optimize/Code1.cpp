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
const int N = 1e6 + 100;
const int mod = 1e9 + 7;
#include <iostream>
#include <vector>
#include <cmath>
#define int long long 
using namespace std;

vector<int> sieve(int limit) {
    vector<bool> is_prime(limit + 1, true);
    vector<int> primes;
    
    for (int i = 2; i <= limit; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return primes;
}
void bruteforce(int n){
    vector <int> primes = sieve(n);
    cout << "Brute = " << (int)primes.size() << "\n";
}
// --------------------------
const int LIM = 1e7 + 100;
int lp[LIM + 2] , pr[LIM] , cnt = 0;
void Sieve_Linear(int N_SIEVE){
    lp[0] = -1;
    lp[1] = 0;
    for (int i = 2; i <= N_SIEVE; i++){
        if (!lp[i]) lp[i] = pr[++cnt] = i;
        for (int j = 1; j <= cnt && pr[j] <= lp[i] && pr[j] * i <= N_SIEVE; j++)
            lp[pr[j] * i] = pr[j];
    }
}
map<pair<int,int>,int> mps;
long long phi(long long x, int a) {
    if (a == 0) return x;
    if (x < pr[a]) return 1;
    // if (mps.count({x,a})) return mps[{x,a}];
    return  phi(x, a - 1) - phi(x / pr[a], a - 1);
}

long long prime_count(long long n) {
    if (n < 2) return 0;
    
    int limit = sqrt(n); // n^(1/3) | n^(1/2) ? 
    Sieve_Linear(limit);
    
    return phi(n,cnt) + cnt - 1;
}
int pi(int n){
    return phi(n,cnt) + cnt - 1;
}
void solve(){
    // int n; cin >> n;
    // // bruteforce(n);
    // clock_t st = clock();
    // int res = prime_count(n);
    // clock_t en = clock();
    // cout << res << "\n";
    // cout << "Time: " << (double)(en-st) << " ms\n";
    int limit = 1e4;
    Sieve_Linear(limit);
    int a,b;
    cin >> a >> b;
    cout << pi(b) - pi(a-1) << "\n";
}
signed main(){
    srand(time(NULL));
    ios::sync_with_stdio(false); cin.tie(NULL);
    file("txt");    
    int t = 1;
    cin >> t;
    for (int _ = 1; _ <= t; _++) solve();
    return 0;
}
    
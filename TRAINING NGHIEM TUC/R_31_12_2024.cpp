#include <bits/stdc++.h>
#include <random>
#include <time.h>
#define int long long
#define ll long long 
#define fi first 
#define se second
#define ii pair<int,int>
using namespace std;
void __file(){
    if (fopen("input.txt","r")){
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    }
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}
const int N = 2e5 + 100;
const int mod = 1e9 + 7;
int dist(ii a, ii b){
    int f = (a.fi - b.fi); f = f * f;
    int g = (a.se - b.se); g = g * g;
    return f + g;
}
int f(int p, int q){
    assert(p >= q);
    int res = 0;
    for (int i = 1; i <= p - q; i++) res = res * 10 + 8;
    for (int i = 1; i <= q; i++) res = res * 10 + 6;
    return res;
}
string H = "URDL";
int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};
int cc(char x){
    int pos = H.find(x);
    return pos;
}
int power(int a, int b, int c){
    a = a % c;
    int res = 1;
    for (; b > 0; b >>= 1 , a = a * a % c){
        if (b & 1) res = res * a % c;
    }
    return res;
}
int get(int x){
    // dem cac so chia het cho 3 hoac tan cung la 3 
    // tu 1 -> x 
    int r = x / 3;
    r += (x + 7) / 10;
    int f = x / 10;
    r -= f/3 + 1 - (f%3==0 && x%10<3);
    // -------------
    return x - r;
}
void solve(){
    int n , p;
    cin >> p >> n;
    vector <bool>  d(p, 0);
    vector <int> loop;
    // --------- Tim vong lap cua mod P ----------
    int val = 1 , kk = 0;
    for (int i = 0; ;i++){
        // val = 10^i 
        kk = (kk + val) % p;
        if (d[kk] == 0){
            loop.push_back(kk);
            d[kk] = 1;
        }
        else break;
        val = val * 10 % p;
    }
    // S(1) % p , S(2) % p , ... , S(n-1) % p 
    // for (auto x : loop) cout << x << " "; cout << "\n";
    // -------------------------------------------------
    // 9 % p * S % p = 0 
    // -------------- truong hop special -----------
    if (9 % p == 0){
        cout << n;
        return;
    }
    // -------------------------------------------------
    // S(x) = 1 + 10 + 100 + ... + 10^x
    // f la tap hop cac so X sao cho 9 * X % p = 0 
    // 0 <= X < p
    vector <int> f;
    for (int i = 0; i < p; i++){
        if (9 % p * i % p == 0) f.push_back(i);
    }
    // for (auto x : f) cout << x << " "; cout << "\n";
    
    // sum = (1 + 10 + 100 + 1000 .. 10^(n - 1)) % p 
    // S(x) thuoc {a1,a2,...,ak} | S(x) thuoc f 
    // int sum = 0 , res = 0;
    // val = 1;
    // for (int i = 0; i < n; i++){
    //     sum = (sum + val) % p;
    //     // ------ val sum -------
    //     bool check = false;
    //     for (auto x : f) if (sum == x) check = true;
    //     if (check) res++;
    //     val = val * 10 % p;
    // }
    // cout << res << " | cay trau\n";
    // cout << loop.size() << " " << f.size() << "\n";
    clock_t st = clock();
    // ------------- Accepted -------------------------
    int G = n / (int)loop.size();
    vector <int> C((int)loop.size(),0);
    for (int i = 0; i < C.size(); i++){
        C[i] = G;
    }
    int ans = 0;
    for (int i = 0; i < n % (int)loop.size(); i++) C[i]++;
    map <int,int> mps;
    for (int i = 0; i < C.size(); i++){
        mps[loop[i]] = C[i];
    }
    for (int i = 0; i < f.size(); i++){
        // dem f[i] co bao nhieu lan trong S(x) | x = 1 -> n
        ans += mps[f[i]];
    }
    clock_t en = clock();
    // cout << "AC = " << ans << "\n";
    cout << ans;
    // cout << "Time of AC: " << ((double)(en - st)/CLOCKS_PER_SEC);
}
signed main(){
    srand(time(NULL));
    ios::sync_with_stdio(false); cin.tie(NULL);
    __file();       
    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; _++) solve();
    return 0;
}
    // int n = 1000000;
    // int ok = 0;
    // for (int T = 1; T <= n; T++){
    //     for (int i = 1; i <= 3; i++) d[i] = 0;
    //     // int x = rand() % 3 + 1;
    //     // vector <int> v;
    //     // d[x] = 1;
    //     // int choose = rand() % 3 + 1;
    //     // for (int i = 1; i <= 3; i++){
    //     //     if (d[i] == 0 && i != choose) v.push_back(i);
    //     // }
    //     // int open = v[rand() % (int)v.size()];
    //     // // cout << v.size() << "\n";
    //     // for (int i = 1; i <= 3; i++){
    //     //     if (i != choose && i != open) choose = i;
    //     // }
    //     // if (d[choose] == 1) ok++;
    //     int x = rand() % 3 + 1;
    //     d[x] = 1;
    //     int choose = rand() % 3 + 1;
    //     if (d[choose] == 0) ok++;
    // }
    // cout << ok << " / " << n << "\n";
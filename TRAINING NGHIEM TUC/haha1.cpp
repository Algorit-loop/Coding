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
const int N = 1e6 + 100;
const int mod = 1e9 + 7;
int dist(ii a, ii b){
    int f = (a.fi - b.fi); f = f * f;
    int g = (a.se - b.se); g = g * g;
    return f + g;
}

bool cphuong(ll x){
    int u = sqrt(x);
    return u * u == x;
}
int power(int a, int b, int c){
    int res = 1;
    a = a % c;
    for (; b > 0; b >>= 1 , a = a * a % c){
        if (b & 1) res = res * a % c;
    }
    return res;
}
int n , m;
vector <int> adj[N];
vector <int> jda[N];
int  avail[N] , d[N];
__int128_t f[2004][2004];
__int128_t dp[N];
void DFS(int u, int c){
    if (u == n){
        dp[c]++;
        return;
    }
    for (int v : adj[u]){
        DFS(v,c+1);
    }
}
void BFS()
{
    queue <int> q;
    q.push(1);
    f[1][1] = 1;
    while (!q.empty()){
        int u = q.front(); q.pop();
        for (auto v : adj[u]){
            for (int i = 0; i <= n; i++){
                f[v][i + 1] = f[v][i + 1] + f[u][i];
                // assert(f[v][i + 1] <= 1e16);
            }
            d[v]--;
            if (d[v] == 0) q.push(v);
        }
    }
}
string cc(__int128_t x){
    string res = "";
    if (x == 0) return "0";
    int ck = 0;
    if (x < 0) x = -x , ck = 1;
    while (x > 0){
        res = char(x % 10 + 48) + res;
        x /= 10;
    }
    if (ck) res = "-" + res;
    return res;
}
void solve(){
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        int u , v;
        cin >> u >> v;
        // jda[u].push_back(v);
        adj[u].push_back(v);
        d[v]++;
    }
    // BFS();
    DFS(1,1);
    // __int128_t res = 0;
    // for (int i = 1; i <= n; i++){
    //     if ((i + 1) % 2 == 0){
    //         res = res + f[n][i];
    //     } else res = res - f[n][i];
    // }
    // cout << cc(res) << "\n";
    // for (int i = 1; i <= n; i++) cout << f[n][i] << " "; cout << "\n";
    // for (int i = 1; i <= n; i++) cout << dp[i] << " ";
    __int128_t r = 0;
    for (int i = 1; i <= n; i++){
        if ((i + 1) % 2 == 0){
            r = r + dp[i];
        } else r = r - dp[i];
    }
    cout << cc(r);
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
    // int n; cin >> n;
    // int ok = 0;
    // for (int T = 1; T <= n; T++){
    //     for (int i = 1; i <= 3; i++) d[i] = 0;
    //     int x = rand() % 3 + 1;
    //     vector <int> v;
    //     d[x] = 1;
    //     int choose = rand() % 3 + 1;
    //     for (int i = 1; i <= 3; i++){
    //         if (d[i] == 0 && i != choose) v.push_back(i);
    //     }
    //     int open = v[rand() % (int)v.size()];
    //     cout << v.size() << "\n";
    //     // for (int i = 1; i <= 3; i++){
    //     //     if (i != choose && i != open) choose = i;
    //     // }
    //     if (d[choose] == 1) ok++;
    // }
    // cout << ok << " / " << n;
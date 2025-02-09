#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <stdio.h>
#include <chrono>
#include <random>

#include <set>
#include <unordered_set>
#include <bitset>
#include <map>
#include <unordered_map>
#include <queue>
#include <deque>
#include <vector>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define int long long 
#define ll long long
#define ld long double
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define ii pair<int,int>
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define pil pair<int,ll>
#define plii pair<ll,pair<int,int>>
#define heapmax(type) priority_queue<type>
#define heapmin(type) priority_queue<type,vector<type>,greater<type>>
#define ordered_multiset  tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_set       tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define FASTIO ios::sync_with_stdio(NULL); cin.tie(NULL); cout.tie(NULL);
#define sz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
#define getbit(mask,i) ((mask >> i) & 1)

template<typename T> bool maximize(const T &res, const T &val) { if (res <  val) { res = val; return true; } return false; }
template<typename T> bool minimize(const T &res, const T &val) { if (res >  val) { res = val; return true; } return false; }
template<typename T> ll rv_num(T x){
    ll res = 0;
    while (x > 0) res = res*10 + x % 10 , x/=10;
    return res;
}
const ll mod = 1e9 + 7;
const ld PI = acos(-1);
const int N = 2e6 + 100;
const int N_Trie = 1e5;
const int N_ST = 2e5 + 10;
const int N_BIT = 2e5 + 10;
const int ooint = (1LL << 31) - 1;
// const ll ooll = (1LL << 63) - 1;
const int LIM = 1e7; // N_Prime
const int N_MST = 1e5; // N of Merge Sort Tree
const int N_Hash = 2e6 + 10;

        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void file(const string FILE){
    if (fopen((FILE + ".INP").c_str(),"r")){
        freopen((FILE + ".INP").c_str(), "r", stdin);
        freopen((FILE + ".OUT").c_str(), "w", stdout);
    }
}
ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}

ll power(ll a,ll b,ll c){ // O(log(b))
    ll res = 1;
    a = a % c;
    for (; b > 0; b >>= 1 , a = a * a % c)
        if (b & 1) res = res * a % c;
    return res;
}
ll pw(ll a, ll b, ll c){
    if (b == 0) return 1;
    if (b == 1) return a % c;
    ll f = pw(a, b / 2, c);
    f = f * f % c;
    if (b % 2 == 0) return f;
    else return (f * (a % c)) % c;
}
int lcm(ll a, ll b){
    return a / __gcd(a,b) * b;
}
int n , x;
string a,b,c;
string P = "" , ans = "";
string f[100];
void dfs(int i, int j, int k){
    if (i == a.size() && j == b.size() && k == c.size()){
        ans = max(ans, P);
        string U = "";
        for (int r = 0; r < ans.size(); r++){
            U = U + ans[r];
            f[r + 1] = U;
        }
        return;
    }
    if (f[(int)P.size()] > P) return;
    if (i < a.size()){
        P = P + a[i];
        dfs(i + 1,j,k);
        // quay ve tai day
        P.pop_back();
    }
    if (j < b.size()){
        P = P + b[j];
        dfs(i,j + 1,k);
        P.pop_back();
    }
    if (k < c.size()){
        P = P + c[k];
        dfs(i,j,k + 1);
        P.pop_back();
    }
}
string dp[100][100][100];

void DynamicProgramming(string a, string b, string c){
    int n = a.size() , m = b.size() , q = c.size();
    a = a + "!"; b = b + "!"; c = c + "!";
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            for (int k = 0; k <= q; k++){
                dp[i][j][k] = "0";
            }
        }
    }
    dp[0][0][0] = "";
    // dp[i][j][k] = so lon nhat xet a[0 .. i] , b[0 .. j] , c[0 .. k]
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            for (int k = 0; k <= q; k++){
                dp[i + 1][j][k] = max(dp[i + 1][j][k], dp[i][j][k] + a[i]);
                // dp[1][0][0] = "a";
                dp[i][j + 1][k] = max(dp[i][j + 1][k], dp[i][j][k] + b[j]);
                dp[i][j][k + 1] = max(dp[i][j][k + 1], dp[i][j][k] + c[k]);
            }
        }
    }
    // i = a.size() - 1 , j = b.size() - 1 , k = c.size() - 1
    // i + 1 , j , k = a.size() , b.size() - 1, c.size() - 1
    // dp[a.size()][b.size()][c.size()]
    cout << "DP = " << dp[n][m][q] << "\n";
}
void solve(){
    f[0] = "";
    cin >> a >> b >> c;
    P = "";
    ans = "";
    for (int i = 1; i <= a.size() + b.size() + c.size(); i++) ans = ans + '0';
    string U = "";
        for (int r = 0; r < ans.size(); r++){
            U = U + ans[r];
            f[r + 1] = U;
        }
    clock_t st = clock();
    dfs(0,0,0);
    clock_t en = clock();
    cout << ans << "\n";
    cout << "Time = " << ((double)(en-st)/CLOCKS_PER_SEC) << "s\n";
    st = clock();
    DynamicProgramming(a,b,c);
    en = clock();
    cout << "Time = " << ((double)(en-st)/CLOCKS_PER_SEC) << "s\n";
}
signed main()
{
    FASTIO;
    file("txt");
    int t = 1;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}

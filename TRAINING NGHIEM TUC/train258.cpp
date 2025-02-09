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
const int N = 2e5 + 100;
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
vector <int> findrp(const string &s, int i, int j) {
    int len = j - i + 1;
    vector <int> v;
    v.pb(len);
    for (int k = 1; k <= len / 2; ++k) {
        if (len % k == 0) {
            bool match = true;
            for (int l = i; l <= j; ++l) {
                if (s[l] != s[i + (l - i) % k]) {
                    match = false;
                    break;
                }
            }
            if (match){
                v.pb(k);
            }
        }
    }
    return v;
}

string tostring(int num) {
    string result;
    while (num > 0) {
        result.push_back('0' + num % 10);
        num /= 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

string compressString(const string &s) {
    int n = s.size();
    vector<vector<string>> dp(n, vector<string>(n));

    for (int i = 0; i < n; ++i) {
        dp[i][i] = s[i];
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            dp[i][j] = s.substr(i, len);

            for (int k = i; k < j; ++k) {
                if (dp[i][j].size() > dp[i][k].size() + dp[k + 1][j].size()) {
                    dp[i][j] = dp[i][k] + dp[k + 1][j];
                }
            }
            vector <int> rpv = findrp(s, i, j);
            for (auto g : rpv){
                // cout << "sizerp " << i << " " << j << " : " << sizerp << " - " << len << "\n";

                int nb = len / g;
                // cout << i << " " << j << " : " << nb << " ? ";
                vector <int> v;
                for (int i = 9; i >= 2; i--){
                    while (nb % i == 0){
                        v.push_back(i);
                        nb /= i;
                    }
                }
                // for (auto x : v) cout << x << " "; cout << "\n";
                if (nb == 1){
                    string rpp = dp[i][i + g - 1];
                    for (auto x : v){
                        rpp = tostring(x) + "(" + rpp + ")";
                    }
                // string str_repeat = tostring(len / sizerp) + "(" + dp[i][i + sizerp - 1] + ")";
//                    if (str_repeat.size() <= dp[i][j].size()) {
//                        dp[i][j] = str_repeat;
//                    }
                    if (rpp.size() < dp[i][j].size()) {
                        dp[i][j] = rpp;
                    }
                }

            }

            // cout << i << " " << j << " : " << dp[i][j] << "\n";
        }
    }
//    for (int i = 0; i < n; i++){
//        for (int j = i; j < n; j++){
//            cout << i << " -> " << j << " : " << dp[i][j] << "\n";
//        }
//    }
    return dp[0][n - 1];
}
int main()
{
    // FASTIO;
    string s; cin >> s;
    cout << compressString(s);
    // cout << findrp(s,0,s.size()-1);
    return 0;
}

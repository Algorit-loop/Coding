//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")

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
 #define int long long
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
const int N = 1e6 + 100;
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
inline int readInt() {
    int num = 0;
    char c = getchar();

    // Bỏ qua các ký tự không phải số
    while (c < '0' || c > '9') {
        c = getchar();
    }

    // Đọc các ký tự số và chuyển đổi chúng thành số nguyên
    while (c >= '0' && c <= '9') {
        num = num * 10 + (c - '0');
        c = getchar();
    }

    return num;
}
struct node{
    int l,r,pos;
};
node que[N];
int P,q,ans[N],d[N];
string s;
int how[N] , dem[N];
int mps[N];
void solve(){
    // cin >> n >> m >> k;
    cin >> P;
    cin >> s;
    int n = s.size();
    s = "!" + s;
    cin >> q;
    for (int i = 1; i <= q; i++){
        cin >> que[i].l >> que[i].r;
        que[i].pos = i;
    }
    for (int i = 1; i <= n; i++){
        if (s[i] == '0') how[i] = i , dem[i] = 1;
        else how[i] = 0 , dem[i] = 0;
    }
    for (int i = 1; i <= n; i++) how[i] = how[i - 1] + how[i] , dem[i] = dem[i - 1] + dem[i];
    if (P == 2 || P == 5){
        for (int i = 1; i <= q; i++){
            int sum = how[que[i].r] - how[que[i].l-1];
            int res = sum - (que[i].l-1) * (dem[que[i].r] - dem[que[i].l - 1]);
            cout << res << "\n";
        }
        return;
    }
    for (int i = 1; i <= n; i++){
        d[i] = (s[i]-48) * power(10,n-i,P);
    }
    for (int i = 1; i <= n; i++) d[i] = (d[i - 1] + d[i]) % P;
    vector <int> rs;
    for (int i = 1; i <= n; i++){
        rs.push_back(d[i]);
    }
    sort(all(rs));
    rs.resize(unique(all(rs)) - rs.begin());
    for (int i = 1; i <= n; i++) d[i] = lower_bound(all(rs),d[i]) - rs.begin();
//    for (int i = 1; i <= q; i++){
//        int ha = 0;
//        for (int j = que[i].l; j <= que[i].r; j++){
//            for (int k = j; k <= que[i].r; k++){
//                int ls = power(10,n-i,P);
//                int gt = (d[k] - d[j-1] + P) * power(ls,P-2,P) % P;
//                if (gt == 0) ha++;
//            }
//        }
//        cout << ha << "\n";
//    }
    sort(que + 1, que + 1 + q,[](const node &u, const node &v){
        if (u.l / 300 != v.l / 300) return u.l / 300 < v.l / 300;
        return u.r < v.r;
    });
    int u = 0 , v = 0;
    int res = 0;
    mps[0]++;
    for (int i = 1; i <= q; i++){
        while (v < que[i].r){
            v++;
            res = res + mps[d[v]];
            mps[d[v]]++;
        }
        while (v > que[i].r){
            mps[d[v]]--;
            res -= mps[d[v]];
            v--;
        }
        while (u < que[i].l - 1){
            mps[d[u]]--;
            res = res - mps[d[u]];
            u++;
        }
        while (u > que[i].l - 1){
            u--;
            res += mps[d[u]];
            mps[d[u]]++;
        }
        ans[que[i].pos] = res;
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << "\n";
    return;
}
signed main()
{
    FASTIO;
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}

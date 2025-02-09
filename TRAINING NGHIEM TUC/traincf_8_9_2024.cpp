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
/*int lp[LIM], pr[LIM], cnt = 0;
void sieve(int lim){
    for (int i = 2; i <= lim; i++){
        if (!lp[i]) lp[i] = pr[++cnt] = i;
        int j = 1;
        while (j <= cnt && pr[j] <= lp[i] && pr[j] * i <= lim){
            lp[pr[j] * i] = pr[j];
            j++;
        }
    }
}*/
struct SuffixArray {
    int sa[N], tmp[N], r[N], c[N]; // Các mảng cần thiết để xây dựng Suffix Array
    int lcp[N], rr[N]; // Mảng LCP và rr
    int n; // Kích thước của vector đầu vào

    // Hàm so sánh hai suffix trong quá trình xây dựng Suffix Array
    bool CmpSuff(int u, int v, int k) {
        if (r[u] != r[v]) return r[u] < r[v];
        if (u + k < n && v + k < n)
            return r[u + k] < r[v + k];
        return (u > v);
    }

    // Counting Sort với bước dịch chuyển k
    void CountingSort(int k) {
        memset(c, 0, sizeof(c));
        for (int i = 0; i < n; i++) {
            int u = (sa[i] + k < n ? r[sa[i] + k] : 0);
            c[u]++;
        }
        for (int i = 1; i <= max(n, 256); i++) c[i] += c[i - 1];
        for (int i = n - 1; i >= 0; i--) {
            int u = (sa[i] + k < n ? r[sa[i] + k] : 0);
            tmp[--c[u]] = sa[i];
        }
        for (int i = 0; i < n; i++) sa[i] = tmp[i];
    }

    // Hàm xây dựng Suffix Array
    void make_SuffixArray() {
        for (int i = 0; i < n; i++) {
            sa[i] = i;
            r[i] = r[i];
        }
        for (int k = 1; k < n; k <<= 1) {
            CountingSort(k);
            CountingSort(0);
            tmp[sa[0]] = 1;
            for (int i = 1; i < n; i++)
                tmp[sa[i]] = tmp[sa[i - 1]] + CmpSuff(sa[i - 1], sa[i], k);
            for (int i = 0; i < n; i++) r[i] = tmp[i];
            if (tmp[sa[n - 1]] == n) break;
        }
    }

    // Hàm xây dựng mảng LCP
    void build_LCP(const vector<int> &a) {
        for (int i = 0; i < n; i++) rr[sa[i]] = i;
        int h = 0;
        for (int i = 0; i < n; i++) {
            if (rr[i] > 0) {
                int j = sa[rr[i] - 1];
                while (i + h < n && j + h < n && a[i + h] == a[j + h]) h++;
                lcp[rr[i]] = h;
                if (h > 0) h--;
            }
        }
    }

    // Constructor nhận một vector và khởi tạo Suffix Array
    SuffixArray(const vector<int> &input) {
        n = input.size();
        for (int i = 0; i < n; i++) {
            r[i] = input[i];
        }
        make_SuffixArray();
        build_LCP(input); // Xây dựng LCP sau khi đã có Suffix Array
    }
};
struct dttt
{
    int l , r;
};
dttt dmin[N],dmax[N];
vector <ii> st;
int top()
{
    return st.size() - 1;
}
void find_min(const vector <int> &a)
{
    ll n = a.size() - 1;
    st.clear();
    st.push_back(ii(-1e9,0));
    for (int i = 1; i <= n; i++)
        if (st[top()].first <= a[i])
        {
            dmin[i].l = st[top()].second + 1;
            st.push_back(ii(a[i],i));
        }
        else
        {
            while (st[top()].first > a[i]) st.pop_back();
            dmin[i].l = st[top()].second + 1;
            st.push_back(ii(a[i],i));
        }
    st.clear();
    st.push_back(ii(-1e9,n+1));
    for (int i = n; i >= 1; i--)
    {
        if (st[top()].first < a[i])
        {
            dmin[i].r = st[top()].second - 1;
            st.push_back(ii(a[i],i));
        }
        else
        {
            while (st[top()].first >= a[i]) st.pop_back();
            dmin[i].r = st[top()].second - 1;
            st.push_back(ii(a[i],i));
        }
    }
    // for (int i = 1; i <= n; i++) cout << a[i] << " "; cout << "\n";
    ll ans = 0;
    for (int i = 1; i <= n; i++){
        long long x = i - dmin[i].l , y = dmin[i].r - i;
        // cout << dmin[i].l << " " << dmin[i].r << "\n";
        ans += (x*y + x + y)*a[i];
    }
    for (int i = 1; i <= n; i++) ans += a[i];
    ans = ans * 2;
    ans = ans + n*(n+1)/2;
    ll uu = n * n;
    ll gg = __gcd(ans,uu);
    cout << ans/gg << "/" << uu/gg;
}
int main()
{
    //freopen("CUTXAU.inp","r",stdin);
    //freopen("CUTXAU.out","w",stdout);
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int n;    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    SuffixArray SS(a);
    // for (int i = 0; i < n; i++) cout << SS.sa[i] << " "; cout << "\n";
    // for (int i = 0; i < n; i++) cout << SS.lcp[i] << " "; cout << "\n";
    vector <int> cc(n+1);
    for (int i = 1; i <= n; i++) cc[i] = SS.lcp[i - 1];
    find_min(cc);
    return 0;
}




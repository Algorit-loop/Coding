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
struct SegmentTreeMin {
    vector<long long> tree, lazy;
    int n;

    SegmentTreeMin(int size) {
        n = size;
        tree.resize(4 * n, INF);
        lazy.resize(4 * n, 0);
    }

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update(int node, int start, int end, int l, int r, long long value) {
        push(node, start, end);
        if (start > r || end < l) return;
        if (l <= start && end <= r) {
            lazy[node] += value;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update(node * 2, start, mid, l, r, value);
        update(node * 2 + 1, mid + 1, end, l, r, value);
        tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
    }

    long long query(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (start > r || end < l) return INF;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        long long leftMin = query(node * 2, start, mid, l, r);
        long long rightMin = query(node * 2 + 1, mid + 1, end, l, r);
        return min(leftMin, rightMin);
    }

    void update(int l, int r, long long value) {
        update(1, 1, n, l, r, value);
    }

    long long query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};
struct SegmentTreeSum {
    vector<long long> tree, lazy;
    int n;

    SegmentTreeSum(int size) {
        n = size;
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node] * (end - start + 1);
            if (start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update(int node, int start, int end, int l, int r, long long value) {
        push(node, start, end);
        if (start > r || end < l) return;
        if (l <= start && end <= r) {
            lazy[node] += value;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update(node * 2, start, mid, l, r, value);
        update(node * 2 + 1, mid + 1, end, l, r, value);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }


    long long query(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (start > r || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        long long leftSum = query(node * 2, start, mid, l, r);
        long long rightSum = query(node * 2 + 1, mid + 1, end, l, r);
        return leftSum + rightSum;
    }

    void update(int l, int r, long long value) {
        update(1, 1, n, l, r, value);
    }

    long long query(int l, int r) {
        return query(1, 1, n, l, r);
    }
};
ll n,k,q;
void solve(){
    cin >> n >> k >> q;
    vector <ll> a(n + 1,0) , res(n+1,0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    multiset <pll> s;
    map <ll,ll> mps;
    for (int i = 1; i <= n; i++){
        // add
        ll gt = a[i] - i;
        auto f = s.find({mps[gt],gt});
        if (f != s.end()){
            s.erase(f);
        }
        mps[gt]++;
        s.insert({mps[gt],gt});
        // ----remove--------
        if (i - k > 0){
            ll gt = a[i - k] - (i - k);
            auto f = s.find({mps[gt],gt});
            if (f != s.end()){
                s.erase(f);
            }
            mps[gt]--;
            s.insert({mps[gt],gt});
        }
        if (i >= k){
            auto ff = *s.rbegin();
            res[i] = k - ff.fi;
        }
    }
    SegmentTreeMin smin(n+1);
    SegmentTreeSum ssum1(n+1) , ssum2(n+1);
    for (int i = k; i <= n; i++){
        int l = k , r = i, pos = k - 1;
        while (l <= r){
            int mid = (l + r) >> 1;
            if (smin.query(k,mid) <= res[i]){
                pos = mid;
                l = mid + 1;
            } else r = mid - 1;
        }
        if (pos >= k){
            ssum1.update
        }
    }
}
int main()
{
    FASTIO;
    int t; cin >> t;
    while (t--){
        solve();
    }
    return 0;
}

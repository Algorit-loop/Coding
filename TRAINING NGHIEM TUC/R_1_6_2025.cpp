#include <bits/stdc++.h>
#include <random>
#include <time.h>
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
struct node{
    int l , r, pos;
};
node qr[N];
int ans[N] , a[N] , n ,q;
ll d[N];
int mps[N];
void update(ll &cnt, int val, int type){
    if (type == -1){
        cnt -= d[val] * (d[val] - 1) / 2;
        cnt -= mps[val] + mps[val + 1];
    }
    else{
        cnt += d[val] * (d[val] - 1) / 2;
        cnt += mps[val] + mps[val + 1];
    }
}
void solve(){
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    cin >> q;
    for (int i = 1; i <= q; i++) cin >> qr[i].l >> qr[i].r , qr[i].pos = i;
    int block = sqrt(2 * n);
    sort(qr + 1,qr + 1 + q,[&](const node &u, const node &v){
        if (u.l / block != v.l / block) return u.l / block < v.l / block;
        return u.r < v.r;
    });
    int it1 = 1 , it2 = 0;
    ll cnt = 0;
    for (int i = 1; i <= q; i++){
        while (it2 < qr[i].r){
            it2++;
            update(cnt, a[it2], -1);
            // cout << "pre_cnt = " << cnt << "\n";
            d[a[it2]]++;
            int val = a[it2];
            // cout << val << "\n";
            // cout << d[val - 1] << " " << d[val] << " " << d[val + 1] << "bro\n";
            mps[val] = d[val - 1] * d[val];
            mps[val + 1] = d[val] * d[val + 1];
            update(cnt, a[it2], +1);
            // update answer
            // cout << "cnt = " << cnt << "\n";
        }
        while (it2 > qr[i].r){
            update(cnt, a[it2], -1);
            d[a[it2]]--;
            int val = a[it2];
            mps[val] = d[val - 1] * d[val];
            mps[val + 1] = d[val] * d[val + 1];
            update(cnt, a[it2], +1);
            // update answer 
            it2--;
        }
        while (it1 < qr[i].l){
            update(cnt, a[it1], -1);
            d[a[it1]]--;
            int val = a[it1];
            mps[val] = d[val - 1] * d[val];
            mps[val + 1] = d[val] * d[val + 1];
            update(cnt, a[it1], +1);
            // update answer
            it1++;
        }
        while (it1 > qr[i].l){
            it1--;
            update(cnt, a[it1], -1);
            d[a[it1]]++;
            int val = a[it1];
            mps[val] = d[val - 1] * d[val];
            mps[val + 1] = d[val] * d[val + 1];
            update(cnt, a[it1], +1);
            // update answer
        }
        // x -> x-1
        // x -> x+1
        // cout << it1 << " " << it2 << " " << cnt << "\n";
        int f = (it2 - it1 + 1);
        ans[qr[i].pos] = 1LL * f*(f-1)/2 - cnt;
    }
    for (int i = 1; i <= q; i++) cout << ans[i] << "\n";
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
    
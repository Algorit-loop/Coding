#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define mp make_pair
#define int long long
#define pb push_back
#define pll pair<long long, long long>
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
const int lim = 1e18;
typedef pair<int, int> pint;
typedef pair<pair<int, int>, pair<int, int>> tint;
typedef long double ld;
const int N = 4e5;
int a[N + 10];
int pre[N + 10];
int pree[N + 10];
int f[N + 10];
int h[N + 10];
int u[N + 10];
int get(int x,int y){
    if(y < x) return 0;
    return u[y] - u[x - 1];
}
void solve() {
    int n;
    cin >> n;
    int q;

    for(int i = 1 ; i <= n ; i ++) cin >> a[i];
    for(int i = 1 ; i <= n ; i ++){
        pre[i] = pre[i - 1] + a[i];
        pree[i] = pree[i - 1] + pre[i - 1] + a[i];
        f[i] = f[i - 1] + n - i + 1;
        h[i] = pre[i] * (n - i);
    }
    for(int i = 1 ; i <= n ; i ++){
        u[i] = pree[n] - pree[i - 1];
        u[i] -= h[i];
        u[i] = u[i - 1] + u[i];
        cout << u[i] << endl;
    }
    cin >> q;
    while(q --){
        int l,r;
        cin >> l >> r;
        int xl = lim,xr = lim;
        int yl = 1, yr = n;
        while(yl <= yr){
            int mid = (yl + yr) / 2;
            if(f[mid] < l){
                yl = mid + 1;
            }
            else{
                xl = mid;
                yr = mid - 1;
            }
        }
        yl = 1,yr = n;
        while(yl <= yr){
            int mid = (yl + yr) / 2;
            if(f[mid] < r){
                yl = mid + 1;
            }
            else{
                xl = mid;
                yr = mid - 1;
            }
        }
        l = l - f[xl - 1] + (xl - 1);
        r = r - f[xr - 1] + (xr - 1);
        cout << l << " " << r << endl;
//        int res = 0;
//        if(xl == xr){
//            res = (pree[r] - pree[l - 1]) - pre[xl - 1] * (r - l + 1);
//        }
//        else{
//            if(xl + 1 > xr - 1){
//                cout << 0 << endl;
//                continue;
//            }
//            res = get(xl + 1,xr - 1);
//            res += (pree[n] - pree[l - 1]) - (pre[xl - 1]) * (n - l + 1);
//            res += (pree[r] - pree[xr - 1]) - pre[xr - 1] * (r - xr + 1);
//        }
//        cout << res << endl;
    }



}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);


    int test = 1;
  //  cin >> test;
    for(int testcase = 1; testcase <= test; testcase++) {
        solve();
    }
}

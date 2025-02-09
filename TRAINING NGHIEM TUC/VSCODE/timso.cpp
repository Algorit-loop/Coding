#include <bits/stdc++.h>
#define int long long 
#define ll long long 
using namespace std;
const int N = 6e5 + 100;

int a , b , n;
int f(int x, int a, int b){
    int bcnn = a * b / __gcd(a,b);
    return x / a + x / b - x / bcnn;
}
signed main(){
    int t = 1;
    cin >> t;
    while (t--){
        cin >> a >> b >> n;
        int l = 1 ,  r = 1e18, res = 0;
        while (l <= r){
            int mid = (l + r) / 2;
            if (f(mid,a,b) >= n){
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        cout << res << "\n";
    }
    return 0;
}
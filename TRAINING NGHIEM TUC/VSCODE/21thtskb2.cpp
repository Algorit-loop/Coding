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
int p[N], k[N];
int res = 0;
void get(int idx, int val, int A, int B){
    if (idx == n + 1){
        if (val >= A) res++;
        return;
    }
    int c = 1;
    for (int i = 0; i <= k[idx]; i++){
        if (!(val <= B / c)) return;
        get(idx + 1, val * c, A, B);
        c = c * p[idx];
    }
}
signed main(){
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> p[i] >> k[i];
    for (int q = 1; q <= 3; q++){
        int A, B;
        cin >> A >> B;
        res = 0;
        get(1,1,A,B);
        cout << res << "\n";
    }
    return 0;   
}
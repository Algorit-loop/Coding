#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 2e5 + 100;
// int get(int n, int luot){
//     if (n == 0) return luot^1;
//     if (dp[n] != -1) return dp[n];
//     int res = luot^1;
//     for (int i = 1; i <= m; i++){
//         if (n >= a[i]){
//             if (get(n - a[i],luot^1) == luot) res = luot;
//         }
//     }
//     return (dp[n] = res);
// }
// int mex(vector <int> v){
//     sort(v.begin(),v.end());
//     v.resize(unique(v.begin(),v.end()) - v.begin());
//     int c = 0;
//     for (int i = 0; i < v.size(); i++){
//         if (c == v[i]) c++;
//     }
//     return c;
// }
// vector <int> factor(int x){
//     vector <int> r;
//     for (int i = 2; i * i <= x; i++){
//         if (x % i == 0){
//             r.push_back(i);
//             while (x % i == 0) x /= i;
//         }
//     }
//     if (x > 1) r.push_back(x);
//     return r;
// }
// string nphan(int x){
//     string res = "";
//     while (x > 0){
//         res = char(x % 2 + 48) + res;
//         x /= 2;
//     }
//     while (res.size() < 10) res = "0" + res;
//     return res;
// }
// void builtgrundy(int n){
//     vector <int> g (n+1,0);
//     for (int i = 0; i <= n; i++){
//         // cout << i << " ?? \n";
//         vector <int> add , f = factor(i);
//         // for (auto x : f) cout << x << " "; cout << "\n";
//         for (auto x : f){
//             if (i - x >= 0) add.push_back(g[i - x]);
//         }
//         g[i] = mex(add);
//     } 
//     for (int i = 0; i <= n; i++) if (i % 2 == 0) cout << (g[i]) << " ";
// } 
int n , a[N], m;
int dp[N] , smax[N];
signed main(){
    cin >> n >> m;
    string s = to_string(n);
    int len = s.size();
    for (int i = 1; i <= len; i++) a[i] = s[i-1] - 48;
    if (m == 2){
        int pos = -1 , u = 10;
        for (int i = 1; i <= len; i++){
            if (a[i] % 2 == 0 && u > a[i]){
                pos = i;
                u = a[i];
            }
        }
        if (pos == -1){
            cout << 0; return 0;
        }
        swap(a[pos],a[len]);
        sort(a + 1,a + len,greater<int>());
        for (int i = 1; i <= len; i++) cout << a[i];
    }
    if (m == 4){
        if (len == 1){
            if (n % m == 0) cout << n;
            else cout << 0;
            return 0;
        }
        int p1 = -1, p2 = -1 , u = 100000;
        int res = 0;
        for (int i = 1; i <= len; i++){
            for (int j = 1; j <= len; j++){
                if (i == j) continue;
                int so = a[i] * 10 + a[j];
                if (so % 4 == 0 && so < u){
                    p1 = i;
                    p2 = j;
                    string v = "";
                    for (int is = 1; is <= len; is++){
                        if (is != p1 && is != p2) v = v + char(a[is] + 48);
                    }
                    sort(v.begin(),v.end(),greater<char>());
                    int tmp = (stoll(v) * 10 + a[p1]) * 10 + a[p2];
                    res = max(res,tmp);
                }
            }
        }
        cout << res;
    }
    if (m == 6){
        int pos = -1 , u = 10, t3 = 0;
        for (int i = 1; i <= len; i++){
            if (a[i] % 2 == 0 && u > a[i]){
                pos = i;
                u = a[i];
            }
            t3 += a[i];
        }
        if (pos == -1 || t3 % 3 != 0){
            cout << 0; return 0;
        }
        swap(a[pos],a[len]);
        sort(a + 1,a + len,greater<int>());
        for (int i = 1; i <= len; i++) cout << a[i];
    }
    if (m == 8){
        if (len == 1){
            if (n % m == 0) cout << n;
            else cout << 0;
            return 0;
        }
        if (len == 2){
            int res = 0;
            if ((a[1] * 10 + a[2]) % 8 == 0) res = max(res,a[1]*10+a[2]);
            if ((a[2] * 10 + a[1]) % 8 == 0) res = max(res,a[2] * 10 + a[1]);
            cout << res;
            return 0;
        }
        int p1 = -1, p2 = -1, p3 = -1 , u = 100000;
        int res = 0;
        for (int i = 1; i <= len; i++){
            for (int j = 1; j <= len; j++){
                for (int k = 1; k <= len; k++){
                    if (i == j || j == k || k == i) continue;
                    int so = a[i] * 100 + a[j] * 10 + a[k];
                    // cout << i << " " << j << " " << k << " " << so << "\n";
                    if (so % 8 == 0 && so < u){
                        p1 = i;
                        p2 = j;
                        p3 = k;
                        string v = "";
                        for (int is = 1; is <= len; is++){
                            if (is != p1 && is != p2 && is != p3) v = v + char(a[is] + 48);
                        }
                        sort(v.begin(),v.end(),greater<char>());
                        int tmp = stoll(v);
                        tmp = (((tmp*10)+a[p1]) * 10 + a[p2])*10+a[p3];
                        res = max(res,tmp);
                    }
                }
            }
        }
        cout << res;
    }
    if (m == 10){
        int p = -1;
        for (int i = 1; i <= len; i++) if (a[i] == 0) p = i;
        if (p == -1) return cout << 0, 0;
        swap(a[p],a[len]);
        sort(a + 1,a + len, greater<int>());
        for (int i = 1; i <= len; i++) cout << a[i];
    }
    return 0;
}
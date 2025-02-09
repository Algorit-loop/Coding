#include <bits/stdc++.h>
#define int long long 
using namespace std;
void __file(){
    if (fopen("input.txt","r")){
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    }
}
const int N = 2e5 + 100;
int a[N] , n , k, q;
int pre[N][10];
signed main(){
    __file();
    cin >> n >> k;
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    // vector <vector<int>> ps(n + 1,vector<int>(n+1,0));
    // for (int i = 1; i <= n; i++) ps[i][i] = 1;
    // for (int i = 1; i <= n - k + 1; i++){
    //     vector <int> vs = ps[i];
    //     for (int j = i; j <= i + k - 1; j++){
    //         for (int g = 1; g <= n; g++){
    //             ps[j][g] -= vs[g];
    //         }
    //     }
    // }
    // for (int i = n - k + 1; i <= n; i++){
    //     for (int j = 1; j <= n; j++){
    //         if (ps[i][j] != 0){
    //             if (ps[i][j] > 0) cout << "+"; else cout << "-";
    //             cout << abs(ps[i][j]) << "a[" << j << "]\n";
    //         }
    //     }
    //         cout << "----\n";
    // }
    for (int p = 0; p < k; p++){
        for (int i = 1; i <= n; i++){
            pre[i][p] = pre[i - 1][p];
            if (i % k == p) pre[i][p] += a[i];
        }
    }
    cin >> q;
    while (q--){
        int l , r;
        cin >> l >> r;
        
        bool ck = true;
        // vector <vector<int>> ps(n + 1,vector<int>(n+1,0));
        // for (int i = l; i <= r; i++) ps[i][i] = 1;
        // for (int i = l; i <= r - k + 1; i++){
        //     vector <int> vs = ps[i];
        //     for (int j = i; j <= i + k - 1; j++){
        //         for (int g = l; g <= r; g++){
        //             ps[j][g] -= vs[g];
        //         }
        //     }
        // }
        // for (int i = r - k + 1; i <= r; i++){
        //     for (int j = l; j <= r; j++){
        //         if (ps[i][j] != 0){
        //             if (ps[i][j] > 0) cout << "+"; else cout << "-";
        //             cout << abs(ps[i][j]) << "a[" << j << "]\n";
        //         }
        //     }
        //         cout << "----\n";
        // }
        // for (int i = r - k + 2; i <= r; i++){
        //     int tg = 0;
        //     for (int j = l; j <= i; j++){
        //         tg += ps[i][j] * a[j];
        //     }
        //     if (tg != 0) ck = false;
        // }
        // cout << "\n";
        l--;
        for (int i = r - k + 2; i <= r; i++){
            int tg = pre[i][i%k] - pre[l][i%k];
            int c = r - k + 1;
            tg -= (pre[c][c%k] - pre[l][c%k]);
            if (tg != 0) ck = false;
            // cout << tg << " ";
        }
        if (ck) cout << "Yes\n"; else cout << "No\n";
    }
    return 0;
}
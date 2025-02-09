#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
ll sumdiv(ll n){
    ll sum = 0;
    for (ll i = 1; i * i <= n; i++){
        if (n % i == 0){
            sum += i;
            if (i != n / i) sum += n / i;
        }
    }
    return sum;
}
int main()
{
    cout << "Nhap N = ";
    cin >> n;
    cout << "Cac so hoan hao khong vuot qua N la: ";
    for (int i = 1; i <= n; i++){
        if (sumdiv(i) == i * 2) cout << i << " ";
    }
    return 0;
}

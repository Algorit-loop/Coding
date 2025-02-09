#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#define ll long long

using namespace std;
#ifndef _CLOCK_T
#define _CLOCK_T
// typedef __darwin_clock_t clock_t;
#endif /* _CLOCK_T */
ll pr[8] = {2,3,5,7,11,13,17,19};
pair <ll,ll> factor(ll x){
    ll s = 0;
    while (!(x & 1)){
        s++;
        x >>= 1;
    }
    return make_pair(s,x);
}
ll mul(ll x,ll y,ll mod){
    ll res = 0;
    x = x % mod;
    while (y > 0){
        if (y & 1) res = (res + x) % mod;
        y >>= 1;
        x = (x + x) % mod;
    }
    return res;
}
ll power(ll x,ll y,ll mod){
    ll res = 1;
    x = x % mod;
    while (y > 0){
        if (y & 1) res = mul(res,x,mod);
        y >>= 1;
        x = mul(x,x,mod);
    }
    return res;
}
bool Test(ll s,ll d,ll n,ll a){
    if (n == a) return true;
    ll p = power(a,d,n);
    if (p == 1) return true;
    for (; s > 0; s--){
        if (p == n - 1) return true;
        p = mul(p,p,n);
    }
    return false;
}
bool Miller(ll n){
    if (n < 2) return false;
    if (!(n & 1)) return n == 2;
    pair <ll,ll> tmp = factor(n - 1);
    bool check = true;
    for (int i = 0; i < 8; i++)
        check = check & Test(tmp.first,tmp.second,n,pr[i]);
    return check;
}
ll gcd(ll a,ll b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}
long long Rand(long long l, long long h)
{
    return l + ((long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) +
                rand()) % (h - l + 1);
}
ll pollard_rho(ll n) {
    ll x = Rand(2,n-1);//  rand() % (n - 2) + 2; // 2 -> (n - 1)
    ll y = x;
    ll c = Rand(1,n-1); // rand() % (n - 1) + 1; // 1 -> (n - 1)
    ll d = 1;
    while (d == 1) {
        x = ((long long)(x * x + c) % n);
        y = ((long long)(y * y + c) % n);
        y = ((long long)(y * y + c) % n);
        d = gcd(abs(x - y), n);
        if (d == n) {
            return pollard_rho(n);
        }
    }
    return d;
}
vector<ll> factor_prime(ll n){
    vector <ll> res;
    while (n % 2 == 0){
        res.push_back(2);
        n /= 2;
    }
    while (n % 3 == 0){
        res.push_back(3);
        n /= 3;
    }
    while (n > 1){
        if (Miller(n)){
            res.push_back(n);
            return res;
        }
        ll p = pollard_rho(n);
        while (Miller(p) == false) p = pollard_rho(p);
        while (n % p == 0){
            res.push_back(p);
            n /= p;
        }
    }
    return res;
}
int main() {
    /*ll n = 123456789;
    ll factor = pollard_rho(n);
    cout << "One of the factors of " << n << " is " << factor << endl;*/

    srand(time(NULL));
    int test = 100000;;
    clock_t st_fn = clock();
    while (test--){
        ll n = Rand(1,1e9);
        clock_t st = clock();
        vector <ll> ft = factor_prime(n);
        clock_t en = clock();
        ll res = 1;
        for (auto x : ft) res = res * x;
        if (res != n){
            //cout << "Error !!! ";
        }
        else{
            //cout << "Accept ";
        }
        //cout << "[ " << (double)(en - st) / CLOCKS_PER_SEC << " ]\n";
    }
    clock_t en_fn = clock();
    cout << "[ " << (double)(en_fn - st_fn) / CLOCKS_PER_SEC << " ]\n";
    return 0;
}

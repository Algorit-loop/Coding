#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5;
int lp[N + 2],pr[N],cnt =0 ;
void sieve(int lim){
  for (int i = 2; i <= N; i++){
    if (lp[i]==0) lp[i] = pr[++cnt] = i;
    int j = 1;
    while (j <= cnt && pr[j] <= lp[i] && pr[j] * i <= lim){
      lp[pr[j] * i] = pr[j];
      j++;
    }
  }
}
const ll INF = 1e9;
int dem[N + 5];
int main()
{
    sieve(N);
    dem[1] = INF-1;
    for (int i = 1; i <= N; i++) dem[i] = INF;
    for (int i = 1; i <= cnt; i++){
      ll fw = pr[i];
      while (fw <= N){
        ll g = fw - fw / pr[i];
        fw = fw * pr[i];
        if (g == 1) continue;
        dem[g] = pr[i];
        for (int j = N / g; j >= 1; j--){
          assert(j*g <= N);
          if (dem[j] < INF) dem[j * g] = min(dem[j * g],pr[i]);
        }
      }
    }
    for (int i = 1; i <= N; i++){
      if (dem[i] < INF) cout << i << " -> " << dem[i] << "\n";
    }
    return 0;
}

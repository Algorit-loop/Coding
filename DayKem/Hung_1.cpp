#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int N = 2e5 + 100;
void file(string f){
    if (fopen((f + ".inp").c_str(),"r")){
        freopen((f + ".inp").c_str(),"r",stdin);
        freopen((f + ".out").c_str(),"w",stdout);
    }
}
int n , m;
vector<pair<int,int>> adj[N];
typedef pair<pair<int,int>,int> node;
void solve(){
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    priority_queue <node,vector<node>,greater<node>> heap;
    heap.push({{0,0},1});
    vector <int> d(n + 10,1e18);
    d[1] = 0;
    while (!heap.empty()){
        auto f = heap.top(); heap.pop();
        int fdu = f.first.first, fmax = f.first.second, u = f.second;
        if (fdu != d[u]) continue;
        // cout << u << " -> ";
        for (auto R : adj[u]){
            int v = R.first , w = R.second;
            // cout << v << " ";
            if (d[v] > fdu + w - max(fmax,w) + fmax){
                d[v] = fdu + w - max(fmax,w) + fmax;
                heap.push({{d[v],max(fmax,w)},v});
            }
        }
        // cout << "\n";
    }
    if (d[n] != 1e18) cout << d[n]; 
    else cout << "-1\n";
}
signed main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    file("txt");
    int t = 1;
    // cin >> t;
    while (t--){
        solve();
    }
    return 0;
}
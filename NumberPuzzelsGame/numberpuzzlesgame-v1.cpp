#include <bits/stdc++.h>
#define int long long
#define ll long long 
using namespace std;
void file(string f){
    if (fopen((f + ".INP").c_str(),"r")){
        freopen((f + ".INP").c_str(),"r",stdin);
        freopen((f + ".OUT").c_str(),"w",stdout);
    }
}
const int N = 1e6 + 100;
const int mod = 1e9 + 7;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}
int f[N];
int F(int x){
    for (int i = 1; i <= x; i++){
        if (x % i != 0){
            return f[i] + 1;
        }
    }
    return -1;
}
int bru(int l, int r){
    int res = 0;
    for (int i = l; i <= r; i++) res += f[i];
    return res;
}
int t(int x){
    return x / 2 + (x % 2);
}
int kf(int x){
    return x / 2;
}
int get(int l, int r){
    int c1 = t(r) - t(l - 1);
    int c2 = kf(r) - kf(l - 1);
    int pl = l / 6; if (l % 6 > 0) pl++;
    int pr = r / 6;
    int c3 = t(pr) - t(pl - 1);
    return c1 + (c2 - c3) * 2 + c3 * 3;
}
int a[100][100] , b[100][100];
int n = 4;
map <vector<int>,vector<int>> mps;
vector <int> get(vector<vector<int>> c){
    vector <int> v;
    for (int i = 0; i < c.size(); i++){
        for (int j = 0; j < c.size(); j++){
            v.push_back(c[i][j]);
        }
    }
    return v;
}
vector<vector<int>> ff(int z){
    vector<vector<int>> res(n,vector<int>(n,0));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (z == 0) res[i][j] = a[i][j];
            else res[i][j] = b[i][j];
        }
    }
    return res;
}
// type = 1 | left
// type = 2 | right 
// type = 3 | up 
// type = 4 | down 
vector <vector<int>> trace;
void printmatrixtrace(vector <int> v){
    for (int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
        if (i % n == n - 1) cout << "\n";
    }
}
bool find_ed = 0;
int d = 0;
// void backtracking(int x, int y, int type){
//     // printmatrixtrace(get(0));
//     // cout << "------------ \n";
//     // d++;
//     // if (d >= 10) return;
//     trace.push_back(get(0));
//     if (get(0) == get(1)){
//         find_ed = 1;
//         for (auto G : trace){
//             printmatrixtrace(G);
//             cout << "-------------\n";
//         }
//         return;
//     }
//     mps[get(0)] = 1;
//     for (int i = 1; i <= 4; i++){
//         if (find_ed == 1) return;
//         if (i == type) continue;
//         if (i == 3 && x - 1 >= 1){
//             swap(a[x][y],a[x - 1][y]);
//             if (mps[get(0)] == 0)
//                 backtracking(x - 1,y,4);
//             swap(a[x][y],a[x - 1][y]);
//         }

//         if (i == 4 && x + 1 <= n){
//             swap(a[x][y],a[x + 1][y]);
//             if (mps[get(0)] == 0)
//                 backtracking(x + 1,y,3);
//             swap(a[x][y],a[x + 1][y]);
//         }

//         if (i == 1 && y - 1 >= 1){
//             swap(a[x][y],a[x][y - 1]);
//             if (mps[get(0)] == 0)
//                 backtracking(x,y - 1,2);
//             swap(a[x][y],a[x][y - 1]);
//         }

//         if (i == 2 && y + 1 <= n){
//             swap(a[x][y],a[x][y + 1]);
//             if (mps[get(0)] == 0)
//                 backtracking(x,y + 1,1);
//             swap(a[x][y],a[x][y + 1]);
//         }
//     }
//     trace.pop_back();
// }
int CountPointTrue(vector<int> a, vector<int> b){
    assert(a.size() == b.size());
    int d = 0;
    for (int i = 0; i < a.size(); i++){
        if (a[i] == b[i]) d++;
    }
    return d;
}
struct node{
    int x,y;
    vector<vector<int>> f;
    int type;
};
void BFS(int xx, int yy){
    queue <node> q;
    node st;
    st.x = xx; st.y = yy; 
    st.f = ff(0); st.type = 0;
    q.push(st);
    vector<int> kaka = {-1};
    mps[get(st.f)] = kaka;
    // printmatrixtrace(get(st.f));
    while (!q.empty()){
        node tp = q.front(); q.pop();
        int new_x = tp.x , new_y = tp.y;
        auto new_f = tp.f; int new_type = tp.type;
        if (new_f == ff(1)){
            cout << "Truy vet\n";
            auto H = get(new_f);
            vector<vector<int>> trace;
            while (H.size() > 1){
                trace.push_back(H);
                H = mps[H];
            }
            reverse(trace.begin(),trace.end());
            for (auto G : trace){
                cout << "CPT = " << CountPointTrue(get(ff(1)),G) << "\n";
                printmatrixtrace(G);
                cout << "---------\n";
            }
            return;
        }
        // ------------ 
        for (int i = 1; i <= 4; i++){
            if (i == 1 && new_y - 1>= 0){
                auto new_c = new_f;
                swap(new_c[new_x][new_y],new_c[new_x][new_y - 1]);
                if (!mps[get(new_c)].empty()) continue;
                node new_node;
                new_node.x = new_x, new_node.y = new_y - 1, new_node.f = new_c, new_node.type = 2;
                mps[get(new_c)] = get(new_f);
                q.push(new_node);
            }
            if (i == 2 && new_y + 1 < n){
                auto new_c = new_f;
                swap(new_c[new_x][new_y],new_c[new_x][new_y + 1]);
                if (!mps[get(new_c)].empty()) continue;
                node new_node;
                new_node.x = new_x, new_node.y = new_y + 1, new_node.f = new_c, new_node.type = 1;
                mps[get(new_c)] = get(new_f);
                q.push(new_node);
            }
            if (i == 3 && new_x - 1 >= 0){
                auto new_c = new_f;
                swap(new_c[new_x][new_y],new_c[new_x - 1][new_y]);
                if (!mps[get(new_c)].empty()) continue;
                node new_node;
                new_node.x = new_x - 1, new_node.y = new_y, new_node.f = new_c, new_node.type = 4;
                mps[get(new_c)] = get(new_f);
                q.push(new_node);
            }
            if (i == 4 && new_x + 1 < n){
                auto new_c = new_f;
                swap(new_c[new_x][new_y],new_c[new_x + 1][new_y]);
                if (!mps[get(new_c)].empty()) continue;
                node new_node;
                new_node.x = new_x + 1, new_node.y = new_y, new_node.f = new_c, new_node.type = 3;
                mps[get(new_c)] = get(new_f);
                q.push(new_node);
            }
        }
        
        // ------------
    }
}
void solve(){
    int px = 0 , py = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> a[i][j];
            if (a[i][j] == 0) px = i , py = j;
        }
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b[i][j] = (i * n + j) % (n * n);
        }
    }
    // ---------- process -----------
    // backtracking(px,py,0);
    clock_t st = clock();
    BFS(px,py);
    clock_t en = clock();
    cout << mps.size() << "\n";
    cout << "Time: " << (double)(en - st) << "ms\n";
    // ------------------------------
}
signed main(){
    file("txt");
    int t = 1;
    // cin >> t;
    while (t--){
        solve();
    }
    return 0;
}

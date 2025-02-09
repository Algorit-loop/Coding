#include <bits/stdc++.h>
#include <random>
#include <time.h>
#define int long long 
#define ll long long 
#define fi first 
#define se second
#define ii pair<int,int>
using namespace std;
void file(string f){
    if (fopen((f + ".INP").c_str(),"r")){
        freopen((f + ".INP").c_str(),"r",stdin);
        freopen((f + ".OUT").c_str(),"w",stdout);
    }
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}
const int N = 2e5 + 100;
const int mod = 1e9 + 7;
int dist(ii a, ii b){
    int f = (a.fi - b.fi); f = f * f;
    int g = (a.se - b.se); g = g * g;
    return f + g;
}
// type = 1 | left 
// tyep = 2 | right
// type = 3 | up 
// type = 4 | down
#define matrix vector<vector<int>> 
struct node{
    int cost = 0;
    int x = 0, y = 0;
    matrix f;
    bool operator < (const node &u) const {
        return this->cost < u.cost;
    }
};
const int n = 9;
matrix a,b;
const int base = 31;
int dx[4] = {0,0,-1,1};
int dy[4] = {-1,1,0,0};
int Hashing(matrix a){
    int res = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            res = (res * base + (a[i][j] + 1));
        }
    }
    return res;
}
int Heuristics(matrix &a, matrix &b){
    vector<ii> c(n*n,{0,0});
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            c[a[i][j]] = {i,j};
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (b[i][j] != 0)
                res = res + abs(i - c[b[i][j]].first) + abs(j - c[b[i][j]].second);
        }
    }
    return res;
}
map <int,pair<int,int>> mps;
void printmatrix(matrix a){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << a[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "---------\n";
}
string ftr[5] = {"","left","right","up","down"};
matrix Lock = matrix (n,vector<int>(n,0));
bool compairmatrix(matrix a, matrix b){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (a[i][j] != b[i][j]) return false;
        }
    }
  return true;
}
pair <int,int> FindEmpty(matrix &a){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (a[i][j] == 0) return make_pair(i,j);
        }
    }
    assert(0);
    return make_pair(-1,-1);
}
pair <int,int> FindVal(matrix &a,int x){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (a[i][j] == x) return make_pair(i,j);
        }
    }
    assert(0);
    return make_pair(-1,-1);
}
bool MoveXYUV(matrix &a, int x, int y, int u, int v, int notx, int noty){
    pair<int,int> p = {x,y};
    map <ii,ii> md;
    queue <ii> q;
    q.push(p);
    md[p] = {-1,-1};
    while (!q.empty()){
        auto TP = q.front(); q.pop();
        int rx = TP.first , ry = TP.second;
        if (rx == u && ry == v){
            auto fx = make_pair(u,v);
            vector<pair<int,int>> trace;
            while (fx.first != -1 && fx.second != -1){
                trace.push_back(fx);
                fx = md[fx];
            }
            trace.pop_back();
            reverse(trace.begin(),trace.end());
            for (auto z : trace){
                swap(a[x][y],a[z.first][z.second]);
                x = z.first;
                y = z.second;
                // cout << z.first << " " << z.second << "\n";
            }
            // printmatrix(a);
            return true;
        }
        for (int i = 0; i < 4; i++){
            int ru = rx + dx[i] , rv = ry + dy[i];
            if (ru >= 0 && ru < n && rv >= 0 && rv < n && !md.count(make_pair(ru,rv))
                        && Lock[ru][rv] == 0 && make_pair(ru,rv) != make_pair(notx,noty)){
                q.push(make_pair(ru,rv));
                md[make_pair(ru,rv)] = TP;
            }
        }
    }
    return false;
}
bool MoveLeft(matrix &a, int x, int y){
    auto PE = FindEmpty(a);
    auto GO = MoveXYUV(a,PE.first,PE.second,x,y - 1,x,y);
    if (GO){
        swap(a[x][y],a[x][y - 1]);
        return true;
    }
    return false;
}
bool MoveRight(matrix &a, int x, int y){
    auto PE = FindEmpty(a);
    auto GO = MoveXYUV(a,PE.first,PE.second,x,y + 1,x,y);
    if (GO){
        swap(a[x][y],a[x][y + 1]);
        return true;
    }
    return false;
}
bool MoveUp(matrix &a, int x, int y){
    auto PE = FindEmpty(a);
    auto GO = MoveXYUV(a,PE.first,PE.second,x - 1,y,x,y);
    if (GO){
        swap(a[x - 1][y],a[x][y]);
        return true;
    }
    return false;
}
bool MoveDown(matrix &a, int x, int y){
    auto PE = FindEmpty(a);
    auto GO = MoveXYUV(a,PE.first,PE.second,x + 1,y,x,y);
    if (GO){
        swap(a[x + 1][y],a[x][y]);
        return true;
    }
    return false;
}
int ValueBox(int x, int y){
    return (x * n + y + 1) % (n * n);
}
bool SolveLockBox(matrix &a, int x, int y, int rx, int ry){
    pair<int,int> pos = FindVal(a,ValueBox(rx,ry));
    // Process
    for (int times = 1; times <= 2; times++){
        while (pos.second > y){
            auto ok = MoveLeft(a,pos.first,pos.second);
            if (!ok) break;
            pos.second--;
        }
        while (pos.second < y){
            auto ok = MoveRight(a,pos.first,pos.second);
            if (!ok) break;
            pos.second++;
        }
        while (pos.first > x){
            auto ok = MoveUp(a,pos.first,pos.second);
            if (!ok) break;
            pos.first--;
        }
        while (pos.first < x){
            auto ok = MoveDown(a,pos.first,pos.second);
            if (!ok) break;
            pos.first++;
        }
    }
    
    
    // Haven't MoveDown [DAN VL]
    if (pos.first != x || pos.second != y){
        // cout << "NGU | Khong LockBox duoc\n";
        cout << "Truong hop kho'\n";
        return false;
    }
    return true;
    // assert(pos.first == x && pos.second == y);
}
void BFS(matrix &a, int x, int y, int u, int v){
    // cout << x << " " << u << " | x\n";
    // cout << y << " " << v << " | y\n";
    map <int,pair<int,int>> mhs;
    auto PE = FindEmpty(a);
    matrix Ar = a;
    pair<pair<int,int>,matrix> nd = {{PE.first,PE.second},Ar};
    queue <pair<pair<int,int>,matrix>> q;
    // cout << nd.first.first << " " << nd.first.second << " PP\n";
    q.push(nd);
    mhs[Hashing(Ar)] = {-1,-1};
    while (!q.empty()){
        auto TP = q.front(); q.pop();
        int rx = TP.first.first , ry = TP.first.second;
        int HashTP = Hashing(TP.second);
        if (TP.second[x][y] == ValueBox(x,y) && TP.second[x][y+1] == ValueBox(x,y+1)){
            pair<int,int> deck = make_pair(HashTP,0);
            vector <int> trace;
            while (deck != make_pair(-1LL,-1LL)){
                trace.push_back(deck.second);
                deck = mhs[deck.first];
            }
            cout << "Trace BFS\n";
            reverse(trace.begin(),trace.end());
            trace.pop_back();
            int px = nd.first.first , py = nd.first.second;
            for (auto r : trace){
                int new_px = px + dx[r - 1];
                int new_py = py + dy[r - 1];
                swap(a[px][py],a[new_px][new_py]);
                px = new_px;
                py = new_py;
                cout << ftr[r] << "\n";
            }
            return;
        }
        for (int i = 0; i < 4; i++){
            int ru = rx + dx[i];
            int rv = ry + dy[i];
            if (ru >= x && ru <= u && rv >= y && rv <= v){
                pair<pair<int,int>,matrix> add;
                add.second = TP.second;
                swap(add.second[rx][ry],add.second[ru][rv]);
                int Hadd = Hashing(add.second);
                if (!mhs.count(Hadd)){
                    mhs[Hadd] = {HashTP,i+1};
                    add.first.first = ru;
                    add.first.second = rv;
                    q.push(add);
                }
            }
        }
    }
    cout << "NGU\n";
    exit(0);
}
void ProgressiveLocking(matrix &a){
    for (int i = 0; i < n - 2; i++){
        for (int j = 0; j < n - 2; j++){
            bool ok = SolveLockBox(a,i,j,i,j);
            if (!ok){
                cout << "Toang\n";
                return;
            }
            Lock[i][j] = true;
        }
        bool ok = SolveLockBox(a,i+2,n-1,i,n-1);
        if (!ok) return;
        Lock[i+2][n-1] = true;
        ok = SolveLockBox(a,i+2,n-2,i,n-2);
        if (!ok){
            Lock[i+2][n-1] = false;
            BFS(a,i,n-2,i+2,n-1);
        } else {
            Lock[i+2][n-2] = true;
            auto PE = FindEmpty(a);
            bool ok = MoveXYUV(a,PE.first,PE.second,i+1,n-2,-1,-1);
            if (!ok){
                cout << "NGU\n";
                assert(0);
                return;
            }
            Lock[i+2][n-1] = false;
            Lock[i+2][n-2] = false;
            BFS(a,i,n-2,i+2,n-1);
        }
        Lock[i][n-1] = Lock[i][n-2] = true;
    }
}
void Astar(){
    // f(n) = g(n) + h(n)
    auto PE = FindEmpty(a);
    int px = PE.first, py = PE.second;
    priority_queue<pair<int,node>,vector<pair<int,node>>,greater<pair<int,node>>> q;
    mps[Hashing(a)] = {-1,-1};
    node gf; gf.x = px, gf.y = py, gf.f = a; gf.cost = 0;
    q.push({gf.cost + Heuristics(a,b),gf});
    int HashB = Hashing(b);
    while (!q.empty()){
        auto TP = q.top(); q.pop();
        int x = TP.second.x , y = TP.second.y;
        int gn = TP.second.cost;
        matrix maTP = TP.second.f;
        // printmatrix(maTP);cout <<"---\n";
        // if (!compairmatrix(maTP,TP.second.f)) cout << "cac\n";
        int HashTP = Hashing(maTP);
        // cout << HashTP << " ? " << HashB << "\n";
        if (HashTP == HashB 
                      // || compairmatrix(a,b) == true
                                                        ){
            cout << gn << "\n";
            vector<pair<int,int>> trace;
            pair<int,int> deck = {HashTP,0};
            while (deck != make_pair(-1LL,-1LL)){
                trace.push_back(deck);
                deck = mps[deck.first];
            }
            reverse(trace.begin(),trace.end());
            for (auto x : trace){
                cout << ftr[x.second] << "\n";
            }
            printmatrix(maTP);
            
            return;
        }
        for (int i = 1; i <= 4; i++){
            if (i == 1 && y - 1 >= 0 && Lock[x][y - 1] == 0){
                node new_node;
                new_node.cost = gn + 1;
                new_node.x = x;
                new_node.y = y - 1;
                new_node.f = maTP;
                swap(new_node.f[x][y], new_node.f[x][y - 1]);
                int Hash_newnode = Hashing(new_node.f);
                if (!mps.count(Hash_newnode)){
                    mps[Hash_newnode] = {HashTP,1};
                    int fn = Heuristics(new_node.f,b);
                    q.push({fn,new_node});
                }
            }
            if (i == 2 && y + 1 < n && Lock[x][y + 1] == 0){
                node new_node;
                new_node.cost = gn + 1;
                new_node.x = x;
                new_node.y = y + 1;
                new_node.f = maTP;
                swap(new_node.f[x][y], new_node.f[x][y + 1]);
                int Hash_newnode = Hashing(new_node.f);
                if (!mps.count(Hash_newnode)){
                    mps[Hash_newnode] = {HashTP,2};
                    int fn = Heuristics(new_node.f,b);
                    q.push({fn,new_node});
                }
            }
            if (i == 3 && x - 1 >= 0 && Lock[x - 1][y] == 0){
                node new_node;
                new_node.cost = gn + 1;
                new_node.x = x - 1;
                new_node.y = y;
                new_node.f = maTP;
                swap(new_node.f[x][y], new_node.f[x - 1][y]);
                int Hash_newnode = Hashing(new_node.f);
                if (!mps.count(Hash_newnode)){
                    mps[Hash_newnode] = {HashTP,3};
                    int fn = Heuristics(new_node.f,b);
                    q.push({fn,new_node});
                }
            }
            if (i == 4 && x + 1 < n && Lock[x + 1][y] == 0){
                node new_node;
                new_node.cost = gn + 1;
                new_node.x = x + 1;
                new_node.y = y;
                new_node.f = maTP;
                swap(new_node.f[x][y], new_node.f[x + 1][y]);
                int Hash_newnode = Hashing(new_node.f);
                if (!mps.count(Hash_newnode)){
                    mps[Hash_newnode] = {HashTP,4};
                    int fn = Heuristics(new_node.f,b);
                    q.push({fn,new_node});
                }
            }
        }
    }
    cout << mps.size() << "\n";
    cout << "what\n";
    // 181440
}
bool check(matrix a){
    vector<int> cc(n*n,0);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cc[a[i][j]]++;
        }
    }
    for (int i = 0; i < n * n; i++) if (cc[i] != 1) return false;
    return true;
}
void solve(){
    a.assign(n,vector<int>(n,0));
    b.assign(n,vector<int>(n,0));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    int d = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            d++;
            b[i][j] = d % (n * n);
        }
    }
    if (check(a) == false){
        cout << "Dien sai roi\n";
        return;
    }
    // printmatrix(a); printmatrix(b);
    clock_t st = clock();
    printmatrix(a);
    // ----- Test Function -----
    // SolveLockBox(a,0,1); [OK]
    // ProgressiveLocking(a); // [Yet OK] [OK wiht (n-2)x(n-2)]
    printmatrix(Lock);
    printmatrix(a);
    Astar();
    // MoveXYUV(a,5,5,3,3,4,3);
    // auto pos = FindVal(a,3);
    // MoveLeft(a,pos.first,pos.second); [OK]
    // pos = FindVal(a,3);
    // MoveLeft(a,pos.first,pos.second); [OK]
    // pos = FindVal(a,3);
    // MoveUp(a,pos.first,pos.second); [OK]
    clock_t en = clock();
    cout << "Time: " << (double)(en - st) << "ms\n";
}
signed main(){
    srand(time(NULL));
    ios::sync_with_stdio(false); cin.tie(NULL);
    file("txt");    
    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; _++) solve();
    return 0;
}
    
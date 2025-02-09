#include <bits/stdc++.h>
#include <random>
#include <time.h>
#define int long long
#define ll long long 
#define fi first 
#define se second
#define ii pair<int,int>
using namespace std;
void __file(){
    if (fopen("input.txt","r")){
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    }
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}
const int N = 1e6 + 100;
const int mod = 1e9 + 7;
int dist(ii a, ii b){
    int f = (a.fi - b.fi); f = f * f;
    int g = (a.se - b.se); g = g * g;
    return f + g;
}

bool cphuong(ll x){
    int u = sqrt(x);
    return u * u == x;
}
int power(int a, int b, int c){
    int res = 1;
    a = a % c;
    for (; b > 0; b >>= 1 , a = a * a % c){
        if (b & 1) res = res * a % c;
    }
    return res;
}
struct Node {
    long long value; // Giá trị lưu trữ tại nút
    Node(long long v = 1e9) : value(v) {}
    
    // Merge hai nút (tuỳ vào bài toán, có thể thay đổi logic)
    void merge(const Node& left, const Node& right) {
        value = min(left.value,right.value); // Ví dụ: Tổng các giá trị
    }
};

struct SegmentTree {
    int n;
    vector<Node> tree;

    SegmentTree(int size) {
        n = size;
        tree.resize(4 * n);
    }

    // Update giá trị tại vị trí idx
    void update(int idx, long long val, int node, int start, int end) {
        if (start == end) {
          assert(start == idx);
            tree[node] = Node(val); // Cập nhật nút lá
        } else {
            int mid = (start + end) / 2;
            int left = 2 * node + 1, right = 2 * node + 2;
            if (idx <= mid) {
                update(idx, val, left, start, mid);
            } else {
                update(idx, val, right, mid + 1, end);
            }
            tree[node].merge(tree[left], tree[right]); // Gộp kết quả từ hai con
        }
    }
    void update_PT(int idx, long long val, int node, int start, int end) {
        // cout << "???\n";
        if (start == end) {
            assert(start == idx);
            int E1 = tree[node].value;
            // cout << "update " << tree[node].value << " " << val << "\n";
            tree[node].value = min(E1,val); // Cập nhật nút lá
        } else {
            int mid = (start + end) / 2;
            int left = 2 * node + 1, right = 2 * node + 2;
            if (idx <= mid) {
                update_PT(idx, val, left, start, mid);
            } else {
                update_PT(idx, val, right, mid + 1, end);
            }
            tree[node].merge(tree[left], tree[right]); // Gộp kết quả từ hai con
        }
    }

    // Query đoạn [l, r]
    Node query(int l, int r, int node, int start, int end) {
        if (l > r) return Node(1e9);
        if (l > end || r < start) {
            return Node(1e9); // Phần tử trung lập (tổng là 0, min/max cần thay đổi)
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left = 2 * node + 1, right = 2 * node + 2;
        Node leftNode = query(l, r, left, start, mid);
        Node rightNode = query(l, r, right, mid + 1, end);
        Node result;
        result.merge(leftNode, rightNode);
        return result;
    }

    // Interface đơn giản để gọi update và query
    void update(int idx, long long val) {
        update(idx, val, 0, 0, n - 1);
    }
    void update_2(int idx, long long val) {
        update_PT(idx, val, 0, 0, n - 1);
    }

    long long query(int l, int r) {
        return query(l, r, 0, 0, n - 1).value;
    }
};
int chuyen(char x){
    if (x == 'R') return 1;
    if (x == 'G') return 2;
    if (x == 'B') return 3;
    assert(0);
}

int pos[10] , k, n, f[N];
char a[N];
int cost(int x, int k){
    return x / k + (x % k > 0);
}
int p[N];
int brute(){
    a[0] = 'B';
    for (int i = 1; i <= n; i++) p[i] = 1e9;
    for (int i = 1; i <= n; i++){
        for (int j = i - 1; j >= 0; j--){
            if (a[i] == 'R' && a[j] == 'B')
                p[i] = min(p[i],p[j] + cost(i - j - 1,k));
            if (a[i] == 'G' && a[j] == 'R')
                p[i] = min(p[i],p[j] + cost(i - j - 1,k));
            if (a[i] == 'B' && a[j] == 'G')
                p[i] = min(p[i],p[j] + cost(i - j - 1,k));
        }
    }
    int res = 1e9;
    for (int i = 0; i <= n; i++) 
        if (a[i] == 'B') res = min(res,p[i] + cost(n - i,k));
    return res;
}
char ccc(int x){
    if (x == 1) return 'R';
    if (x == 2) return 'G';
    if (x == 3) return 'B';
}
int ok = 0;
void solve(){
    cin >> n >> k;
    // n = 10 , k = range(1,5);
    for (int i = 1; i <= n; i++){
        // a[i] = ccc(range(1,3));
        cin >> a[i];
    }
    // a[n/2] = 'G';
    SegmentTree tR(n+10) , tG(n+10), tB(n+10);
    for (int i = 0; i <= n + 7; i++){
        tR.update(i,1e9);
        tG.update(i,1e9);
        tB.update(i,1e9);
    }
    f[0] = 0;
    tB.update(0 % k,f[0] - 0 / k);
    // cout << tB.query(0,0) << "\n";
    for (int i = 1; i <= n; i++){
        f[i] = 1e9;
        if (a[i] == 'R'){
            int x = (i - 1) % k;
            int w1 = tB.query(0,x-1) + (i - 1) / k + 1;
            int w2 = tB.query(x,k-1) + (i - 1) / k;
            // cout << x << " " << k-1 << "\n";
            // cout << "w1 " << w1 << "\n"; cout << "w2 " << w2 << "\n";
            f[i] = min(w1,w2);
            tR.update_2(i % k,f[i] - i / k);
        }
        if (a[i] == 'G'){
            int x = (i - 1) % k;
            int w1 = tR.query(0,x-1) + (i - 1) / k + 1;
            int w2 = tR.query(x,k-1) + (i - 1) / k;
            f[i] = min(w1,w2);
            tG.update_2(i % k,f[i] - i / k);
        }
        if (a[i] == 'B'){
            int x = (i - 1) % k;
            int w1 = tG.query(0,x-1) + (i - 1) / k + 1;
            int w2 = tG.query(x,k-1) + (i - 1) / k;
            f[i] = min(w1,w2);
            tB.update_2(i % k,f[i] - i / k);
        }
        // cout << tB.query(0,0) << " " << i << " ??\n";
    }
    int res = 1e9;
    for (int i = 1; i <= n; i++){
        // cout << f[i] << " "; 
        if (a[i] == 'B'){
            res = min(res, f[i] + cost(n - i,k));
        }
    }
    // for (int i = 1; i <= n; i++) cout << f[i] << " "; cout << "\n";
    // cout << res << "\n";
    res = min(res,cost(n,k));
    cout << res << "\n";
    // int ff = brute();
    // cout << res << " " << ff << "\n";
    // if (res == ff) ok++;
    // else{
    //     cout << res << " " << ff << "\n";
    //     cout << n << " " << k << "\n";
    //     for (int i = 1; i <= n; i++) cout << a[i] << " "; cout << "\n";
    // }
    // cout << res << "\n";
    
}
signed main(){
    srand(time(NULL));
    ios::sync_with_stdio(false); cin.tie(NULL);
    __file();       
    int t = 1;
    // cin >> t;
    for (int _ = 1; _ <= t; _++) solve();
    // cout << ok << " / " << t << "\n";
    // int ok = 0;
    // for (int i = 1; i <= 10000; i++){
    //     int a = range(1,1000) , b = range(a,1000);
    //     int c = range(1,1000);
    //     int x1 = cost(b - a,c);
    //     int x2 = b / c - a / c + (a % c < b % c);
    //     cout << x1 << " " << x2 << "\n";
    //     if (x1 == x2) ok++;
    // }
    // cout << ok << " / " << 10000;
    return 0;
}
    // int n; cin >> n;
    // int ok = 0;
    // for (int T = 1; T <= n; T++){
    //     for (int i = 1; i <= 3; i++) d[i] = 0;
    //     int x = rand() % 3 + 1;
    //     vector <int> v;
    //     d[x] = 1;
    //     int choose = rand() % 3 + 1;
    //     for (int i = 1; i <= 3; i++){
    //         if (d[i] == 0 && i != choose) v.push_back(i);
    //     }
    //     int open = v[rand() % (int)v.size()];
    //     cout << v.size() << "\n";
    //     // for (int i = 1; i <= 3; i++){
    //     //     if (i != choose && i != open) choose = i;
    //     // }
    //     if (d[choose] == 1) ok++;
    // }
    // cout << ok << " / " << n;
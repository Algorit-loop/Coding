#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const ll MOD = 998244353;

typedef vector<vector<ll>> Matrix;

// Hàm nhân ma trận với modulo MOD
Matrix matMul(const Matrix &A, const Matrix &B) {
    int n = A.size();
    int m = B[0].size();
    int p = A[0].size(); // p = số cột của A = số hàng của B
    Matrix C(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++){
        for (int k = 0; k < p; k++){
            if (A[i][k] != 0) {
                for (int j = 0; j < m; j++){
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
    }
    return C;
}

// Hàm lũy thừa ma trận
Matrix matPow(Matrix base, ll exp) {
    int n = base.size();
    Matrix result(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++){
        result[i][i] = 1;
    }
    while(exp > 0){
        if(exp & 1)
            result = matMul(result, base);
        base = matMul(base, base);
        exp >>= 1;
    }
    return result;
}

// Hàm tính lũy thừa nhanh modulo
ll modExp(ll base, ll exp, ll mod) {
    ll result = 1 % mod;
    base %= mod;
    while(exp > 0){
        if(exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}
void file(const string FILE){
    if (fopen((FILE + ".INP").c_str(),"r")){
        freopen((FILE + ".INP").c_str(), "r", stdin);
        freopen((FILE + ".OUT").c_str(), "w", stdout);
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    file("distance");
    ll N;
    int M, K;
    cin >> N >> M >> K;

    // Trường hợp K == 0: không có ràng buộc
    if(K == 0){
        cout << modExp(M, N, MOD) << "\n";
        return 0;
    }

    // Xây dựng ma trận chuyển trạng thái T: kích thước MxM, giá trị 1 nếu |i - j|>=K (với i,j biểu diễn giá trị 1-indexed)
    Matrix Tmat(M, vector<ll>(M, 0));
    for (int i = 0; i < M; i++){
        for (int j = 0; j < M; j++){
            if(abs((i+1) - (j+1)) >= K)
                Tmat[i][j] = 1;
        }
    }
    // Tính T^(N-1)
    Matrix Texp = matPow(Tmat, N - 1);
    // Với vector khởi tạo v = [1,1,...,1], kết quả là tổng các phần tử của T^(N-1)
    ll ans = 0;
    for (int i = 0; i < M; i++){
        for (int j = 0; j < M; j++){
            ans = (ans + Texp[i][j]) % MOD;
        }
    }
    cout << ans << "\n";

    return 0;
}

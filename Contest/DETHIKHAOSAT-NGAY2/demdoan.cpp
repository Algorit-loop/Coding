#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAX_A = 10000000;
vector<bool> isPrime;

void sieve() {
    isPrime.assign(MAX_A+1, true);
    if(MAX_A >= 0) isPrime[0] = false;
    if(MAX_A >= 1) isPrime[1] = false;
    for (int i = 2; i * i <= MAX_A; i++){
        if(isPrime[i]){
            for (int j = i*i; j <= MAX_A; j += i)
                isPrime[j] = false;
        }
    }
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
    file("demdoan");
    sieve();

    int T;
    cin >> T;
    while(T--){
        int N, K;
        cin >> N >> K;
        vector<int> A(N);
        for (int i = 0; i < N; i++){
            cin >> A[i];
        }
        // Biến dãy A thành dãy B, B[i] = 1 nếu A[i] là số nguyên tố, 0 nếu không.
        vector<int> B(N, 0);
        for (int i = 0; i < N; i++){
            B[i] = (A[i] <= MAX_A && isPrime[A[i]]) ? 1 : 0;
        }
        // Đếm số đoạn con có tổng bằng K bằng cách sử dụng prefix sum và hashmap.
        ll res = 0;
        unordered_map<ll, ll> freq;
        ll prefix = 0;
        freq[0] = 1;
        for (int i = 0; i < N; i++){
            prefix += B[i];
            // Tìm số lượng các prefix trước đó mà prefix[i] - prefix[j] = K
            if(freq.find(prefix - K) != freq.end()){
                res += freq[prefix - K];
            }
            freq[prefix]++;
        }
        cout << res << "\n";
    }
    return 0;
}

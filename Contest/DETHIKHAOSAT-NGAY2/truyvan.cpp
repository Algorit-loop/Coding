#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXVAL = 10000000;
vector<bool> isPrime;

// Sàng số nguyên tố cho các giá trị từ 0 đến MAXVAL
void sieve(){
    isPrime.assign(MAXVAL+1, true);
    if(MAXVAL >= 0) isPrime[0] = false;
    if(MAXVAL >= 1) isPrime[1] = false;
    for (int i = 2; i * i <= MAXVAL; i++){
        if(isPrime[i]){
            for (int j = i*i; j <= MAXVAL; j += i){
                isPrime[j] = false;
            }
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
    file("truyvan");
    sieve();
    int Q;
    cin >> Q;
    // Sử dụng map để theo dõi số lượng của từng số
    map<int, ll> freq;
    ll totalSum = 0;
    ll primeCount = 0;

    while(Q--){
        int type;
        cin >> type;
        if(type == 1){
            int x;
            cin >> x;
            totalSum += x;
            freq[x]++;
            if(x <= MAXVAL && isPrime[x]) {
                primeCount++;
            }
        }
        else if(type == 2){
            int x;
            ll c;
            cin >> x >> c;
            auto it = freq.find(x);
            if(it != freq.end()){
                ll cnt = it->second;
                ll removed = min(cnt, c);
                totalSum -= (ll)x * removed;
                if(x <= MAXVAL && isPrime[x]){
                    primeCount -= removed;
                }
                it->second -= removed;
                if(it->second <= 0){
                    freq.erase(it);
                }
            }
            // Nếu x không tồn tại trong tập thì không làm gì
        }
        else if(type == 3){
            if(freq.empty()){
                cout << "0 0 0\n";
            } else {
                int minVal = freq.begin()->first;
                int maxVal = freq.rbegin()->first;
                cout << totalSum << " " << (maxVal - minVal) << " " << primeCount << "\n";
            }
        }
    }
    return 0;
}

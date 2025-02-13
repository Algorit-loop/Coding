#include <bits/stdc++.h>
#include <random>
#include <chrono>
using namespace std;
#define ll long long

// global const for tests maker
const string name = "demdoan"; // tên đề bài
const int n_tests = 20;        // số lượng test
const int len_id = 3;          // chiều dài id của test (>= số chữ số của n_tests)
const string ex_in = ".inp";
const string ex_out = ".out";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Hàm random trong khoảng [l, r]
ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL * (r - l + 1));
}

void make_test(string id_s, int id)
{
    string dir = name + '\\' + id_s;
    string inpfi = name + ex_in;
    string outfi = name + ex_out;
    ofstream inp(inpfi);

    // Định dạng đầu vào cho bài 2:
    // Dòng đầu tiên: T (số lượng test, 1 ≤ T ≤ 5)
    // Với mỗi test:
    //   Dòng 1: N K   (với 0 ≤ K ≤ N, 1 ≤ N ≤ 10^5)
    //   Dòng 2: N số nguyên A_i, với 1 ≤ A_i ≤ 10^7
    if (id <= 0.4 * n_tests){
        int t = range(1,5);
        inp << t << "\n";
        while(t--){
            int n = range(1, 2000); // branch 40%: 1 ≤ N ≤ 2000
            int K = range(0, n);
            inp << n << " " << K << "\n";
            for (int i = 1; i <= n; i++){
                inp << range(1, 1000) << " ";
            }
            inp << "\n";
        }
    }
    else if (id <= 0.7 * n_tests){
        int t = range(1,5);
        inp << t << "\n";
        while(t--){
            int n = range(1, 1000); // branch 30%: 1 ≤ N ≤ 1000
            int K = range(0, n);
            inp << n << " " << K << "\n";
            for (int i = 1; i <= n; i++){
                inp << range(1, 10000000) << " ";
            }
            inp << "\n";
        }
    }
    else {
        int t = range(1,5);
        inp << t << "\n";
        while(t--){
            int n = range(10000, 100000); // branch 30%: 1e4 ≤ N ≤ 1e5
            int K = range(0, n);
            inp << n << " " << K << "\n";
            for (int i = 1; i <= n; i++){
                inp << range(1, 10000000) << " ";
            }
            inp << "\n";
        }
    }
    inp.close();

    // Chạy code giải bài và copy file kết quả vào thư mục test
    system((name + ".exe").c_str());
    system(("md " + dir).c_str());
    system(("copy " + inpfi + " " + dir).c_str());
    system(("copy " + outfi + " " + dir).c_str());
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    srand(time(NULL));
    system(("rd /s /q " + name).c_str());
    system(("md " + name).c_str());
    system(("g++ -std=c++14 " + name + ".cpp -o " + name + ".exe").c_str());
    for (int it = 1; it <= n_tests; ++it)
    {
        string id = to_string(it);
        while (id.size() < len_id) id = '0' + id;
        make_test(id, it);
        cerr << "Test " << it << ": Completed!\n";
    }
    return 0;
}

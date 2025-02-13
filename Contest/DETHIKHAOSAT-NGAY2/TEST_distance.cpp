#include <bits/stdc++.h>
#include <random>
#include <chrono>
using namespace std;
#define ll long long

// global const for tests maker
const string name = "distance"; // tên đề bài
const int n_tests = 20;
const int len_id = 3;
const string ex_in = ".inp";
const string ex_out = ".out";

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Hàm random trong khoảng [l, r]
ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL * (r - l + 1));
}

void make_test(string id_s, int id){
    string dir = name + '\\' + id_s;
    string inpfi = name + ex_in;
    string outfi = name + ex_out;
    ofstream inp(inpfi);

    // Định dạng đầu vào cho bài 3:
    // Một dòng chứa 3 số nguyên: N, M, K
    // với: 1 ≤ N ≤ 1e9, 1 ≤ M ≤ 100, 0 ≤ K < M.
    if(id <= 0.3 * n_tests){
        int N = range(1, 8);
        int M = range(1, 8);
        int K = (M > 1) ? range(0, M - 1) : 0;
        inp << N << " " << M << " " << K << "\n";
    }
    else if(id <= 0.6 * n_tests){
        int N = range(1, 100);
        int M = range(1, 100);
        int K = (M > 1) ? range(0, M - 1) : 0;
        int u = range(1,100); if (u <= 60) K = 0;
        inp << N << " " << M << " " << K << "\n";
    }
    else if(id <= 0.8 * n_tests){
        int N = range(1, 10000);
        int M = range(90, 100);
        int K = (M > 1) ? range(0, M - 1) : 0;
        inp << N << " " << M << " " << K << "\n";
    }
    else {
        int N = range(100000000, 1000000000LL);
        int M = range(90, 100);
        int K = (M > 1) ? range(0, M - 1) : 0;
        inp << N << " " << M << " " << K << "\n";
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
        while(id.size() < len_id) id = '0' + id;
        make_test(id, it);
        cerr << "Test " << it << ": Completed!\n";
    }
    return 0;
}

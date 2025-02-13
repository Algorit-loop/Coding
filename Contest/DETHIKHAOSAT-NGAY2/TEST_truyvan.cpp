#include <bits/stdc++.h>
#include <random>
#include <chrono>
using namespace std;
#define ll long long

// global const for tests maker
const string name = "truyvan"; // tên đề bài
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

    // Định dạng đầu vào cho bài 4:
    // Dòng đầu tiên chứa số nguyên Q (số lượng truy vấn).
    // Sau đó Q dòng, mỗi dòng là một truy vấn:
    // - Loại 1: "1 x"
    // - Loại 2: "2 x c"
    // - Loại 3: "3"
    //
    // Phân bố test theo 4 branch:
    // Branch 1: Q ∈ [1, 1000], x ∈ [1, 1e6], đối với truy vấn loại 2, c = 0.
    // Branch 2: Q ∈ [1, 1000], x ∈ [1, 1e6], đối với truy vấn loại 2, c = 1.
    // Branch 3: Q ∈ [10000, 200000], x ∈ [1, 1e6], c = 1.
    // Branch 4: Q ∈ [10000, 200000], x ∈ [1, 1e7], c ∈ [0, 1e9].

    if(id <= 0.2 * n_tests){
        int Q = range(1, 1000);
        inp << Q << "\n";
        for (int i = 0; i < Q; i++){
            int type = range(1, 3); // chọn ngẫu nhiên kiểu truy vấn (1, 2, hoặc 3)
            if (type == 1) {
                int x = range(1, 1000000);
                inp << "1 " << x << "\n";
            } else if (type == 2) {
                int x = range(1, 1000000);
                int c = 0;
                inp << "2 " << x << " " << c << "\n";
            } else {
                inp << "3\n";
            }
        }
    }
    else if(id <= 0.4 * n_tests){
        int Q = range(1, 1000);
        inp << Q << "\n";
        for (int i = 0; i < Q; i++){
            int type = range(1, 3);
            if (type == 1) {
                int x = range(1, 1000000);
                inp << "1 " << x << "\n";
            } else if (type == 2) {
                int x = range(1, 1000000);
                int c = 1;
                inp << "2 " << x << " " << c << "\n";
            } else {
                inp << "3\n";
            }
        }
    }
    else if(id <= 0.7 * n_tests){
        int Q = range(100000, 200000);
        inp << Q << "\n";
        for (int i = 0; i < Q; i++){
            int type = range(1, 3);
            if (type == 1) {
                int x = range(1, 1000000);
                inp << "1 " << x << "\n";
            } else if (type == 2) {
                int x = range(1, 1000000);
                int c = 1;
                inp << "2 " << x << " " << c << "\n";
            } else {
                inp << "3\n";
            }
        }
    }
    else {
        int Q = range(10000, 200000);
        inp << Q << "\n";
        vector<int> v;
        for (int i = 0; i < Q; i++){
            int type = range(1, 3);
            if (type == 1) {
                int x = range(1, 10000000);
                if (v.empty()) v.push_back(x);
                else{
                    int px = range(1,100);
                    if (px <= 40) x = v[range(0,v.size()-1)];
                    else v.push_back(x);
                }
                inp << "1 " << x << "\n";
            } else if (type == 2) {
                int x = range(1, 10000000);
                int p = range(1,100);
                int c = range(0, 1000000000);
                if (p <= 50) c = range(1,10);
                inp << "2 " << x << " " << c << "\n";
            } else {
                inp << "3\n";
            }
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
        while(id.size() < len_id) id = '0' + id;
        make_test(id, it);
        cerr << "Test " << it << ": Completed!\n";
    }
    return 0;
}

#include <bits/stdc++.h>
#include <random>
#include <chrono>

#define ll long long

using namespace std;

// global const of tests maker
const string name = "dpknste2"; // Name of tests
const int n_tests = 40; // Number of tests
const int len_id = 3; // You should make len_id >= len(n_tests)
const string ex_in = ".inp";
const string ex_out = ".out";

	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

long long Rand(long long l, long long h)
{
    return l + ((long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
                (long long)rand() * (RAND_MAX + 1) +
                rand()) % (h - l + 1);
}

ll range(ll l, ll r){
    return l + (1ULL * rng() * 1ULL * rng() + rng() + rng() + 1) % (1ULL *(r - l + 1));
}

void make_test(string id_s, int id)
{
    string dir = name + '\\' + id_s;
    string inpfi = name + ex_in;
    string outfi = name + ex_out;
    ofstream inp(inpfi);

    // create input
    if (id <= 0.1 * n_tests){
        int n = range(100,100) , m = range(1e4-100,1e4);
        inp << n << " " << m << "\n";
        for (int i = 1; i <= n; i++){
            int w = range(0,100) , v = range(0,9999), a = range(1000-10,1000);
            if (w <= 95) w = 0; else w = 1;
            inp << w << " " << v << " " << a << "\n";
        }
    }
    else
    if (id <= 0.2 * n_tests){
        int n = range(100,100) , m = range(1e4-100,1e4);
        inp << n << " " << m << "\n";
        for (int i = 1; i <= n; i++){
            int w = range(0,100) , v = range(0,9999), a = range(800,1000);
            inp << w << " " << v << " " << a << "\n";
        }
    }
    else
    if (id <= 0.5 * n_tests){
        int n = range(90,100) , m = range(7e3,1e4);
        inp << n << " " << m << "\n";
        for (int i = 1; i <= n; i++){
            int w = range(700,1e3) , v = range(0,1234), a = range(0,500);
            inp << w << " " << v << " " << a << "\n";
        }
    }
    else
    if (id <= 0.7 * n_tests){
        int n = range(90,100) , m = range(7e3,1e4);
        inp << n << " " << m << "\n";
        for (int i = 1; i <= n; i++){
            int w = range(0,200) , v = range(0,1341), a = range(0,1000);
            int c = range(1,100); if (c <= 35) w = 0;
            c = range(1,100); if (c <= 35) v = 0;
            inp << w << " " << v << " " << a << "\n";
        }
    }
    else
    if (id <= 0.85 * n_tests){
        int n = range(90,100) , m = range(7e3,1e4);
        inp << n << " " << m << "\n";
        for (int i = 1; i <= n; i++){
            int w = range(0,100) , v = range(0,1234), a = range(0,100);
            inp << w << " " << v << " " << a << "\n";
        }
    }
    else
    if (id <= 1.0 * n_tests){
        int n = range(90,100) , m = range(7e3,1e4);
        inp << n << " " << m << "\n";
        for (int i = 1; i <= n; i++){
            int w = range(0,1e3) , v = range(0,9999), a = range(0,500);
            inp << w << " " << v << " " << a << "\n";
        }
    }
    inp.close();

    // run code and copy files
    system((name + ".exe").c_str());
    system(("md " + dir).c_str());
    system(("copy " + inpfi + ' ' + dir).c_str());
    system(("copy " + outfi + ' ' + dir).c_str());
}

int main()
{
    ios_base::sync_with_stdio(0); cout.tie(0);
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

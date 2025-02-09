#include <string>
#include <bitset>
#include <iostream>
#include <random>
#include <time.h>
#include <bits/stdc++.h>
using namespace std;

string BinaryCode(int x, int sz){
    string res = "";
    while (x > 0){
        res = char(x % 2 + '0') + res;
        x /= 2;
    }
    while ((int)res.size() < sz) res = "0" + res;
    return res;
}
int BinaryToInt(string s){
    reverse(s.begin(),s.end());
    int res = 0;
    for (int i = 0; i < s.size(); i++){
        if (s[i] == '1') res = res + (1 << i);
    }
    return res;
}
string encode(const string rawMessage) {
    // "DD HH:MM"
    string s1 = rawMessage.substr(0,2);
    string s2 = rawMessage.substr(3,2);
    string s3 = rawMessage.substr(6,2);
    string newstr = BinaryCode(stoi(s1),5)
                    + BinaryCode(stoi(s2),5)
                    + BinaryCode(stoi(s3),6);
    int mr = 21;
    // string newstr = rawMessage;
	vector <int> s(mr + 1,0);
    int c = 1;
    for (int i = 0; i < newstr.size(); i++){
        while (true){
            int lg = __lg(c);
            if ((1 << lg) == c) c++;
            else break;
        }
        s[c++] = newstr[i] - '0';
    }
    for (int i = 1 , d = 0; i <= mr; i = i * 2 , d++){
        int x = 0;
        for (int j = i + 1; j <= mr; j++){
            if ((j >> d) & 1) x = x ^ s[j];
        }
        s[i] = x;
    }
    string res = "";
    for (int i = 1; i <= mr; i++) res = res + char(s[i] + '0');
    // cout << res << "\n";
    return res;
}

string decode(const string encry) {
    int mparity = 5;
    vector <int> s((int)encry.size() + 1,0);
    for (int i = 0; i < encry.size(); i++){
        s[i+1] = encry[i] - '0';
    }
    //for (int i = 1; i < s.size(); i++) cout << s[i] << " "; cout << "\n";
    int pos = 0;
    for (int i = 1; i <= mparity; i++){
        // cout << "i = " << i << "\n";
        int x = 0;
        for (int j = i; j < s.size(); j++){
            if ((j >> (i - 1)) & 1){
                x = x ^ s[j];
                // cout << j << "? ";
            }
        }
        // cout << "\n";
        // if (x == 1) cout << "sai p" << i << "\n";
        if (x == 1) pos = pos + ((1 << (i - 1)));
    }
    if (pos > 0) s[pos] = s[pos] ^ 1;
    //cout << "error_pos = " << pos << "\n";
    string strf = "";
    for (int i = 1; i < s.size(); i++){
        int l2 = __lg(i);
        if ((1 << l2) != i) strf = strf + char(s[i] + '0');
    }
    //cout << "strf = " << strf << "\n";
    // return strf;
    string s1 = strf.substr(0,5);
    string s2 = strf.substr(5,5);
    string s3 = strf.substr(10,6);
    int dd = BinaryToInt(s1);
    int hh = BinaryToInt(s2);
    int mm = BinaryToInt(s3);

    char buffer[9];
    snprintf(buffer, sizeof(buffer), "%02d %02d:%02d", dd, hh, mm);
    string res = string(buffer);
    // cout << res.size() << "\n";
    return res;
}

int main(){
    
    srand(time(NULL));
    string test = "31 19:58";
    string ec = encode(test);
    for (int i = -1; i < (int)ec.size(); i++){
        string newstr = ec;
        if (i >= 0)
            if (newstr[i] == '0') newstr[i] = '1'; else newstr[i] = '0';
        cout << "If x = " << i << " then decode = " << decode(newstr) << "\n";
    }

    // string test = encode("0001010");
    // cout << "encode = " << test << "\n";
    // for (int i = 0; i < test.size(); i++){
    //     string i_test = test;
    //     if (i_test[i] == '0') i_test[i] = '1'; else i_test[i] = '0';
    //     cout << "If i = " << i << " then decode = ";
    //     cout << decode(i_test) << "\n";
    // }
    
}
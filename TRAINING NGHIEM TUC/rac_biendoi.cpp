#include <bits/stdc++.h>
#define int long long

using namespace std;
void file(string f){
    if (fopen((f + ".INP").c_str(),"r")){
        freopen((f + ".INP").c_str(),"r",stdin);
        freopen((f + ".OUT").c_str(),"w",stdout);
    }
}
int k;
string s;
void solve(){
    cin >> k;
    cin >> s;
    assert(k <= s.size());
    string copyS = s;
    int n = s.size();
    s = "!" + s;
    multiset <char> st;
    for (int i = 1; i < k; i++){
        st.insert(s[i]);
    }
    int pos = 0;
    // --- find pos ----
    for (int i = k; i <= n; i++){
        if (i - k > 0){
            auto f = st.find(s[i - k]);
            assert(f != st.end());
            st.erase(f);
        }
        st.insert(s[i]);
        for (int j = i - k + 1; j <= i; j++){
            if (s[j] > *st.begin()){
                pos = j;
                break;
            }
        }
        if (pos != 0) break;
    }
    // cout << "pos = " << pos << "\n";
    // -----
    if (pos == 0){
        // cout << copyS << "\n" << copyS << "\n";
        cout << copyS << "\n";
        return;
    }
    st.clear();
    char val = 'z' + 1;
    int respos = -1;
    for (int i = 1; i <= n; i++){
        if (i - k > 0){
            auto f = st.find(s[i - k]);
            assert(f != st.end());
            st.erase(f);
        }
        st.insert(s[i]);
        if (i >= k && i - k + 1 <= pos && pos <= i){
            if (val >= *st.begin()){
                val = *st.begin();
                respos = i;
            }
        }
    }
    assert(respos != -1);
    for (int i = respos - k + 1; i <= respos; i++){
        s[i] = val;
    }
    s.erase(0,1);
    cout << s << "\n";
}
signed main(){
    file("biendoi");
    int t = 1;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}

#include <bits/stdc++.h>
using namespace std;

int __ac(string Noti, string Feedback){
    cout << Noti;
    cerr << Feedback;
    return 0;
}
int __wa(string Noti, string Feedback){
    cout << Noti;
    cerr << Feedback;
    return 1;
}
int __partial(double point, string Noti, string Feedback){
    cerr << point << endl;
    cout << Noti;
    cerr << Feedback;
    return 7;
}
int main(int argc, char** argv) {
    ifstream inp(argv[1]);
    ifstream out(argv[2]);
    ifstream ans(argv[3]);

    int n, a, b, c, d;

    try{
        inp >> n;
        out >> a >> b;
        ans >> c >> d;

        if (a + b == c + d) {
            cout << a << " + " << b << " = " << c << " + " << d << endl;

            if (a >= 0 && b >= 0) {
                return __ac("Dun roi ban oi","ok em");
            }
            else {
                return __partial(0.7,"cung duoc nhung chua dung","ga`");
            }
        }     
        else {
            cout << "a + b = " << a + b << " != " << n << endl;
            return __wa("qua ga`","sai roi");
        }
    }
    catch (exception e){
        cout << "Looks like the format is wrong";
        cerr << e.what();
        return 0;
    }
}
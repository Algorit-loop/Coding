#include <iostream>

using namespace std;

int main(){
    cout << "toi rat dep trai" << endl; // end line
    // kieu du lieu ?
    // so nguyen : byte, int, long long, unsigned long long, ...
    // so thuc : float, double, long double, ....
    // ki tu : char
    // dung/sai : bool
    // xau : string
    // for (<khoi tao> ; <dieu kien>; <lenh tang/giam>)
    int a = 10;
    cin >> a;
    // + - *
    // a / b : nếu a và b là số nguyên thì nó sẽ là a div b
    // a % b : -> a mod b
    for (int i = 1; i <= a; i++)
    {
        if (i % 2 == 0)
        {
            cout << i << " ";
            cout << "haha" << endl;
        }
    }
    return 0;
}

#include <iostream>
#include "BigInt.h"

using namespace std;

int main()
{
    BigInt a(0);
    BigInt b(1);
    BigInt c(4096);
    BigInt d(30042007);

    BigInt e("1A2B3C4D");
    BigInt f("123456789ABCDEF");

    cout << "0: " << a << endl;
    cout << "1: " << b << endl;
    cout << "4096: " << c << endl;
    cout << "30042007: " << d << endl;

    cout << "hex1: " << e << endl;
    cout << "hex2: " << f << endl;

    return 0;
}
#include <iostream>
#include "BigInt.h"

using namespace std;

int main()
{
    BigInt a("123456789ABCDEF0");
    BigInt b("1111111111111111");

    cout << "A = " << a << "\n";
    cout << "B = " << b << "\n\n";

    cout << "Addition:\n";
    cout << "A + B = " << (a + b) << "\n\n";

    cout << "Subtraction:\n";
    cout << "A - B = " << (a - b) << "\n\n";

    BigInt c("ABC");
    BigInt d("123");

    cout << "Comparison:\n";
    cout << "C = " << c << "\n";
    cout << "D = " << d << "\n";
    cout << "C < D:  " << (c < d) << "\n";
    cout << "C > D:  " << (c > d) << "\n";
    cout << "C == D: " << (c == d) << "\n";
    cout << "C != D: " << (c != d) << "\n\n";

    BigInt testNum("2D");

    cout << "Bit operations:\n";
    cout << "Number = " << testNum << "\n";
    cout << "Bit length = " << testNum.bitLength() << "\n";

    BigInt shiftedHigh = testNum.shiftBitsHigh(4);
    cout << "Number << 4 = " << shiftedHigh << "\n";

    BigInt shiftedLow = shiftedHigh.shiftBitsLow(4);
    cout << "Shifted number >> 4 = " << shiftedLow << "\n";

    BigInt e("12345678");
    BigInt f("ABCDEF");

    cout << "\nMultiplication:\n";
    cout << "E = " << e << "\n";
    cout << "F = " << f << "\n";
    cout << "E * 5 = " << (e * 5) << "\n";
    cout << "E * F = " << (e * f) << "\n\n";

    return 0;
}
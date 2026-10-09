#include "BigInt.h"

#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

BigInt::BigInt()
{
    for (int i = 0; i < WORDS; i++)
    {
        words[i] = 0;
    }
}

BigInt::BigInt(uint64_t value)
{
    for (int i = 0; i < WORDS; i++)
    {
        words[i] = 0;
    }

    words[0] = value;
}

BigInt::BigInt(const string& hex)
{
    for (int i = 0; i < WORDS; i++)
    {
        words[i] = 0;
    }

    int len = hex.length();
    int pos = 0;

    for (int i = len; i > 0; i -= 16)
    {
        if (pos >= WORDS)
        {
            break;
        }

        int start = max(0, i - 16);
        int count = i - start;

        string part = hex.substr(start, count);

        words[pos] = stoull(part, nullptr, 16);

        pos++;
    }
}

string BigInt::toHex() const
{
    stringstream ss;

    ss << hex << setfill('0');

    bool zero = true;

    for (int i = WORDS - 1; i >= 0; i--)
    {
        if (words[i] != 0 || !zero)
        {
            if (zero)
            {
                ss << words[i];
                zero = false;
            }
            else
            {
                ss << setw(16) << words[i];
            }
        }
    }

    if (zero)
    {
        return "0";
    }

    return ss.str();
}

ostream& operator<<(ostream& os, const BigInt& num)
{
    os << num.toHex();

    return os;
}
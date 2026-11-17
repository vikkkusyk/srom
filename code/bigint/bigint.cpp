#include "BigInt.h"

#include <iomanip>
#include <sstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

BigInt::BigInt()
{
    for (int i = 0; i < WORDS; i++)
    {
        words[i] = 0;
    }
}

BigInt::BigInt(uint32_t value)
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

    for (int i = len; i > 0; i -= 8)
    {
        if (pos >= WORDS)
        {
            break;
        }

        int start = max(0, i - 8);
        int count = i - start;

        string part = hex.substr(start, count);

        words[pos] = static_cast<uint32_t>(stoull(part, nullptr, 16));

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
                ss << setw(8) << words[i];
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

BigInt BigInt::operator+(const BigInt& other) const
{
    BigInt result;
    uint32_t carry = 0;

    for (size_t i = 0; i < WORDS; ++i)
    {
        uint64_t temp = static_cast<uint64_t>(words[i])
            + other.words[i] + carry;

        result.words[i] = static_cast<uint32_t>(temp & 0xFFFFFFFF);
        carry = static_cast<uint32_t>(temp >> 32);
    }

    return result;
}

BigInt BigInt::operator-(const BigInt& other) const
{
    BigInt result;
    uint32_t borrow = 0;

    for (size_t i = 0; i < WORDS; ++i)
    {
        int64_t temp = static_cast<int64_t>(words[i])
            - other.words[i] - borrow;

        if (temp >= 0)
        {
            result.words[i] = static_cast<uint32_t>(temp);
            borrow = 0;
        }
        else
        {
            result.words[i] = static_cast<uint32_t>((1ULL << 32) + temp);
            borrow = 1;
        }
    }

    if (borrow == 1)
    {
        throw invalid_argument("Error: subtraction result is negative");
    }

    return result;
}

int BigInt::compare(const BigInt& other) const
{
    int i = WORDS - 1;

    while (i >= 0 && words[i] == other.words[i])
    {
        i--;
    }

    if (i == -1)
    {
        return 0;
    }
    else if (words[i] > other.words[i])
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

bool BigInt::operator<(const BigInt& other) const
{
    return compare(other) == -1;
}

bool BigInt::operator>(const BigInt& other) const
{
    return compare(other) == 1;
}

bool BigInt::operator<=(const BigInt& other) const
{
    return compare(other) <= 0;
}

bool BigInt::operator>=(const BigInt& other) const
{
    return compare(other) >= 0;
}

bool BigInt::operator==(const BigInt& other) const
{
    return compare(other) == 0;
}

bool BigInt::operator!=(const BigInt& other) const
{
    return compare(other) != 0;
}

int BigInt::bitLength() const
{
    for (int i = WORDS - 1; i >= 0; --i)
    {
        if (words[i] != 0)
        {
            int length = i * 32;
            uint32_t temp = words[i];

            while (temp > 0)
            {
                length++;
                temp >>= 1;
            }

            return length;
        }
    }

    return 0;
}

BigInt BigInt::shiftBitsHigh(int shift) const
{
    if (shift < 0)
    {
        throw invalid_argument("Negative shift");
    }

    BigInt result;

    int wordShift = shift / 32;
    int bitShift = shift % 32;

    if (wordShift >= WORDS)
    {
        return result;
    }

    uint32_t carry = 0;

    for (size_t i = 0; i < WORDS - wordShift; ++i)
    {
        uint32_t current = words[i];

        result.words[i + wordShift] =
            (bitShift == 0 ? current : (current << bitShift)) | carry;

        carry = (bitShift == 0 ? 0 : (current >> (32 - bitShift)));
    }

    return result;
}

BigInt BigInt::shiftBitsLow(int shift) const
{
    if (shift < 0)
    {
        throw invalid_argument("Negative shift");
    }

    BigInt result;

    int wordShift = shift / 32;
    int bitShift = shift % 32;

    if (wordShift >= WORDS)
    {
        return result;
    }

    uint32_t carry = 0;

    for (int i = WORDS - 1; i >= wordShift; --i)
    {
        uint32_t current = words[i];

        result.words[i - wordShift] =
            (bitShift == 0 ? current : (current >> bitShift)) | carry;

        carry = (bitShift == 0 ? 0 : (current << (32 - bitShift)));
    }

    return result;
}




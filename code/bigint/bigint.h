#pragma once
#include <array>
#include <cstdint>
#include <string>
#include <iostream>

using namespace std;

class BigInt
{
public:
    static constexpr size_t WORDS = 32;

    array<uint64_t, WORDS> words{};

    BigInt();
    BigInt(uint64_t value);
    BigInt(const string& hex);

    string toHex() const;

    friend ostream& operator<<(ostream& os, const BigInt& num);
};

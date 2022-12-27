#include <iostream>
#include <string>

class BigInt
{
    public:

    int *data;
    int16_t size;
    bool negative;

    BigInt();
    BigInt(std::string in_str);
    BigInt(int32_t num);
    BigInt(const BigInt & other_num);
    BigInt(BigInt && other_num);

    BigInt &operator=(const BigInt &num);

    // Arithmetics
    
    friend BigInt operator+(const BigInt &a, const BigInt &b);
    friend BigInt operator+(const BigInt &a, const int32_t &b);

    friend BigInt operator-(const BigInt &, const BigInt &);
    friend BigInt operator-(const BigInt &, const int32_t &);
/*
    friend BigInt operator*(const BigInt &, const BigInt &);
    friend BigInt operator*(const BigInt &, const int32_t &);*/

    BigInt operator-();

    // Logic
    friend bool operator==(const BigInt &, const BigInt &);
    friend bool operator!=(const BigInt &, const BigInt &);

    friend bool operator>(const BigInt &, const BigInt &);
    friend bool operator>=(const BigInt &, const BigInt &);

    friend bool operator<(const BigInt &, const BigInt &);
    friend bool operator<=(const BigInt &, const BigInt &);

    friend std::ostream& operator<<(std::ostream& os, BigInt& num);

    ~BigInt();
};
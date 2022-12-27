#include "bigint.hpp"
#include <string>


BigInt::BigInt()
{
    data = nullptr;
    negative = false;
}

BigInt::BigInt(int32_t num)
{
    std::string to_str;
    to_str = std::to_string(abs(num));
    
    BigInt new_num(to_str);
    new_num.negative = (num < 0);

    *this = new_num;
}

BigInt::BigInt(std::string in_str)
{
    if (in_str[0] == '-')
    {
        negative = true;
    }
    else
    {
        negative = false;
    }

    size = in_str.length() - negative;

    data = new int[size];
    std::string str_buf;

    // больше индекс - выше разряд
    int count = 0;
    for (int i = size - 1; i >= 0; --i)
    {
        str_buf = in_str[i + negative];
        data[count] = std::stoi(str_buf);
        ++count;
    }
}

BigInt::BigInt(const BigInt & other_num)
{
    negative = other_num.negative;
    size = other_num.size;
    // обновим данные
    if (data != nullptr)
    {
        delete[] data;
    }
    data = new int[size];
    
    for (int i = 0; i < size; ++i)
    {
        data[i] = other_num.data[i];
    }
}

BigInt::BigInt(BigInt&& other_num)
{
    negative = other_num.negative;
    size = other_num.size;
    data = other_num.data;
    
    other_num.data = nullptr;
}


BigInt &BigInt::operator=(const BigInt &num)
{
    negative = num.negative;
    size = num.size;

    if (data != nullptr)
    {
        delete[] data;
    }

    data = new int[size];
    
    for (int i = 0; i < size; ++i)
    {
        data[i] = num.data[i];
    }   


    return *this;
}


// --- Арифметика ---
BigInt operator+(const BigInt &a, const BigInt &b)
{
    /*
    // Здесь рассматриваются разные случаи
    // в зависимости от знаков операндо
    // BUG: вместе с этим куском код работает странно
    if (a.negative ^ b.negative)
    {
        BigInt temp_1, temp_2;
        
        temp_1 = a;
        temp_2 = b;

        if (a.negative)
        {
            temp_1.negative = false;
            return (temp_2 - temp_1);
        }
        else
        {
            temp_2.negative = false;
            return (temp_1 - temp_2);
        }
    }*/

    BigInt new_num;
    new_num.negative = a.negative;

    int result = 0;
    int overflow = 0;

    BigInt short_num, long_num;

    if (a > b)
    {
        short_num = b;
        long_num = a;
    }
    else
    {
        short_num = a;
        long_num = b;
    }

    new_num.size = long_num.size;
    new_num.data = new int[new_num.size];

    for (int i = 0; i < short_num.size; ++i)
    {
        result = short_num.data[i] + long_num.data[i] + overflow;

        if (result < 9)
        {
            new_num.data[i] = result;
            overflow = 0;
        }
        else
        {
            new_num.data[i] = result % 10;
            overflow = result / 10;
        }
    }

    // Прошлись по числу покороче, 
    // теперь остаток надо прибавить к оставшимся старшим разряда
    for (int i = short_num.size; i < long_num.size; ++i)
    {
        result = long_num.data[i] + overflow;

        if (result < 9)
        {
            new_num.data[i] = result;
            overflow = 0;
        }
        else
        {
            new_num.data[i] = result % 10;
            overflow = result / 10;
        }
    }
    
    // Если в конце все еще остался остаток, то число получило новый порядок
    if (overflow > 0)
    {
        int* temp = new_num.data;
        new_num.data = new int[new_num.size + 1];

        for (int i = 0; i < new_num.size; ++i)
        {
            new_num.data[i] =  temp[i];
        }
        new_num.size += 1;
        // Новый старший порядок
        new_num.data[new_num.size - 1] = 1;

        delete[] temp;
        temp = nullptr;
    }
    return new_num;
}

BigInt operator+(const BigInt &a, const int32_t &b)
{
    return a + BigInt(b);
}


BigInt operator-(const BigInt &a, const BigInt &b)
{
    /*
    // Та же самая логика что и в + и та же фигня: 
    // с этими условиями код работает неисправно
    if (a.negative || b.negative)
    {
        if (a.negative && b.negative)
        {
            BigInt arg_2;
            arg_2 = b;
            arg_2.negative = false;
            return arg_2 - a;
        }

        if (a.negative)
        {
            BigInt arg_1, arg_2;
            arg_1 = a;
            arg_2 = b;

            arg_1.negative = false;
            arg_2.negative = false;

            BigInt arg_3 = arg_1 + arg_2;
            arg_3.negative = true;
            return arg_3;
        }

        if (b.negative)
        {
            BigInt arg_1, arg_2;
            arg_1 = a;
            arg_2 = b;

            BigInt arg_3 = arg_1 + arg_2;
            
            return arg_3;
        }
    }*/
    
    
    BigInt new_num;
    // arg_1 - arg_2
    BigInt arg_1, arg_2;
    int16_t res = 0;
    
    if (a < b)
    {
        new_num.negative = true;
        arg_1 = b;
        arg_2 = a;
    }
    else
    {
        new_num.negative = false;
        arg_1 = a;
        arg_2 = b;
    }

    new_num.size = arg_1.size;
    new_num.data = new int[new_num.size];
    int offset = 0;

    for (int i = 0; i < arg_2.size; ++i)
    {
        if (arg_1.data[i] < arg_2.data[i])
        {
            offset = 1;
            // Ищем ненулевое число старшего порядка
            while (arg_1.data[i + offset] == 0)
            {
                ++offset;
            }
            arg_1.data[i + offset] -= 1;
            new_num.data[i] = 10 + arg_1.data[i] - arg_2.data[i];
        }
        else
        {
            new_num.data[i] = arg_1.data[i] - arg_2.data[i];
        } 
    }

    // Добьем оставшееся
    for (int i = arg_2.size; i < arg_1.size; ++i)
    {
        new_num.data[i] = arg_1.data[i];
    }

    // Поубираем нули в старших разрядах
    if (new_num.data[new_num.size - 1] == 0)
    {
        for (int i = new_num.size - 1; i >= 0; --i)
        {
            if (i == 0 && new_num.data[i] == 0)
            {
                delete[] new_num.data;
                new_num.size = 1;
                new_num.data = new int[1];
                new_num.data[0] = 0;
                break;
            }

            if (new_num.data[i] != 0)
            {
                int* temp = new_num.data;
                new_num.size = i + 1;
                new_num.data = new int[i + 1];
                for (int j = 0; j < new_num.size; ++i)
                {
                    new_num.data[j] = temp[j];
                }
                delete[] temp;
                temp = nullptr;
                break;
            }
        }
    }
    return new_num;
}

BigInt operator-(const BigInt &a, const int32_t &b)
{
    return a - BigInt(b);
}


BigInt BigInt::operator-()
{
    BigInt new_num;
    new_num = *this;
    new_num.negative = !this->negative;
    return new_num;
}

bool operator==(const BigInt &a, const BigInt &b)
{
    if (a.size != b.size)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < a.size; ++i)
        {
            if (a.data[i] != b.data[i])
            {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const BigInt &a, const BigInt &b)
{
    return !(a == b);
}

bool operator>(const BigInt &a, const BigInt &b)
{
    int16_t n = a.size, m = b.size;
    if (n != m)
    {
        return n > m;
    }
    while (n--)
    {
        if (a.data[n] != b.data[n])
        {
            return (a.data[n] > b.data[n]);
        }
    }
    return false;
}

bool operator<(const BigInt &a, const BigInt &b)
{
    return (b > a);
}

bool operator>=(const BigInt &a, const BigInt &b)
{
    return !(a < b);
}

bool operator<=(const BigInt &a, const BigInt &b)
{
    return !(a > b);
}

std::ostream& operator<<(std::ostream& os, BigInt& num)
{
    if (num.negative)
    {
        os << '-';
    }
    
    for (int i = num.size - 1; i >= 0 ; --i)
    {
        os << num.data[i];
    }

    return os;
}


BigInt::~BigInt()
{
    delete[] data;
    data = nullptr;
}
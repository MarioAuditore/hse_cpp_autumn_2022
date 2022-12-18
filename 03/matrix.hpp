#pragma once
#include <iostream>

class Matrix
{
public:    
    class ProxyRow
    {

    protected:
        int32_t *data_;

    public:
        int32_t size;

        ProxyRow()=default;
        void Init(int m);
        
        int32_t& operator[](size_t j);

        const ProxyRow& operator*=(const int32_t n);
        const ProxyRow operator+(const ProxyRow &row);
        const bool operator==(const ProxyRow &row);
        const bool operator!=(const ProxyRow &row);
        const void operator=(const ProxyRow row);

        friend std::ostream& operator<<(std::ostream& os, ProxyRow& row);

        ~ProxyRow();
    };

    Matrix() = default;
    Matrix(int n, int m);
    
    ProxyRow& operator[](size_t i)
    ;
    Matrix& operator*=(int32_t n);
    const Matrix operator+(const Matrix &row);
    const bool operator==(const Matrix &row);
    const bool operator!=(const Matrix &row);
    const void operator=(const Matrix row);

    friend std::ostream& operator<<(std::ostream& os, Matrix& mtx);

    ~Matrix();

protected:
    ProxyRow *rows_;
    int32_t n_rows;
};
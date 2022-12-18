#include "matrix.hpp"


// ==================
// ProxyRow functions
// ==================

void Matrix::ProxyRow::Init(int m)
{
    size = m;
    data_ = new int32_t[m]();
}

int32_t& Matrix::ProxyRow::operator[](size_t j)
{
    if (j > size - 1) {
        throw std::out_of_range("");
    }
    else {
        return data_[j];
    }
}

const Matrix::ProxyRow& Matrix::ProxyRow::operator*=(const int32_t n)
{
    for (int i = 0; i < size; ++i)
    {
        data_[i] *= n;
    }
    return *this;
}

const Matrix::ProxyRow Matrix::ProxyRow::operator+(const Matrix::ProxyRow &row)
{
    Matrix::ProxyRow new_row = Matrix::ProxyRow();
    new_row.Init(size);

    for (int i = 0; i < size; ++i)
    {
        new_row.data_[i] = data_[i] + row.data_[i];
    }
    return new_row;
}

const void Matrix::ProxyRow::operator=(const Matrix::ProxyRow row)
{
    *data_ = *row.data_;
}

const bool Matrix::ProxyRow::operator==(const Matrix::ProxyRow &row)
{
    
    for (int i = 0; i < size; ++i)
    {
        if (data_[i] != row.data_[i])
        {
            return false;
        }
        
    }
    return true;
}

const bool Matrix::ProxyRow::operator!=(const Matrix::ProxyRow &row)
{
    return !(this->operator==(row));
}

std::ostream& operator<<(std::ostream& os, Matrix::ProxyRow& row)
{
    os << "[";
    for (int i = 0; i < row.size; ++i)
    {
        os << row.data_[i] << " ";
    }
    os << "]";
    return os;
}

Matrix::ProxyRow::~ProxyRow()
{
    delete[] data_;
}


// ================
// Matrix functions
// ================


Matrix::Matrix(int n, int m) : Matrix()
{
    //std::cout << "Matrix created at " << this << std::endl;
    n_rows = n;
    rows_ = new ProxyRow[n]();
    for (int i=0; i < n; ++i)
    {
        rows_[i].Init(m);
    }
}

Matrix::ProxyRow& Matrix::operator[](size_t i)
{
    if (i > n_rows - 1) {
        throw std::out_of_range("");
    }
    else{
        return rows_[i];
    }
    
}


Matrix& Matrix::operator*=(const int32_t n)
{
    for (int i = 0; i < n_rows; ++i)
    {
        rows_[i] *= n;
    }
    return *this;
}

const Matrix Matrix::operator+(const Matrix &mtx)
{
    Matrix new_mtx = Matrix(n_rows, rows_[0].size);

    for (int i = 0; i < n_rows; ++i)
    {
        new_mtx.rows_[i] = rows_[i].operator+(mtx.rows_[i]);
    }
    return new_mtx;
}

const void Matrix::operator=(const Matrix mtx)
{
    n_rows = mtx.n_rows;
}

const bool Matrix::operator==(const Matrix &mtx)
{
    
    for (int i = 0; i < n_rows; ++i)
    {
        if (!(rows_[i] == mtx.rows_[i]))
        {
            return false;
        }
        
    }
    return true;
}

const bool Matrix::operator!=(const Matrix &mtx)
{
    return !(this->operator==(mtx));
}



std::ostream& operator<<(std::ostream& os, Matrix& mtx)
{
    os << "[";
    for (int i = 0; i < mtx.n_rows; ++i)
    {
        if (i == mtx.n_rows - 1)
        {
            os << mtx.rows_[i];    
        }
        else
        {
            os << mtx.rows_[i] << "\n";
        }
        
    }
    os << "]";
    return os;
}

Matrix::~Matrix()
{
    //std::cout << "Matrix destructor at " << this << std::endl;
    delete[] rows_;
}

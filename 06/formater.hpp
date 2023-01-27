#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "error.hpp"


/*
format будет собирать все
внутри будет функция для преобразования в строки
*/





template <class T>
int to_str(std::vector<std::string>& params, T& val)
{
    //std::ostream os;
    std::stringstream buf;
    
    //os << val;
    //buf << os.rdbuf();
    buf << val;
    params.push_back(buf.str());

    return 0;
}

template <class T, class... ArgsT>
int to_str(std::vector<std::string>& params, T& val, ArgsT&&... args)
{
    int res = to_str(params, val);
    if (res == 0)
    {
        return to_str(params, std::forward<ArgsT>(args)...);
    }
    else
    {
        throw Error("Error occured while converting to string", __FILE__, __LINE__);
        return 1;
    }
}

template <class... ArgsT>
std::string format(std::string seq, ArgsT... args)
{
    std::vector<std::string> params;
    // Результат функции
    std::string formatted = "";
    // Хранение индекса
    std::string num = "";
    int idx = 0;
    // ПРоверяем правильность скобок
    int balance = 0;

    int res = to_str(params, args...);
    
    if (res != 0)
    {
        throw Error("Error occured while converting to string", __FILE__, __LINE__);   
    }

    int i = 0;
    while (i < seq.length())
    {
        if (seq[i] == '{')
        {
            if (balance == 1)
            {
                throw Error("Invalid nested curly braces", __FILE__, __LINE__);
            }
            else
            {
                ++balance;
                ++i;

                if (std::isdigit(seq[i]))
                {
                    num += seq[i];
                }
                else
                {
                    throw Error("Invalid character inside curly braces", __FILE__, __LINE__);
                }
                ++i;
            }
            
        }

        else if (balance == 1)
        {
            if (std::isdigit(seq[i]))
                {
                    num += seq[i];
                    ++i;
                }
                else
                {
                    throw Error("Invalid character inside curly braces", __FILE__, __LINE__);
                }       
        }

        if (seq[i] == '}')
        {
            if (balance == 0)
            {
                throw Error("Invalid curly braces: closing brace before opening", __FILE__, __LINE__);
            }
            else
            {
                --balance;
                idx = std::stoi(num);
                formatted += params[idx];
                num = "";
                idx = 0;
                ++i;
            }
        }
        else
        {
            formatted += seq[i];
            ++i;
        }
    }

    return formatted;
}
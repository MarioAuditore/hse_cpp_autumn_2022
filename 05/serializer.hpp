#pragma once
#include <iostream>
#include <sstream>
#include <string>


enum class Error
{
    NoError,
    CorruptedArchive
};


struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

class Serializer
{
    static constexpr char Separator = ' ';
    std::ostream* out_;

public:
    explicit Serializer(std::ostream* out)
        : out_(out)
    {
    }

    template <class T>
    Error save(T& object)
    {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args)
    {
        return process(args...);
    }

    Error process(bool &arg)
    {
        std::cout << "Bool got argument: " << arg << std::endl;
        
        if (arg)
        {
            *out_ << "true" << Separator;

            std::cout << "True added" << std::endl;
            return Error::NoError;
        }
        
        if (!arg)
        {
            *out_ << "false" << Separator;

            std::cout << "false added" << std::endl;
            return Error::NoError;
        }
        return Error::CorruptedArchive;
    }

    Error process(uint64_t &arg)
    {
        std::cout << "Uint got argument: " << arg << std::endl;

        std::string buf = std::to_string(arg);
        *out_ << buf << Separator;
        
        return Error::NoError;
    }

    template <class T, class... ArgsT>
    Error process(T& val, ArgsT&&... args)
    {
        Error err = process(val);

        if (err == Error::CorruptedArchive)
        {
            return Error::CorruptedArchive;
        }
        else
        {
            return process(std::forward<ArgsT>(args)...);
        }
    }
};


bool isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}


class Deserializer
{
    static constexpr char Separator = ' ';
    std::istream* in_;

public:
    explicit Deserializer(std::istream* in)
        : in_(in)
    {
    }

    template <class T>
    Error load(T& object)
    {
        return object.deserialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args)
    {
        return process(args...);
    }

    Error process(bool &arg)
    {
        std::string buf;
        *in_ >> buf;
        std::cout << "Deserialize bool got: " << buf << std::endl;
        
        if (buf == "true")
        {
            arg = true;
            std::cout << "True converted" << std::endl;
            return Error::NoError;
        }
        
        if (buf == "false")
        {
            arg = false;
            std::cout << "false converted" << std::endl;
            return Error::NoError;
        }

        return Error::CorruptedArchive;
    }

    Error process(uint64_t &arg)
    {
        std::string buf;
        *in_ >> buf;
        std::cout << "Deserialize uint got: " << buf << std::endl;
        if (isNumber(buf))
        {
            arg = std::stoi(buf);

            std::cout << buf <<" converted" << std::endl;

            return Error::NoError;
        }
        else
        {
            return Error::CorruptedArchive;
        }
    }

    template <class T, class... ArgsT>
    Error process(T& val, ArgsT&&... args)
    {
        Error err = process(val);

        if (err == Error::CorruptedArchive)
        {
            return Error::CorruptedArchive;
        }
        else
        {
            return process(std::forward<ArgsT>(args)...);
        }
    }
};
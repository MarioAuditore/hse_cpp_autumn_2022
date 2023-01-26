#pragma once

struct Error
{
    std::string message_;
    const char* fileName_;
    int line_;
    Error(const std::string& message, const char* fileName, int line) : 
    message_(message), fileName_(fileName), line_(line)
    {}
};

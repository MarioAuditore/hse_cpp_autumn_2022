#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class TokenParser

{
    protected:

    std::string(*start_callback)(std::string);
    std::string(*end_callback)(std::string);
    uint64_t(*digit_token_callback)(uint64_t);

    public:

    std::vector<std::string> string_tokens;
    std::vector<uint64_t> digit_tokens;

    TokenParser()
    {
        start_callback = nullptr;
        end_callback = nullptr;
        digit_token_callback = nullptr;
    };



    // Устанавливаем callback-функцию перед стартом парсинга.

    void SetStartCallback(std::string (*callback_func)(std::string));



    // Устанавливаем callback-функцию после окончания парсинга.

    void SetEndCallback(std::string (*callback_func)(std::string));



    // Устанавливаем callback-функцию для обработки чисел.

    void SetDigitTokenCallback(uint64_t (*callback_func)(uint64_t));



    // Тут другие методы для установки callback-функций.

    //...

    void Parse(const std::string line);

};




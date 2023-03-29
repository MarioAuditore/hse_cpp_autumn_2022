#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>


using digit_func = uint64_t (*)(uint64_t i);
using letter_func = std::string (*)(std::string str);

class TokenParser

{
    protected:

    std::string(*start_callback)(std::string);
    std::string(*end_callback)(std::string);
    uint64_t(*digit_token_callback)(uint64_t);
    std::string(*letter_token_callback)(std::string);

    public:

    TokenParser()
    {
        start_callback = nullptr;
        end_callback = nullptr;
        digit_token_callback = nullptr;
        letter_token_callback = nullptr;
    }


    // Устанавливаем callback-функцию перед стартом парсинга.

    void SetStartCallback(std::string (*callback_func)(std::string));



    // Устанавливаем callback-функцию после окончания парсинга.

    void SetEndCallback(std::string (*callback_func)(std::string));



    // Устанавливаем callback-функцию для обработки чисел.

    void SetDigitTokenCallback(uint64_t (*callback_func)(uint64_t));



    // Тут другие методы для установки callback-функций.

    void SetLetterTokenCallback(std::string (*callback_func)(std::string));


    std::string Parse(const std::string line);

};




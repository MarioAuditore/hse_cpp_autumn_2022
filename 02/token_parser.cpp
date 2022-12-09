#include "token_parser.hpp"

void TokenParser::SetStartCallback(std::string (*callback_func)(std::string))
{
    start_callback = callback_func;
}

void TokenParser::SetEndCallback(std::string (*callback_func)(std::string))
{
    end_callback = callback_func;
}

void TokenParser::SetDigitTokenCallback(uint64_t (*callback_func)(uint64_t))
{
    digit_token_callback = callback_func;
}

void TokenParser::Parse(const std::string line)
{
    std::cout << "Parsing started\n";
    std::string line_processed = line;

    if (start_callback != nullptr)
    {
        line_processed = start_callback(line_processed);
    }

    // Парсинг
    std::istringstream split_stream(line_processed);

    std::string line_split, tab_split, space_split;
    std::istringstream line_stream, tab_stream;

    uint64_t digit_buf;
    
    while(getline(split_stream, line_split, '\n'))
    {
        line_stream = std::istringstream(line_split);
        while(getline(line_stream, tab_split, '\t'))
        {
            tab_stream = std::istringstream(tab_split);
            while(getline(tab_stream, space_split, ' '))
            {
                try 
                {
                    digit_buf = std::stoull(space_split, nullptr, 10);
                    
                    digit_tokens.push_back(digit_buf);
                }
                catch (std::invalid_argument &)
                {
                    string_tokens.push_back(space_split);
                }
                catch (std::out_of_range &)
                {
                    string_tokens.push_back(space_split);
                }
                
            }
        }
    }
    

    // Постобработка
    if (end_callback !=nullptr)
    {
        for (auto it = begin(string_tokens); it != end(string_tokens); ++it)
        {
            *it = end_callback(*it);
        }
    }
    
    if (digit_token_callback != nullptr)
    {
        for (auto it = begin(digit_tokens); it != end(digit_tokens); ++it)
        {
            *it = digit_token_callback(*it);
        }
    }
}

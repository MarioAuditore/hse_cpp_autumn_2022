#include "token_parser.hpp"

void TokenParser::SetStartCallback(letter_func callback_func)
{
    start_callback = callback_func;
}

void TokenParser::SetEndCallback(letter_func callback_func)
{
    end_callback = callback_func;
}

void TokenParser::SetDigitTokenCallback(digit_func callback_func)
{
    digit_token_callback = callback_func;
}

void TokenParser::SetLetterTokenCallback(letter_func callback_func)
{
    letter_token_callback = callback_func;
}


bool isDigit(std::string str) {
    for (auto ch : str) {
        if (std::isdigit(ch) == 0)
            return false;
    }
    return true;
}


std::string TokenParser::Parse(const std::string line)
{
    std::cout << "Parsing started\n";
    std::string tokens = "";
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
    uint64_t processed;
    
    while(getline(split_stream, line_split, '\n'))
    {
        line_stream = std::istringstream(line_split);
        while(getline(line_stream, tab_split, '\t'))
        {
            tab_stream = std::istringstream(tab_split);
            while(getline(tab_stream, space_split, ' '))
            {
                if (space_split == " " || space_split == "")
                {
                    continue;
                }

                try 
                {
                    if (digit_token_callback != nullptr and isDigit(space_split))
                    {
                        digit_buf = std::stoull(space_split, nullptr, 10);
                        processed = digit_token_callback(digit_buf);
                        tokens = tokens + " " +  std::to_string(processed);
                    }
                    else
                    {
                        if (letter_token_callback != nullptr)
                        {
                            tokens = tokens + " " +  letter_token_callback(space_split);
                        }
                        else
                        {
                            tokens = tokens + " " +  space_split;
                        }
                    }
                }
                catch (std::invalid_argument &)
                {
                    if (letter_token_callback != nullptr)
                    {
                        tokens = tokens + " " +  letter_token_callback(space_split);
                    }
                    else
                    {
                        tokens = tokens + " " +  space_split;
                    }
                }
                catch (std::out_of_range &)
                {
                    if (letter_token_callback != nullptr)
                    {
                        tokens = tokens + " " +  letter_token_callback(space_split);
                    }
                    else
                    {
                        tokens = tokens + " " +  space_split;
                    }
                }
                
            }
        }
    }
    

    // Постобработка
    if (end_callback !=nullptr)
    {
        tokens = end_callback(tokens);
    }
    
    if (tokens == "") {
        return line;
    }
    return tokens;
}

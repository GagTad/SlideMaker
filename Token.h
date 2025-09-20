#pragma once

#include <iostream>
#include <vector>

enum class TokenType{

    COMMAND,
    SHAPE_TYPE,
    NUMBER,
    STRING_LITERAL,
    OPTION,
    UNKNOWN,
    END_OF_INPUT

};

struct Token
{
    TokenType type;
    std::string value;
    
};

#pragma once

#include <string>
#include "TokenType.h"

struct Token {
    TokenType type;
    std::string value;


    std::string toString() const;
};
#pragma once
#include <string>
#include "Token.h"

class Lexer {
public:
    Lexer(const std::string& input);
    Token getNextToken();

private:
    std::string m_input;
    size_t m_position;
    char m_currentChar;

    void advance();
    void skipWhitespace();
    Token makeNumber();
    Token makeString();
    Token makeIdentifier();
    Token makeFlag();
};

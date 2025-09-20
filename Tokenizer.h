#pragma once
#include "Token.h"

class Tokenizer
{
 public:
    std::vector<Token> tokenize(int argc , char* argv[]);
 
 private:
    TokenType identify_token_type(const std::string& arg);
    
    
};

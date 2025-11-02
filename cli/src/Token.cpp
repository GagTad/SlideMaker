#include "Token.h"

std::string Token::toString() const{

        std::string typeStr;
        switch (type) {
        case TokenType::CREATE_SLIDE: typeStr = "CREATE_SLIDE"; break;
        case TokenType::LIST_SLIDES:  typeStr = "LIST_SLIDES";  break;
        case TokenType::SELECT_SLIDE: typeStr = "SELECT_SLIDE"; break;
        case TokenType::ADD:          typeStr = "ADD";          break;
        case TokenType::EXPORT:       typeStr = "EXPORT";       break;
        case TokenType::IDENTIFIER:   typeStr = "IDENTIFIER";   break;
        case TokenType::NUMBER:       typeStr = "NUMBER";       break;
        case TokenType::STRING_LITERAL: typeStr = "STRING_LITERAL"; break;
        case TokenType::FLAG:         typeStr = "FLAG";         break;
        case TokenType::END_OF_INPUT: typeStr = "END_OF_INPUT"; break;
        case TokenType::UNKNOWN:      typeStr = "UNKNOWN";      break;
        }
        return "Token(" + typeStr + ", '" + value + "')";
}

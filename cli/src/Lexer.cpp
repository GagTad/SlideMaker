#include "Lexer.h"
#include <cctype> 
#include <map>

static std::map<std::string, TokenType> keywords = {
    {"create_slide", TokenType::CREATE_SLIDE},
    {"list_slides", TokenType::LIST_SLIDES},
    {"select_slide", TokenType::SELECT_SLIDE},
    {"add", TokenType::ADD},
    {"export", TokenType::EXPORT},
    {"export_slideshow", TokenType::EXPORT_SLIDESHOW},
    {"save", TokenType::SAVE},
    {"undo", TokenType::UNDO}, 
    {"redo", TokenType::REDO} 
};

Lexer::Lexer(const std::string& input) : m_input(input), m_position(0) {
    m_currentChar = (m_position < m_input.length()) ? m_input[m_position] : '\0';
}

void Lexer::advance() {
    m_position++;
    m_currentChar = (m_position < m_input.length()) ? m_input[m_position] : '\0';
}

void Lexer::skipWhitespace() {
    while (m_currentChar != '\0' && isspace(m_currentChar)) advance();
}

Token Lexer::makeNumber() {
    std::string result = "";
    while (m_currentChar != '\0' && isdigit(m_currentChar)) {
        result += m_currentChar;
        advance();
    }
    return { TokenType::NUMBER, result };
}

Token Lexer::makeString() {
    std::string result = "";
    advance();
    while (m_currentChar != '\0' && m_currentChar != '"') {
        result += m_currentChar;
        advance();
    }
    advance();
    return { TokenType::STRING_LITERAL, result };
}

Token Lexer::makeIdentifier() {
    std::string result = "";
    while (m_currentChar != '\0' && (isalnum(m_currentChar) || m_currentChar == '_')) {
        result += m_currentChar;
        advance();
    }
    if (keywords.count(result)) return { keywords[result], result };
    return { TokenType::IDENTIFIER, result };
}

Token Lexer::makeFlag() {
    std::string result = "";
    if (m_currentChar == '-' && m_position + 1 < m_input.length() && m_input[m_position + 1] == '-') {
        advance(); advance();
        while (m_currentChar != '\0' && isalpha(m_currentChar)) {
            result += m_currentChar;
            advance();
        }
        return { TokenType::FLAG, "--" + result };
    }
    std::string unknown_char(1, m_currentChar);
    advance();
    return { TokenType::UNKNOWN, unknown_char };
}

Token Lexer::getNextToken() {
    while (m_currentChar != '\0') {
        if (isspace(m_currentChar)) { skipWhitespace(); continue; }
        if (isdigit(m_currentChar)) return makeNumber();
        if (isalpha(m_currentChar)) return makeIdentifier();
        if (m_currentChar == '"') return makeString();
        if (m_currentChar == '-') return makeFlag();

        std::string unknown_char(1, m_currentChar);
        advance();
        return { TokenType::UNKNOWN, unknown_char };
    }
    return { TokenType::END_OF_INPUT, "" };
}

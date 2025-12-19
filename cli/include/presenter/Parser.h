#pragma once
#include <vector>
#include <memory> 
#include "Token.h"
#include "Command.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens);
    std::unique_ptr<Command> parse();

private:
    std::vector<Token> m_tokens;
    size_t m_position;
    Token& peek();
    Token& consume();
    bool isAtEnd();

    std::unique_ptr<Command> parseCreateSlide();
    std::unique_ptr<Command> parseSelectSlide();
    std::unique_ptr<Command> parseListSlides();
    std::unique_ptr<Command> parseAdd();
    std::unique_ptr<Command> parseExport();
    std::unique_ptr<Command> parseSave(); 
    std::unique_ptr<Command> parseExportSlideshow();
};

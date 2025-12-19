#include "Parser.h"
#include <stdexcept> 

Parser::Parser(const std::vector<Token>& tokens) : m_tokens(tokens), m_position(0) {}

Token& Parser::peek() { return m_tokens[m_position]; }
Token& Parser::consume() { if (!isAtEnd()) m_position++; return m_tokens[m_position - 1]; }
bool Parser::isAtEnd() { return m_position >= m_tokens.size(); }

std::unique_ptr<Command> Parser::parse() {
    if (isAtEnd()) return nullptr;
    Token& firstToken = peek();
    switch (firstToken.type) {
    case TokenType::CREATE_SLIDE: return parseCreateSlide();
    case TokenType::SELECT_SLIDE: return parseSelectSlide();
    case TokenType::LIST_SLIDES:  return parseListSlides();
    case TokenType::ADD:          return parseAdd();
    case TokenType::EXPORT:       return parseExport();
    case TokenType::EXPORT_SLIDESHOW: return parseExportSlideshow();
    case TokenType::SAVE:         return parseSave();
    case TokenType::UNDO:
        consume();
        return std::make_unique<UndoCommand>();
    case TokenType::REDO:
        consume();
        return std::make_unique<RedoCommand>();

    default: throw std::runtime_error("Syntax Error: Unknown command '" + firstToken.value + "'");
    }
}

std::unique_ptr<Command> Parser::parseCreateSlide() {
    consume();
    if (isAtEnd() || peek().type != TokenType::STRING_LITERAL) throw std::runtime_error("Expected slide name.");
    auto cmd = std::make_unique<CreateSlideCommand>();
    cmd->slideName = consume().value;
    return cmd;
}

std::unique_ptr<Command> Parser::parseSelectSlide() {
    consume();
    if (isAtEnd() || peek().type != TokenType::NUMBER) throw std::runtime_error("Expected slide ID.");
    auto cmd = std::make_unique<SelectSlideCommand>();
    cmd->slideId = std::stoi(consume().value);
    return cmd;
}

std::unique_ptr<Command> Parser::parseListSlides() {
    consume();
    return std::make_unique<ListSlidesCommand>();
}

std::unique_ptr<Command> Parser::parseExport() {
    consume();
    if (isAtEnd() || (peek().type != TokenType::STRING_LITERAL && peek().type != TokenType::IDENTIFIER)) throw std::runtime_error("Expected filename.");
    auto cmd = std::make_unique<ExportCommand>();
    cmd->filename = consume().value;
    return cmd;
}

std::unique_ptr<Command> Parser::parseExportSlideshow() {
    consume();
    if (isAtEnd() || peek().type != TokenType::STRING_LITERAL) throw std::runtime_error("Expected filename.");
    auto cmd = std::make_unique<ExportSlideshowCommand>();
    cmd->filename = consume().value;
    return cmd;
}

std::unique_ptr<Command> Parser::parseSave() {
    consume();
    if (isAtEnd() || peek().type != TokenType::STRING_LITERAL) throw std::runtime_error("Expected filename.");
    auto cmd = std::make_unique<SaveCommand>();
    cmd->filename = consume().value;
    return cmd;
}

std::unique_ptr<Command> Parser::parseAdd() {
    consume();

    if (isAtEnd() || peek().type != TokenType::IDENTIFIER) {
        throw std::runtime_error("Syntax Error: Expected shape type after 'add'");
    }

    auto cmd = std::make_unique<AddShapeCommand>();
    cmd->shapeType = consume().value;
    while (!isAtEnd() && peek().type == TokenType::NUMBER) {
        cmd->params.push_back(std::stoi(consume().value));
    }

    while (!isAtEnd() && peek().type == TokenType::FLAG) {
        std::string flagName = consume().value; 

        if (isAtEnd()) {
            throw std::runtime_error("Syntax Error: Expected value after flag '" + flagName + "'");
        }
        if (peek().type != TokenType::STRING_LITERAL &&
            peek().type != TokenType::IDENTIFIER &&
            peek().type != TokenType::NUMBER) {
            throw std::runtime_error("Syntax Error: Expected valid value after flag '" + flagName + "'");
        }

        std::string flagValue = consume().value;
        cmd->flags[flagName] = flagValue;
    }

    return cmd;
}

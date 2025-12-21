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
    case TokenType::LIST_SHAPES: return parseListShapes();
    case TokenType::ADD:          return parseAdd();
    case TokenType::REMOVE_SHAPE: return parseRemoveShape();
    case TokenType::CLEAR_SLIDE: return parseClearSlide();
    case TokenType::EXPORT:       return parseExport();
    case TokenType::MOVE_SHAPE: return parseMoveShape();
    case TokenType::EXPORT_SLIDESHOW: return parseExportSlideshow();
    case TokenType::SAVE:         return parseSave();
    case TokenType::DUPLICATE_SLIDE: return parseDuplicateSlide();
    case TokenType::MOVE_SLIDE: return parseMoveSlide();
	case TokenType::SCALE_SHAPE: return parseScaleShape();
	case TokenType::RECOLOR_SHAPE: return parseRecolorShape();
    case TokenType::BRING_FRONT: return parseZOrder(true);
    case TokenType::SEND_BACK: return parseZOrder(false);
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

std::unique_ptr<Command> Parser::parseListShapes() {
    consume(); // "ուտում" ենք list_shapes բառը
    return std::make_unique<ListShapesCommand>();
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

std::unique_ptr<Command> Parser::parseMoveSlide() {
    consume(); // move_slide

    if (isAtEnd() || peek().type != TokenType::NUMBER) throw std::runtime_error("Expected source slide ID.");
    int from = std::stoi(consume().value);

    if (isAtEnd() || peek().type != TokenType::NUMBER) throw std::runtime_error("Expected destination slide ID.");
    int to = std::stoi(consume().value);

    auto cmd = std::make_unique<MoveSlideCommand>();
    cmd->fromId = from;
    cmd->toId = to;
    return cmd;
}

std::unique_ptr<Command> Parser::parseDuplicateSlide() {
    consume(); // duplicate_slide
    if (isAtEnd() || peek().type != TokenType::NUMBER) throw std::runtime_error("Expected slide ID to duplicate.");
    auto cmd = std::make_unique<DuplicateSlideCommand>();
    cmd->slideId = std::stoi(consume().value);
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

std::unique_ptr<Command> Parser::parseRemoveShape() {
    consume();
    if (isAtEnd() || peek().type != TokenType::NUMBER) throw std::runtime_error("Expected shape index.");
    auto cmd = std::make_unique<RemoveShapeCommand>();
    cmd->shapeIndex = std::stoi(consume().value);
    return cmd;
}

std::unique_ptr<Command> Parser::parseClearSlide() {
    consume();
    return std::make_unique<ClearSlideCommand>();
}

std::unique_ptr<Command> Parser::parseZOrder(bool toFront) {
    consume(); // command name
    if (isAtEnd() || peek().type != TokenType::NUMBER) throw std::runtime_error("Expected shape index.");

    auto cmd = std::make_unique<ZOrderCommand>();
    cmd->shapeIndex = std::stoi(consume().value);
    cmd->toFront = toFront;
    return cmd;
}


std::unique_ptr<Command> Parser::parseMoveShape() {
    consume();
    if (isAtEnd() || peek().type != TokenType::NUMBER) throw std::runtime_error("Expected index.");
    int idx = std::stoi(consume().value);

    if (isAtEnd() || peek().type != TokenType::NUMBER) throw std::runtime_error("Expected X.");
    int x = std::stoi(consume().value);

    if (isAtEnd() || peek().type != TokenType::NUMBER) throw std::runtime_error("Expected Y.");
    int y = std::stoi(consume().value);

    auto cmd = std::make_unique<MoveShapeCommand>();
    cmd->shapeIndex = idx;
    cmd->newX = x;
    cmd->newY = y;
    return cmd;
}

std::unique_ptr<Command> Parser::parseScaleShape() {
    consume();
    int idx = std::stoi(consume().value);
    double factor = std::stod(consume().value); // stod - string to double
    auto cmd = std::make_unique<ScaleShapeCommand>();
    cmd->index = idx; cmd->factor = factor;
    return cmd;
}

std::unique_ptr<Command> Parser::parseRecolorShape() {
    consume();
    int idx = std::stoi(consume().value);
    if (peek().type != TokenType::STRING_LITERAL) throw std::runtime_error("Expected color string.");
    std::string color = consume().value;
    auto cmd = std::make_unique<RecolorShapeCommand>();
    cmd->index = idx; cmd->newColor = color;
    return cmd;
}

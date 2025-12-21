#include "Editor.h"
#include "Lexer.h"
#include "Parser.h"
#include "ShapeFactory.h"
#include <fstream>
#include <iostream>

Editor::Editor() : m_executor(m_presentation) {
    auto& registry = ShapeRegistry::getInstance();
    registry.registerShape("circle", std::make_unique<CircleFactory>());
    registry.registerShape("rectangle", std::make_unique<RectangleFactory>());
    registry.registerShape("line", std::make_unique<LineFactory>());
    registry.registerShape("text", std::make_unique<TextFactory>());
    registry.registerShape("image", std::make_unique<ImageFactory>());
    registry.registerShape("ellipse", std::make_unique<EllipseFactory>());
    registry.registerShape("triangle", std::make_unique<TriangleFactory>());
    registry.registerShape("polygon", std::make_unique<PolygonFactory>());
}

void Editor::run(const std::string& inputFilePath) {
    std::ifstream file(inputFilePath);
    if (!file.is_open()) {
        std::cerr << "CRITICAL ERROR: Could not open file '" << inputFilePath << "'." << std::endl;
        return;
    }
    std::cout << "--- Editor Started: Processing '" << inputFilePath << "' ---" << std::endl;
    std::string line;
    while (std::getline(file, line)) {
        size_t comment_pos = line.find('//');
        if (comment_pos != std::string::npos) line = line.substr(0, comment_pos);
        if (line.empty() || line.find_first_not_of(" \t\n\r") == std::string::npos) continue;
        std::cout << ">> " << line << std::endl;
        processLine(line);
    }
    std::cout << "--- Editor Finished ---" << std::endl;
}

void Editor::processLine(const std::string& line) {
    try {
        Lexer lexer(line);
        std::vector<Token> tokens;
        Token token = lexer.getNextToken();
        while (token.type != TokenType::END_OF_INPUT) {
            tokens.push_back(token);
            token = lexer.getNextToken();
        }
        if (tokens.empty()) return;
        Parser parser(tokens);
        std::unique_ptr<Command> command = parser.parse();
        if (command) {
            m_executor.execute(std::move(command));
        }
    }
    catch (const std::exception& e) {
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
}

void Editor::runInteractive() {
    std::string line;
    while (true) {
        std::cout << "CMD> "; 
        if (!std::getline(std::cin, line)) break; 
        size_t first = line.find_first_not_of(" \t\r\n");
        if (first == std::string::npos) continue; 
        if (line == "exit" || line == "quit") {
            std::cout << "Exiting interactive mode..." << std::endl;
            break;
        }
        processLine(line);
    }
}

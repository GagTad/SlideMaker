#include <iostream>   
#include <fstream>    
#include <string>    
#include <vector>      
#include <memory>      

#include "Presentation.h"
#include "Lexer.h"
#include "Parser.h"
#include "Executor.h"
#include "ShapeFactory.h" 


void initializeShapeFactories() {
    auto& registry = ShapeRegistry::getInstance();
    registry.registerShape("circle", std::make_unique<CircleFactory>());
    registry.registerShape("rectangle", std::make_unique<RectangleFactory>());
    registry.registerShape("line", std::make_unique<LineFactory>());


}

void process_command(const std::string& line, Executor& executor) {
    try {
        
        Lexer lexer(line);
        std::vector<Token> tokens;
        Token token = lexer.getNextToken();
        while (token.type != TokenType::END_OF_INPUT) {
            tokens.push_back(token);
            token = lexer.getNextToken();
        }

       
        if (tokens.empty()) {
            return;
        }

        
        Parser parser(tokens);
        std::unique_ptr<Command> command = parser.parse();

        if (command) {
            executor.execute(command);
        }

    }
    catch (const std::runtime_error& e) {
       
        std::cerr << "[ERROR] " << e.what() << std::endl;
    }
}


int main() {
 
    initializeShapeFactories();
    std::cout << "Application initialized." << std::endl;

    Presentation presentation;
    Executor executor(presentation);

    std::string filename = "commands.prs";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "CRITICAL ERROR: Could not open file '" << filename << "'." << std::endl;
        return 1; 
    }

    std::cout << "Reading commands from '" << filename << "'..." << std::endl << std::endl;

    std::string line;
    while (std::getline(file, line)) {

        
        size_t comment_pos = line.find('#');
        if (comment_pos != std::string::npos) {
            line = line.substr(0, comment_pos);
        }

        
        if (line.empty() || line.find_first_not_of(" \t\n\r") == std::string::npos) {
            continue; 
        }

        std::cout << "--- Processing: \"" << line << "\" ---" << std::endl;
        process_command(line, executor);
        std::cout << std::endl; 
    }

    file.close(); 

    std::cout << "Finished processing file." << std::endl;

    return 0;
}

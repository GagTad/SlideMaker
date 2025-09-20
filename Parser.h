#pragma once 

#include "Token.h"
#include "Command.h"
#include <vector>
#include <memory>
#include "Shape.h"

class Parser{
    public:
    explicit Parser(std::vector<Token> tokens);
    
    std::unique_ptr<Command> parse();

    private:
    std::vector<Token> m_tokens;
    size_t m_position = 0;

    const Token& current_token() const;
    void advance(); //hajord tokeny sharjvel

    void expect(TokenType type , const std::string& error_message); //stugum e vor current token y chisht e ,,->araj a gnum ,sxali depqum message talis

    std::unique_ptr<Command> parse_create_slide();
    std::unique_ptr<Command> parse_list_slides();
    std::unique_ptr<Command> parse_add_command();
    //mnacacy petqa avelacnel hly
    std::unique_ptr<Shape> parse_circle();
    std::unique_ptr<Shape> parse_square();
    //----------------------------
};
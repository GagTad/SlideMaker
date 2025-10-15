#include "Tokenizer.h"
#include <stdexcept>  

std::vector<Token> Tokenizer::tokenize(int argc , char* argv[]){

    std::vector<Token> tokens;

    for (int i = 1 ; i < argc ; ++i)
    {
        std::string arg_str = argv[i];

        TokenType type = identify_token_type(arg_str);

        tokens.push_back({type , arg_str});
        

    }

    tokens.push_back({TokenType::END_OF_INPUT , " "});
    
    return tokens;

}

TokenType Tokenizer::identify_token_type(const std::string& arg){

    if(arg.rfind("--", 0 ) == 0) //rfind  stugum e ardyoq toghy sksvum 1 -- ov
    {
        return TokenType::OPTION;
        

    }

    if(arg == "create_slide" || arg =="list_slide" || arg == "select_slide" || arg == "add" )
    {
        return TokenType::COMMAND;
    }

    if(arg == "text" || arg == "line" || arg == "square" || arg == "rectangle" || arg == "parallelogram" || arg == "triangle" || arg == "circle" || arg == "elipse " || arg == "arrow")
    {
        return TokenType::SHAPE_TYPE;
    }

    try {

        std::stod(arg); // toghy dardznum en q double
        return TokenType::NUMBER;

    } catch (const std::invalid_argument& e)
    {
        //ete chstacvec uremn tiv chi , ancnum en q araj
    }

    return TokenType::STRING_LITERAL;
}

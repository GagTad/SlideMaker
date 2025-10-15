#include "Parser.h"
#include <stdexcept>  

Parser::Parser(std::vector<Token> tokens) 
    :m_tokens(std::move(tokens)) , m_position(0){}


const Token& Parser::current_token() const{
    return m_tokens[m_position];
}

void Parser::advance(){

    if(m_position < m_tokens.size())
    {
        m_position++;
    }
}

void Parser::expect(TokenType type , const std::string& error_message){

    if(current_token().type != type )
    {
        throw std::runtime_error(error_message);
    }
    advance();
}


std::unique_ptr<Command> Parser::parse(){
    //arajiny misht hraman petq e lini
    const auto& token  =  current_token();
    if(token.type != TokenType::COMMAND)
    {
        throw std::runtime_error("ERROR! ,  expected 'add', 'create_slide' ...");
    }
    if(token.value == "create_slide"){
        return parse_create_slide();
    }else if(token.value == "list_slieds"){
        return parse_list_slides();
    }else if(token.value == "add"){
        return parse_add_command();
    }
    //avelacnel add ev mnacac funkcianery !!!!!
    else {
        throw std::runtime_error("ERROR : unknown commandd " + token.value + "':");
    }
}

//create slide
std::unique_ptr<Command> Parser::parse_create_slide(){
    advance();
    std::string slide_name = current_token().value;
    expect(TokenType::STRING_LITERAL , "ERROR :  after 'create_slide'  expected name of slide") ;
    
    auto cmp = std::make_unique<CrateSlideCommand>();
    cmp->slide_name = slide_name;
    return cmp;
}

//list_slides
std::unique_ptr<Command> Parser::parse_list_slides(){
    advance();
    //parametr chuni 

    return std::make_unique<ListSlideCommand>();
}

std::unique_ptr<Command> Parser::parse_add_command(){
    advance();
    const auto& shape_type_token = current_token(); //stugum enq vor hajordy patkeri tesak e
    expect(TokenType::SHAPE_TYPE , "ERROR:, after 'add'   expected  shape type  'circle' ,'square' ...");


    std::unique_ptr<Shape> shape ;

    if(shape_type_token.value == "circle")
    {
        shape = parse_circle();
    }else if(shape_type_token.value == "square")
    {
        shape = parse_square();
    }
    ///else  if ov mnacac patkernery kavelacnenq



    auto cmd = std::make_unique<AddShapeCommand>();
    cmd->shape_to_add = std::move(shape); //shape i sepakanutyutyuny talis enq cmd in
    return cmd;
}

//circle

std::unique_ptr<Shape> Parser::parse_circle(){
    advance();
    //aknkalum enq 3 tiv cx,cy ,radius
    int cx = std::stoi(current_token().value);
    expect(TokenType::NUMBER , "ERROR : 'circle' Expected X coordinate of center.");

    int cy = std::stoi(current_token().value);
    expect(TokenType::NUMBER , "ERROR : 'circle' Expected X coordinate of center.");

    int radius =std::stoi(current_token().value);
    expect(TokenType::NUMBER , "ERROR : 'circle' Expected  a radius .");

    auto circle  =  std::make_unique<Circle>();
    circle->cx = cx;
    circle->cy = cy;
    circle->radius = radius;
    return circle;

}

//square

std::unique_ptr<Shape> Parser::parse_square(){
    advance();

    //aknkalum enq 3 tiv , x, y , side

    int x = std::stoi(current_token().value);
    expect(TokenType::NUMBER , "ERROR : 'square' Expected the X coordinate of the upper left corner.");

    int y = std::stoi(current_token().value);
    expect(TokenType::NUMBER , "ERROR : 'square' Expected the Y coordinate of the upper left corner.");

    int side = std::stoi(current_token().value);
    expect(TokenType::NUMBER , "ERROR : 'square' Expected the length of the side .");

    auto square = std::make_unique<Square>();
    square->x = x;
    square->y = y;
    square->side = side;
    return square;


}

#pragma once

#pragma once


enum class TokenType {

    // Keywords 
    CREATE_SLIDE,  
    LIST_SLIDES,    
    SELECT_SLIDE,   
    ADD,     
    EXPORT,

    // Literals
    IDENTIFIER,     
    NUMBER,         
    STRING_LITERAL,

    // Special Symbols
    FLAG,          

    // Meta Tokens
    END_OF_INPUT,   
    UNKNOWN         
};



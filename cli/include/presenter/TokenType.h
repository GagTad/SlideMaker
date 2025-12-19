#pragma once

enum class TokenType {
    CREATE_SLIDE,
    LIST_SLIDES,
    SELECT_SLIDE,
    ADD,
    EXPORT,
    EXPORT_SLIDESHOW,
    SAVE,
    UNDO, 
    REDO,

    IDENTIFIER,
    NUMBER,
    STRING_LITERAL,
    FLAG,

    END_OF_INPUT,
    UNKNOWN
};

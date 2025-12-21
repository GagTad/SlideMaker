#pragma once

enum class TokenType {
    CREATE_SLIDE,
    LIST_SLIDES,
    LIST_SHAPES,
    SELECT_SLIDE,
    ADD,
    REMOVE_SHAPE,
    CLEAR_SLIDE,
    EXPORT,
    EXPORT_SLIDESHOW,
    SAVE,
    UNDO, 
    REDO,
    DUPLICATE_SLIDE,
    BRING_FRONT, 
    SCALE_SHAPE,
    RECOLOR_SHAPE,
    MOVE_SLIDE,
    MOVE_SHAPE,
    SEND_BACK,

    IDENTIFIER,
    NUMBER,
    STRING_LITERAL,
    FLAG,

    END_OF_INPUT,
    UNKNOWN
};

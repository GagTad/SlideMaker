#pragma once

#include <string>
#include <vector>
#include <map>
#include "Token.h" 

struct Command {
    virtual ~Command() = default;
};

struct CreateSlideCommand : public Command {
    std::string slideName;
};


struct SelectSlideCommand : public Command {
    int slideId;
};


struct AddShapeCommand : public Command {
    std::string shapeType; 
    std::vector<int> params;
    std::map<std::string, std::string> flags;
};

struct ExportCommand : public Command {
    std::string filename;
};

struct ListSlidesCommand : public Command {};

#pragma once

#include <iostream>
#include <memory> 
#include "Shape.h"

struct Command{

    virtual ~Command() = default;
};

struct CrateSlideCommand : public Command{
    
    std::string slide_name;
};

struct ListSlideCommand : public Command{

    //tvyalner petq chem
};

struct SelectSlideCommand : public  Command {

        int slide_id;
};

struct AddShapeCommand : public Command{

    std::unique_ptr<Shape> shape_to_add;

};
// struct CircleData{
//     int cx;
//     int cy;
//     int radius;
// };

// struct AddCircleCommand : public Command {
//     CircleData data;
// };

// struct SquareData{
//     int x;
//     int y;
//     int side;
// };

// struct AddSquareCommand : public Command {
//     SquareData data;
// };

//avelacnelu ban ka ,,uxxankyun ,gic ....

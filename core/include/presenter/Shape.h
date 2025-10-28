#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory> 

class Shape {
public:
  
    virtual ~Shape() = default;

     
    std::map<std::string, std::string> flags;
};


 
class CircleShape : public Shape {
public:
  
    CircleShape(int cx, int cy, int r)
        : centerX(cx), centerY(cy), radius(r) {
    }

    
    int centerX, centerY, radius;
};

 
class RectangleShape : public Shape {
public:
    RectangleShape(int x_coord, int y_coord, int w, int h)
        : x(x_coord), y(y_coord), width(w), height(h) {
    }

    int x, y, width, height;
};

 
class LineShape : public Shape {
public:
    LineShape(int start_x, int start_y, int end_x, int end_y)
        : x1(start_x), y1(start_y), x2(end_x), y2(end_y) {
    }

    int x1, y1, x2, y2;
};
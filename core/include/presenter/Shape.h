#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory> 
#include <sstream>

class Shape {
public:
    virtual ~Shape() = default;
    virtual std::string toSvg() const = 0;
    std::map<std::string, std::string> flags;
};


class CircleShape : public Shape {
public:
    CircleShape(int cx, int cy, int r);
    std::string toSvg() const override; 

public:
    int centerX, centerY, radius;
};

 
class RectangleShape : public Shape {
public:
    RectangleShape(int x_coord, int y_coord, int w, int h);
    std::string toSvg() const override;

public:
    int x, y, width, height;
};

 
class LineShape : public Shape {
public:
    LineShape(int start_x, int start_y, int end_x, int end_y);
    std::string toSvg() const override;

public:
    int x1, y1, x2, y2;
};

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
    virtual std::string serialize() const = 0;
    std::map<std::string, std::string> flags;

protected:
    std::string flagsToString() const;
    std::string getSvgStyle() const;
};

class CircleShape : public Shape {
public:
    CircleShape(int cx, int cy, int r);
    std::string toSvg() const override;
    std::string serialize() const override;
    int centerX, centerY, radius;
};

class RectangleShape : public Shape {
public:
    RectangleShape(int x, int y, int w, int h);
    std::string toSvg() const override;
    std::string serialize() const override;
    int x, y, width, height;
};

class LineShape : public Shape {
public:
    LineShape(int x1, int y1, int x2, int y2);
    std::string toSvg() const override;
    std::string serialize() const override;
    int x1, y1, x2, y2;
};

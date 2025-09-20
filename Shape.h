#pragma once 

#include <string>


struct Shape {
    virtual ~Shape() = default;
};

struct Text : public Shape {
    int x, y;
    std::string content;
};

struct Line : public Shape {
    int x1, y1, x2, y2;
};

struct Square : public Shape {
    int x, y, side;
};

struct Rectangle : public Shape {
    int x, y, width, height;
};

struct Circle : public Shape {
    int cx, cy, radius;
};



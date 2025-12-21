#pragma once
#include <string>
#include <vector>
#include <map>
#include <memory> 
#include <sstream>
#include <utility>

class Shape {
public:
    virtual ~Shape() = default;
    virtual std::string toSvg() const = 0;
    virtual std::string serialize() const = 0;
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual std::pair<int, int> getPosition() const = 0;
    virtual void scale(double factor) = 0;

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
    std::unique_ptr<Shape> clone() const override;
    void setPosition(int x, int y) override;
    std::pair<int, int> getPosition() const override;
    void scale(double factor) override;

private:
    int centerX, centerY, radius;
};

class RectangleShape : public Shape {
public:
    RectangleShape(int x, int y, int w, int h);
    std::string toSvg() const override;
    std::string serialize() const override;
    std::unique_ptr<Shape> clone() const override;
    void setPosition(int x, int y) override;
    std::pair<int, int> getPosition() const override;
    void scale(double factor) override;

private:
    int x, y, width, height;
};

class LineShape : public Shape {
public:
    LineShape(int x1, int y1, int x2, int y2);
    std::string toSvg() const override;
    std::string serialize() const override;
    std::unique_ptr<Shape> clone() const override;
    void setPosition(int x, int y) override;
    std::pair<int, int> getPosition() const override;
    void scale(double factor) override;

private:
    int x1, y1, x2, y2;
};

class TextShape : public Shape {
public:
    TextShape(int x, int y, int fs);
    std::string toSvg() const override;
    std::string serialize() const override;
    std::unique_ptr<Shape> clone() const override;
    void setPosition(int x, int y) override;
    std::pair<int, int> getPosition() const override;
    void scale(double factor) override;

private:
    int x, y, fontSize;
};

class ImageShape : public Shape {
public:
    ImageShape(int x, int y, int w, int h);
    std::string toSvg() const override;
    std::string serialize() const override;
    std::unique_ptr<Shape> clone() const override;
    void setPosition(int x, int y) override;
    std::pair<int, int> getPosition() const override;
    void scale(double factor) override;

private: 
    int x, y, width, height;
};

class EllipseShape : public Shape {
public:
    EllipseShape(int cx, int cy, int rx, int ry);
    std::string toSvg() const override;
    std::string serialize() const override;
    std::unique_ptr<Shape> clone() const override;
    void setPosition(int x, int y) override;
    std::pair<int, int> getPosition() const override;
    void scale(double factor) override;

private:
    int cx, cy, rx, ry;
};

class TriangleShape : public Shape {
public:
    TriangleShape(int x1, int y1, int x2, int y2, int x3, int y3);
    std::string toSvg() const override;
    std::string serialize() const override;
    std::unique_ptr<Shape> clone() const override;
    void setPosition(int x, int y) override;
    std::pair<int, int> getPosition() const override;
    void scale(double factor) override;

private: 
    int x1, y1, x2, y2, x3, y3;
};

class PolygonShape : public Shape {
public:
    PolygonShape(const std::vector<int>& pts);
    std::string toSvg() const override;
    std::string serialize() const override;
    std::unique_ptr<Shape> clone() const override;
    void setPosition(int x, int y) override;
    std::pair<int, int> getPosition() const override;
    void scale(double factor) override;

private: 
    std::vector<int> points;
};

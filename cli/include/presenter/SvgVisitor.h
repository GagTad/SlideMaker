#pragma once
#include <string>
#include <sstream>
#include "IShapeVisitor.h"

class Shape;

class SvgVisitor : public IShapeVisitor {
public:
    std::string getSvgString() const;

    void reset();

    void visit(const CircleShape& shape) override;
    void visit(const RectangleShape& shape) override;
    void visit(const LineShape& shape) override;
    void visit(const TextShape& shape) override;
    void visit(const ImageShape& shape) override;
    void visit(const EllipseShape& shape) override;
    void visit(const TriangleShape& shape) override;
    void visit(const PolygonShape& shape) override;

private:
    std::stringstream m_ss;

    std::string getCommonStyle(const Shape& shape, bool isLine = false);
};
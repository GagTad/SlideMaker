#pragma once

class CircleShape;
class RectangleShape;
class LineShape;
class TextShape;
class ImageShape;
class EllipseShape;
class TriangleShape;
class PolygonShape;

class IShapeVisitor {
public:
    virtual ~IShapeVisitor() = default;

    virtual void visit(const CircleShape& shape) = 0;
    virtual void visit(const RectangleShape& shape) = 0;
    virtual void visit(const LineShape& shape) = 0;
    virtual void visit(const TextShape& shape) = 0;
    virtual void visit(const ImageShape& shape) = 0;
    virtual void visit(const EllipseShape& shape) = 0;
    virtual void visit(const TriangleShape& shape) = 0;
    virtual void visit(const PolygonShape& shape) = 0;
};
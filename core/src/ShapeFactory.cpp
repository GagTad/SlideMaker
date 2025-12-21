#include "ShapeFactory.h"
#include <stdexcept>

void ShapeRegistry::registerShape(const std::string& shapeType, std::unique_ptr<IShapeFactory> factory) {
    m_factories[shapeType] = std::move(factory);
}

std::unique_ptr<Shape> ShapeRegistry::createShape(const std::string& shapeType, const std::vector<int>& params) {
    if (m_factories.find(shapeType) == m_factories.end()) {
        throw std::runtime_error("Semantic Error: Unknown shape type '" + shapeType + "'.");
    }
    return m_factories.at(shapeType)->createShape(params);
}

std::unique_ptr<Shape> CircleFactory::createShape(const std::vector<int>& params) {
    if (params.size() != 3) throw std::runtime_error("Semantic Error: 'circle' requires 3 params (cx, cy, r).");
    if (params[2] < 0) throw std::runtime_error("Invariant Error: Circle radius cannot be negative.");
    return std::make_unique<CircleShape>(params[0], params[1], params[2]);
}

std::unique_ptr<Shape> RectangleFactory::createShape(const std::vector<int>& params) {
    if (params.size() != 4) throw std::runtime_error("Semantic Error: 'rectangle' requires 4 params (x, y, w, h).");
    if (params[2] < 0 || params[3] < 0) throw std::runtime_error("Invariant Error: Rectangle width/height cannot be negative.");
    return std::make_unique<RectangleShape>(params[0], params[1], params[2], params[3]);
}

std::unique_ptr<Shape> LineFactory::createShape(const std::vector<int>& params) {
    if (params.size() != 4) throw std::runtime_error("Semantic Error: 'line' requires 4 params (x1, y1, x2, y2).");
    return std::make_unique<LineShape>(params[0], params[1], params[2], params[3]);
}

std::unique_ptr<Shape> TextFactory::createShape(const std::vector<int>& params) {
    if (params.size() != 3) throw std::runtime_error("Semantic Error: 'text' requires 3 params (x, y, fontSize).");
    if (params[2] <= 0) throw std::runtime_error("Invariant Error: Font size must be positive.");
    return std::make_unique<TextShape>(params[0], params[1], params[2]);
}

std::unique_ptr<Shape> ImageFactory::createShape(const std::vector<int>& params) {
    if (params.size() != 4) throw std::runtime_error("Semantic Error: 'image' requires 4 params (x, y, w, h).");
    if (params[2] < 0 || params[3] < 0) throw std::runtime_error("Invariant Error: Image width/height cannot be negative.");
    return std::make_unique<ImageShape>(params[0], params[1], params[2], params[3]);
}

std::unique_ptr<Shape> EllipseFactory::createShape(const std::vector<int>& params) {
    if (params.size() != 4) throw std::runtime_error("Semantic Error: 'ellipse' requires 4 params (cx, cy, rx, ry).");
    if (params[2] < 0 || params[3] < 0) throw std::runtime_error("Invariant Error: Ellipse radii cannot be negative.");
    return std::make_unique<EllipseShape>(params[0], params[1], params[2], params[3]);
}

std::unique_ptr<Shape> TriangleFactory::createShape(const std::vector<int>& params) {
    if (params.size() != 6) throw std::runtime_error("Semantic Error: 'triangle' requires 6 params.");
    return std::make_unique<TriangleShape>(params[0], params[1], params[2], params[3], params[4], params[5]);
}

std::unique_ptr<Shape> PolygonFactory::createShape(const std::vector<int>& params) {
    if (params.size() < 6 || params.size() % 2 != 0) {
        throw std::runtime_error("Semantic Error: Polygon needs at least 3 points (6 numbers) and must be even.");
    }
    return std::make_unique<PolygonShape>(params);
}

#include "ShapeFactory.h"


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
    if (params.size() != 3) {
        throw std::runtime_error("Semantic Error: 'circle' requires 3 parameters (cx, cy, radius).");
    }
    return std::make_unique<CircleShape>(params[0], params[1], params[2]);
}

std::unique_ptr<Shape> RectangleFactory::createShape(const std::vector<int>& params) {
    if (params.size() != 4) {
        throw std::runtime_error("Semantic Error: 'rectangle' requires 4 parameters (x, y, width, height).");
    }
    return std::make_unique<RectangleShape>(params[0], params[1], params[2], params[3]);
}

std::unique_ptr<Shape> LineFactory::createShape(const std::vector<int>& params) {
    if (params.size() != 4) {
        throw std::runtime_error("Semantic Error: 'line' requires 4 parameters (x1, y1, x2, y2).");
    }
    return std::make_unique<LineShape>(params[0], params[1], params[2], params[3]);
}

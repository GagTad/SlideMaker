#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "Shape.h" 

class IShapeFactory {
public:
    virtual ~IShapeFactory() = default;
    virtual std::unique_ptr<Shape> createShape(const std::vector<int>& params) = 0;
};

class ShapeRegistry {
public:
    static ShapeRegistry& getInstance() {
        static ShapeRegistry instance;
        return instance;
    }
    void registerShape(const std::string& shapeType, std::unique_ptr<IShapeFactory> factory);
    std::unique_ptr<Shape> createShape(const std::string& shapeType, const std::vector<int>& params);

private:
    ShapeRegistry() = default;
    ~ShapeRegistry() = default;
    ShapeRegistry(const ShapeRegistry&) = delete;
    ShapeRegistry& operator=(const ShapeRegistry&) = delete;
    std::map<std::string, std::unique_ptr<IShapeFactory>> m_factories;
};

class CircleFactory : public IShapeFactory {
public:
    std::unique_ptr<Shape> createShape(const std::vector<int>& params) override;
};

class RectangleFactory : public IShapeFactory {
public:
    std::unique_ptr<Shape> createShape(const std::vector<int>& params) override;
};

class LineFactory : public IShapeFactory {
public:
    std::unique_ptr<Shape> createShape(const std::vector<int>& params) override;
};

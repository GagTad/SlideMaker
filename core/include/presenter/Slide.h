#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Shape.h"

class Slide {
public:
    Slide(const std::string& name) : m_name(name) {}

    void addShape(std::unique_ptr<Shape> shape) {
        m_shapes.push_back(std::move(shape));
    }
    void removeLastShape() {
        if (!m_shapes.empty()) {
            m_shapes.pop_back();
        }
    }

    const std::string& getName() const { return m_name; }
    const std::vector<std::unique_ptr<Shape>>& getShapes() const { return m_shapes; }
private:
    std::string m_name;
    std::vector<std::unique_ptr<Shape>> m_shapes;
};

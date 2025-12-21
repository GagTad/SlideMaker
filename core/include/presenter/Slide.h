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
    std::unique_ptr<Slide> clone() const {
        auto newSlide = std::make_unique<Slide>(m_name + " (Copy)");
        for (const auto& shape : m_shapes) {
            newSlide->addShape(shape->clone());
        }
        return newSlide;
    }

    void removeShapeAt(size_t index) {
        if (index < m_shapes.size()) {
            m_shapes.erase(m_shapes.begin() + index);
        }
    }

    void clearAllShapes() {
        m_shapes.clear();
    }

    size_t getShapeCount() const { return m_shapes.size(); }

    void bringShapeToFront(size_t index) {
        if (index >= m_shapes.size()) return;
        auto shape = std::move(m_shapes[index]);
        m_shapes.erase(m_shapes.begin() + index);
        m_shapes.push_back(std::move(shape));
    }

    void sendShapeToBack(size_t index) {
        if (index >= m_shapes.size()) return;
        
        auto shape = std::move(m_shapes[index]);
        m_shapes.erase(m_shapes.begin() + index);
        m_shapes.insert(m_shapes.begin(), std::move(shape));
    }

    std::unique_ptr<Shape> extractShapeAt(size_t index) {
        if (index >= m_shapes.size()) return nullptr;
        std::unique_ptr<Shape> shape = std::move(m_shapes[index]);
        m_shapes.erase(m_shapes.begin() + index);
        return shape;
    }

    void insertShapeAt(size_t index, std::unique_ptr<Shape> shape) {
        if (index > m_shapes.size()) index = m_shapes.size();
        m_shapes.insert(m_shapes.begin() + index, std::move(shape));
    }

    std::vector<std::unique_ptr<Shape>> extractAllShapes() {
        std::vector<std::unique_ptr<Shape>> temp = std::move(m_shapes);
        m_shapes.clear();
        return temp;
    }

    void setShapes(std::vector<std::unique_ptr<Shape>> shapes) {
        m_shapes = std::move(shapes);
    }

private:
    std::string m_name;
    std::vector<std::unique_ptr<Shape>> m_shapes;
};

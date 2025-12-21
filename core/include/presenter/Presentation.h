#pragma once
#include <vector>
#include <memory>
#include <stdexcept> 
#include "Slide.h"

class Presentation {
public:
    Presentation() : m_activeSlideId(-1) {}
    int createSlide(const std::string& name) {
        m_slides.push_back(std::make_unique<Slide>(name));
        return static_cast<int>(m_slides.size()) - 1; 
    }

    void duplicateSlide(int id) {
        if (id < 0 || static_cast<size_t>(id) >= m_slides.size()) {
            throw std::runtime_error("Invalid slide ID to duplicate.");
        }
        m_slides.push_back(m_slides[id]->clone());
    }

    void removeLastSlide() {
        if (!m_slides.empty()) {
            m_slides.pop_back();
            if (m_activeSlideId >= static_cast<int>(m_slides.size())) {
                m_activeSlideId = m_slides.empty() ? -1 : static_cast<int>(m_slides.size()) - 1;
            }
        }
    }

    void setActiveSlideId(int id) {
        if (id < -1 || (id >= 0 && static_cast<size_t>(id) >= m_slides.size())) {
            throw std::runtime_error("Invariant Violation: Invalid Slide ID " + std::to_string(id));
        }
        m_activeSlideId = id;
    }

//shape managment
    void addShapeToActiveSlide(std::unique_ptr<Shape> shape) {
        Slide* slide = getMutableActiveSlide();
        if (!slide) throw std::runtime_error("No active slide selected.");
        slide->addShape(std::move(shape));
    }

    void removeShapeFromActiveSlide(int index) {
        Slide* slide = getMutableActiveSlide();
        if (!slide) throw std::runtime_error("No active slide.");
        if (index < 0 || static_cast<size_t>(index) >= slide->getShapes().size()) {
            throw std::runtime_error("Shape index out of range.");
        }
        slide->removeShapeAt(index);
    }

    void clearActiveSlide() {
        Slide* slide = getMutableActiveSlide();
        if (!slide) throw std::runtime_error("No active slide.");
        slide->clearAllShapes();
    }

    void bringShapeToFront(int index) {
        Slide* slide = getMutableActiveSlide();
        if (!slide) throw std::runtime_error("No active slide.");
        slide->bringShapeToFront(index);
    }

    void sendShapeToBack(int index) {
        Slide* slide = getMutableActiveSlide();
        if (!slide) throw std::runtime_error("No active slide.");
        slide->sendShapeToBack(index);
    }

    // Getters
    int getActiveSlideId() const { return m_activeSlideId; }

    const Slide* getActiveSlide() const {
        if (m_activeSlideId >= 0 && static_cast<size_t>(m_activeSlideId) < m_slides.size()) {
            return m_slides[m_activeSlideId].get();
        }
        return nullptr;
    }

    const std::vector<std::unique_ptr<Slide>>& getSlides() const { return m_slides; }

    // Undo Helper Methods (Extract/Restore)
    std::unique_ptr<Shape> extractShapeFromActiveSlide(int index) {
        Slide* slide = getMutableActiveSlide();
        if (!slide) throw std::runtime_error("No active slide.");
        return slide->extractShapeAt(index);
    }

    void insertShapeToActiveSlide(int index, std::unique_ptr<Shape> shape) {
        Slide* slide = getMutableActiveSlide();
        if (slide) slide->insertShapeAt(index, std::move(shape));
    }

    std::vector<std::unique_ptr<Shape>> extractAllShapesFromActiveSlide() {
        Slide* slide = getMutableActiveSlide();
        if (!slide) return {};
        return slide->extractAllShapes();
    }

    void restoreShapesToActiveSlide(std::vector<std::unique_ptr<Shape>> shapes) {
        Slide* slide = getMutableActiveSlide();
        if (slide) slide->setShapes(std::move(shapes));
    }

    void moveSlide(int fromIndex, int toIndex) {
        if (fromIndex < 0 || fromIndex >= static_cast<int>(m_slides.size()) ||
            toIndex < 0 || toIndex >= static_cast<int>(m_slides.size())) {
            throw std::runtime_error("Invalid slide index for move.");
        }

        if (fromIndex == toIndex) return;
        auto slide = std::move(m_slides[fromIndex]);
        m_slides.erase(m_slides.begin() + fromIndex);
        m_slides.insert(m_slides.begin() + toIndex, std::move(slide));
        if (m_activeSlideId == fromIndex) {
            m_activeSlideId = toIndex;
        }
        else if (m_activeSlideId > fromIndex && m_activeSlideId <= toIndex) {
            m_activeSlideId--;
        }
        else if (m_activeSlideId < fromIndex && m_activeSlideId >= toIndex) {
            m_activeSlideId++;
        }
    }

    //  Move Helpers
    std::pair<int, int> getShapePosition(int shapeIndex) {
        Slide* slide = getMutableActiveSlide();
        if (!slide) throw std::runtime_error("No active slide.");

        const auto& shapes = slide->getShapes();
        if (shapeIndex < 0 || static_cast<size_t>(shapeIndex) >= shapes.size()) {
            // FIX: Throw exception instead of returning dummy value
            throw std::runtime_error("Invalid shape index for position lookup.");
        }
        return shapes[shapeIndex]->getPosition();
    }

    void moveShape(int shapeIndex, int x, int y) {
        Slide* slide = getMutableActiveSlide();
        if (!slide) throw std::runtime_error("No active slide.");

        const auto& shapes = slide->getShapes();
        if (shapeIndex < 0 || static_cast<size_t>(shapeIndex) >= shapes.size()) {
            throw std::runtime_error("Invalid shape index.");
        }
        const_cast<Shape*>(shapes[shapeIndex].get())->setPosition(x, y);
    }

    void scaleShape(int index, double factor) {
        Slide* slide = getMutableActiveSlide();
        if (!slide) throw std::runtime_error("No active slide.");
        if (index < 0 || static_cast<size_t>(index) >= slide->getShapes().size()) throw std::runtime_error("Invalid index.");

        const_cast<Shape*>(slide->getShapes()[index].get())->scale(factor);
    }

    void recolorShape(int index, const std::string& color) {
        Slide* slide = getMutableActiveSlide();
        if (!slide) throw std::runtime_error("No active slide.");
        if (index < 0 || static_cast<size_t>(index) >= slide->getShapes().size()) throw std::runtime_error("Invalid index.");
        const_cast<Shape*>(slide->getShapes()[index].get())->flags["--color"] = color;
    }

    std::string getShapeColor(int index) {
        Slide* slide = getMutableActiveSlide();
        if (!slide) return "black";
        auto& flags = slide->getShapes()[index]->flags;
        return flags.count("--color") ? flags["--color"] : "black";
    }


private:
    Slide* getMutableActiveSlide() {
        if (m_activeSlideId >= 0 && static_cast<size_t>(m_activeSlideId) < m_slides.size()) {
            return m_slides[m_activeSlideId].get();
        }
        return nullptr;
    }
private:
    std::vector<std::unique_ptr<Slide>> m_slides;
    int m_activeSlideId;
};


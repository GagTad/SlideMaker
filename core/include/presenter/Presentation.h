#pragma once
#include <vector>
#include <memory>
#include <iostream> 
#include <stdexcept>
#include "Slide.h"

class Presentation {
public:
    Presentation() : m_activeSlideId(-1) {}

    void createSlide(const std::string& name) {
        m_slides.push_back(std::make_unique<Slide>(name));
        std::cout << "Created slide ID: " << m_slides.size() - 1 << ", Name: " << name << std::endl;
        m_activeSlideId = m_slides.size() - 1;
    }

    void removeLastSlide() {
        if (!m_slides.empty()) {
            std::cout << "Removing slide: " << m_slides.back()->getName() << std::endl;
            m_slides.pop_back();
            // Reset active ID if needed
            if (m_activeSlideId >= static_cast<int>(m_slides.size())) {
                m_activeSlideId = m_slides.empty() ? -1 : m_slides.size() - 1;
            }
        }
    }

    void listSlides() const {
        std::cout << "--- Slides ---" << std::endl;
        for (size_t i = 0; i < m_slides.size(); ++i) {
            std::cout << "ID: " << i << ", Name: \"" << m_slides[i]->getName() << "\""
                << (static_cast<int>(i) == m_activeSlideId ? " [ACTIVE]" : "") << std::endl;
        }
        std::cout << "--------------" << std::endl;
    }

    void setActiveSlideId(int id) {
        if (id < -1 || (id >= 0 && static_cast<size_t>(id) >= m_slides.size())) {
            //throw std::runtime_error("Slide ID out of range.");
        }
        m_activeSlideId = id;
        std::cout << "Active slide set to: " << id << std::endl;
    }

    int getActiveSlideId() const { return m_activeSlideId; }

    void addShapeToActiveSlide(std::unique_ptr<Shape> shape) {
        Slide* slide = getMutableActiveSlide();
        if (!slide) throw std::runtime_error("No active slide selected.");
        slide->addShape(std::move(shape));
    }

    void removeLastShapeFromActiveSlide() {
        Slide* slide = getMutableActiveSlide();
        if (slide) {
            slide->removeLastShape();
            std::cout << "Removed last shape from slide " << m_activeSlideId << std::endl;
        }
    }

    const Slide* getActiveSlide() const {
        if (m_activeSlideId >= 0 && static_cast<size_t>(m_activeSlideId) < m_slides.size()) {
            return m_slides[m_activeSlideId].get();
        }
        return nullptr;
    }

    const std::vector<std::unique_ptr<Slide>>& getSlides() const { return m_slides; }

private:
    Slide* getMutableActiveSlide() {
        if (m_activeSlideId >= 0 && static_cast<size_t>(m_activeSlideId) < m_slides.size()) {
            return m_slides[m_activeSlideId].get();
        }
        return nullptr;
    }

    std::vector<std::unique_ptr<Slide>> m_slides;
    int m_activeSlideId;
};

#pragma once
#include <vector>
#include <memory>
#include <iostream> 
#include "Slide.h"

class Presentation {
public:
    Presentation() : m_activeSlideId(-1) {}

    void createSlide(const std::string& name) {
        m_slides.push_back(std::make_unique<Slide>(name));
        std::cout << "Created slide with ID: " << m_slides.size() - 1 << std::endl;
    }

    void listSlides() const {
        std::cout << "--- Slides ---" << std::endl;
        for (size_t i = 0; i < m_slides.size(); ++i) {
            std::cout << "ID: " << i << ", Name: \"" << m_slides[i]->getName() << "\"" << std::endl;
        }
        std::cout << "--------------" << std::endl;
    }

    size_t getSlideCount() const { return m_slides.size(); }
    int getActiveSlideId() const { return m_activeSlideId; }

    void setActiveSlideId(int id) { m_activeSlideId = id; }

    Slide* getActiveSlide() {
        if (m_activeSlideId >= 0 && m_activeSlideId < m_slides.size()) {
            return m_slides[m_activeSlideId].get();
        }
        return nullptr;
    }

private:
    std::vector<std::unique_ptr<Slide>> m_slides;
    int m_activeSlideId;
};

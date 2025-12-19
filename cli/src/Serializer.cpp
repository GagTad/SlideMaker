#include "Serializer.h"
#include <fstream>
#include <iostream>

void Serializer::savePresentation(const Presentation& presentation, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " + filename);
    }

    const auto& slides = presentation.getSlides();
    for (size_t i = 0; i < slides.size(); ++i) {
        file << "create_slide \"" << slides[i]->getName() << "\"\n";
        file << "select_slide " << i << "\n";
        for (const auto& shape : slides[i]->getShapes()) {
            file << shape->serialize() << "\n";
        }
        file << "\n";
    }
    file.close();
}

void Serializer::exportSlideToSvg(const Slide* slide, const std::string& filename) {
    if (!slide) throw std::runtime_error("No slide to export.");

    std::ofstream svgFile(filename);
    if (!svgFile.is_open()) throw std::runtime_error("Could not open SVG file: " + filename);

    svgFile << "<svg width=\"800\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    for (const auto& shape : slide->getShapes()) {
        svgFile << "  " << shape->toSvg() << "\n";
    }
    svgFile << "</svg>\n";
    svgFile.close();
}


void Serializer::exportToHtml(const Presentation& presentation, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) throw std::runtime_error("Cannot open HTML file for writing: " + filename);

    // HTML Header & CSS
    file << "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Presentation</title><style>";
    file << "body { font-family: sans-serif; text-align: center; background-color: #f0f0f0; }";
    file << ".slide-container { position: relative; width: 800px; height: 600px; margin: 20px auto; background: white; border: 2px solid #333; box-shadow: 0 0 10px rgba(0,0,0,0.5); }";
    file << ".slide { display: none; width: 100%; height: 100%; }";
    file << ".active { display: block; }";
    file << ".controls { margin-top: 20px; }";
    file << "button { padding: 10px 20px; font-size: 16px; cursor: pointer; background: #007bff; color: white; border: none; border-radius: 5px; margin: 0 10px; }";
    file << "button:hover { background: #0056b3; }";
    file << "button:disabled { background: #ccc; cursor: not-allowed; }";
    file << "</style></head><body>";

    file << "<h1>Slideshow</h1>";

    // Slides Container
    file << "<div class='slide-container'>";

    const auto& slides = presentation.getSlides();
    if (slides.empty()) {
        file << "<h3>No slides available</h3>";
    }
    else {
        for (size_t i = 0; i < slides.size(); ++i) {
            file << "<div class='slide" << (i == 0 ? " active" : "") << "' id='slide_" << i << "'>";
            // SVG Content
            file << "<svg width='800' height='600' xmlns='http://www.w3.org/2000/svg'>";
            for (const auto& shape : slides[i]->getShapes()) {
                file << shape->toSvg();
            }
            file << "</svg>";
            // Slide Title Overlay
            file << "<div style='position:absolute; bottom:10px; left:10px; background:rgba(255,255,255,0.7); padding:5px;'>"
                << slides[i]->getName() << " (" << i + 1 << "/" << slides.size() << ")</div>";
            file << "</div>";
        }
    }
    file << "</div>";

    // Controls
    file << "<div class='controls'>";
    file << "<button onclick='prev()'>&#8592; Previous</button>";
    file << "<button onclick='next()'>Next &#8594;</button>";
    file << "</div>";

    // JavaScript Logic
    file << "<script>";
    file << "let current = 0; const total = " << slides.size() << ";";
    file << "function show(idx) {";
    file << "  if(idx < 0 || idx >= total) return;";
    file << "  document.querySelectorAll('.slide').forEach(s => s.classList.remove('active'));";
    file << "  document.getElementById('slide_' + idx).classList.add('active');";
    file << "  current = idx;";
    file << "}";
    file << "function next() { show(current + 1); }";
    file << "function prev() { show(current - 1); }";
    file << "document.addEventListener('keydown', function(event) {";
    file << "  if (event.key === 'ArrowRight') next();";
    file << "  if (event.key === 'ArrowLeft') prev();";
    file << "});";
    file << "</script>";

    file << "</body></html>";
    file.close();

    std::cout << "Slideshow exported to '" << filename << "'. Open this file in your browser." << std::endl;
}
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

    file << "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Presentation</title><style>";
    file << "body { font-family: 'Segoe UI', Arial, sans-serif; background-color: #e0e0e0; margin: 0; padding: 0; display: flex; flex-direction: column; align-items: center; height: 100vh; }";
    file << "header { margin-top: 20px; margin-bottom: 10px; text-align: center; }";
    file << "h1 { margin: 0; color: #333; }";
    file << "h2 { margin: 5px 0 0 0; color: #666; font-weight: normal; font-size: 1.2rem; }";
    file << ".slide-container { position: relative; width: 800px; height: 600px; background: white; box-shadow: 0 10px 25px rgba(0,0,0,0.2); border: 1px solid #ccc; }";
    file << ".slide { display: none; width: 100%; height: 100%; }";
    file << ".active { display: block; }";
    file << "svg { width: 100%; height: 100%; display: block; }";
    file << ".controls { margin-top: 20px; background: white; padding: 10px 20px; border-radius: 30px; box-shadow: 0 4px 10px rgba(0,0,0,0.1); display: flex; align-items: center; gap: 15px; }";
    file << "button { padding: 8px 16px; border: none; background: #0078d4; color: white; border-radius: 20px; cursor: pointer; font-size: 14px; transition: 0.2s; }";
    file << "button:hover { background: #005a9e; }";
    file << "button.fs-btn { background: #107c10; }"; 
    file << "button.fs-btn:hover { background: #0b5a0b; }";
    file << ".counter { font-weight: bold; color: #555; min-width: 60px; text-align: center; }";

    file << ":fullscreen { background: black; }";
    file << ":fullscreen body { background: black; justify-content: center; }";
    file << ":fullscreen header, :fullscreen .controls { display: none; }";
    file << ":fullscreen .slide-container { width: 100vw; height: 100vh; border: none; box-shadow: none; background: black; display: flex; align-items: center; justify-content: center; }";
    file << ":fullscreen svg { width: 100%; height: 100%; max-width: 100%; max-height: 100%; }";

    file << "</style></head><body>";

    const auto& slides = presentation.getSlides();

    file << "<header>";
    file << "<h1>SimpleSlide Presentation</h1>";
    file << "<h2 id='slide-title'>...</h2>";
    file << "</header>";
    file << "<div class='slide-container' id='main-container'>";

    if (slides.empty()) {
        file << "<div style='display:flex;justify-content:center;align-items:center;height:100%;'>No slides</div>";
    }
    else {
        for (size_t i = 0; i < slides.size(); ++i) {
            file << "<div class='slide" << (i == 0 ? " active" : "") << "' id='slide_" << i << "' data-name=\"" << slides[i]->getName() << "\">";
            file << "<svg viewBox='0 0 800 600' preserveAspectRatio='xMidYMid meet' xmlns='http://www.w3.org/2000/svg'>";
            file << "<rect width='800' height='600' fill='white' />";

            for (const auto& shape : slides[i]->getShapes()) {
                file << shape->toSvg();
            }
            file << "</svg>";
            file << "</div>";
        }
    }
    file << "</div>";

    file << "<div class='controls'>";
    file << "<button onclick='prev()'>Previous</button>";
    file << "<span class='counter' id='counter'>1 / " << slides.size() << "</span>";
    file << "<button onclick='next()'>Next</button>";
    file << "<button class='fs-btn' onclick='toggleFullScreen()'><b>&#x26F6; Start Presenting</b></button>";
    file << "</div>";

    file << "<script>";
    file << "let current = 0; const total = " << slides.size() << ";";

    file << "function updateUI() {";
    file << "  document.querySelectorAll('.slide').forEach(s => s.classList.remove('active'));";
    file << "  const activeSlide = document.getElementById('slide_' + current);";
    file << "  if(activeSlide) {";
    file << "    activeSlide.classList.add('active');";
    file << "    document.getElementById('slide-title').innerText = activeSlide.getAttribute('data-name');";
    file << "    document.getElementById('counter').innerText = (current + 1) + ' / ' + total;";
    file << "  }";
    file << "}";

    file << "function next() { if(current < total - 1) { current++; updateUI(); } }";
    file << "function prev() { if(current > 0) { current--; updateUI(); } }";

    file << "function toggleFullScreen() {";
    file << "  const elem = document.documentElement;"; // Make whole page fullscreen
    file << "  if (!document.fullscreenElement) { elem.requestFullscreen(); } else { document.exitFullscreen(); }";
    file << "}";

    file << "document.getElementById('main-container').addEventListener('click', function() {";
    file << "   if(document.fullscreenElement) next();"; // Only advance on click if in fullscreen
    file << "});";

    file << "document.addEventListener('keydown', function(e) {";
    file << "  if(e.key === 'ArrowRight' || e.key === ' ' || e.key === 'Enter') next();";
    file << "  if(e.key === 'ArrowLeft') prev();";
    file << "  if(e.key === 'f') toggleFullScreen();";
    file << "});";

    file << "updateUI();";
    file << "</script>";

    file << "</body></html>";
    file.close();

    std::cout << "Exported '" << filename << "' with True Fullscreen scaling." << std::endl;
}

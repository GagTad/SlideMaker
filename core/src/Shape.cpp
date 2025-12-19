#include "Shape.h"

std::string Shape::flagsToString() const {
    std::stringstream ss;
    for (const auto& pair : flags) {
        ss << " " << pair.first << " \"" << pair.second << "\"";
    }
    return ss.str();
}

std::string Shape::getSvgStyle() const {
    std::string stroke = flags.count("--color") ? flags.at("--color") : "black";
    std::string fill = flags.count("--fill") ? flags.at("--fill") : "transparent";
    std::string strokeWidth = flags.count("--width") ? flags.at("--width") : "2";

    std::stringstream ss;
    ss << " stroke=\"" << stroke << "\" fill=\"" << fill << "\" stroke-width=\"" << strokeWidth << "\" ";
    return ss.str();
}

// Circle
CircleShape::CircleShape(int cx, int cy, int r) : centerX(cx), centerY(cy), radius(r) {}

std::string CircleShape::toSvg() const {
    std::stringstream ss;
    ss << "<circle cx=\"" << centerX << "\" cy=\"" << centerY << "\" r=\"" << radius << "\""
        << getSvgStyle() << " />";
    return ss.str();
}

std::string CircleShape::serialize() const {
    return "add circle " + std::to_string(centerX) + " " + std::to_string(centerY) + " " + std::to_string(radius) + flagsToString();
}

// Rectangle
RectangleShape::RectangleShape(int x_coord, int y_coord, int w, int h)
    : x(x_coord), y(y_coord), width(w), height(h) {
}

std::string RectangleShape::toSvg() const {
    std::stringstream ss;
    ss << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height << "\""
        << getSvgStyle() << " />";
    return ss.str();
}

std::string RectangleShape::serialize() const {
    return "add rectangle " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(width) + " " + std::to_string(height) + flagsToString();
}

// Line
LineShape::LineShape(int start_x, int start_y, int end_x, int end_y)
    : x1(start_x), y1(start_y), x2(end_x), y2(end_y) {
}

std::string LineShape::toSvg() const {
    std::stringstream ss;
    // Line doesn't use fill usually
    std::string stroke = flags.count("--color") ? flags.at("--color") : "black";
    std::string strokeWidth = flags.count("--width") ? flags.at("--width") : "2";

    ss << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\""
        << " stroke=\"" << stroke << "\" stroke-width=\"" << strokeWidth << "\" />";
    return ss.str();
}

std::string LineShape::serialize() const {
    return "add line " + std::to_string(x1) + " " + std::to_string(y1) + " " + std::to_string(x2) + " " + std::to_string(y2) + flagsToString();
}

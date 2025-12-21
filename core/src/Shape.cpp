#include "Shape.h"
#include <stdexcept> 

// Shape Helpers 
std::string Shape::flagsToString() const {
    std::stringstream ss;
    for (const auto& pair : flags) ss << " " << pair.first << " \"" << pair.second << "\"";
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
    ss << "<circle cx=\"" << centerX << "\" cy=\"" << centerY << "\" r=\"" << radius << "\"" << getSvgStyle() << " />";
    return ss.str();
}
std::string CircleShape::serialize() const {
    return "add circle " + std::to_string(centerX) + " " + std::to_string(centerY) + " " + std::to_string(radius) + flagsToString();
}
std::unique_ptr<Shape> CircleShape::clone() const {
    auto s = std::make_unique<CircleShape>(centerX, centerY, radius); s->flags = flags; return s;
}
void CircleShape::setPosition(int x, int y) { centerX = x; centerY = y; }
std::pair<int, int> CircleShape::getPosition() const { return { centerX, centerY }; }
void CircleShape::scale(double factor) {
    if (factor < 0) throw std::runtime_error("Scale factor cannot be negative.");
    radius = static_cast<int>(radius * factor);
}

// Rectangle
RectangleShape::RectangleShape(int x_coord, int y_coord, int w, int h) : x(x_coord), y(y_coord), width(w), height(h) {}
std::string RectangleShape::toSvg() const {
    std::stringstream ss;
    ss << "<rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height << "\"" << getSvgStyle() << " />";
    return ss.str();
}
std::string RectangleShape::serialize() const {
    return "add rectangle " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(width) + " " + std::to_string(height) + flagsToString();
}
std::unique_ptr<Shape> RectangleShape::clone() const {
    auto s = std::make_unique<RectangleShape>(x, y, width, height); s->flags = flags; return s;
}
void RectangleShape::setPosition(int newX, int newY) { x = newX; y = newY; }
std::pair<int, int> RectangleShape::getPosition() const { return { x, y }; }
void RectangleShape::scale(double factor) {
    if (factor < 0) throw std::runtime_error("Scale factor cannot be negative.");
    width = static_cast<int>(width * factor);
    height = static_cast<int>(height * factor);
}

// Line 
LineShape::LineShape(int start_x, int start_y, int end_x, int end_y) : x1(start_x), y1(start_y), x2(end_x), y2(end_y) {}
std::string LineShape::toSvg() const {
    std::stringstream ss;
    std::string stroke = flags.count("--color") ? flags.at("--color") : "black";
    std::string strokeWidth = flags.count("--width") ? flags.at("--width") : "2";
    ss << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" stroke=\"" << stroke << "\" stroke-width=\"" << strokeWidth << "\" />";
    return ss.str();
}
std::string LineShape::serialize() const {
    return "add line " + std::to_string(x1) + " " + std::to_string(y1) + " " + std::to_string(x2) + " " + std::to_string(y2) + flagsToString();
}
std::unique_ptr<Shape> LineShape::clone() const {
    auto s = std::make_unique<LineShape>(x1, y1, x2, y2); s->flags = flags; return s;
}
void LineShape::setPosition(int newX, int newY) {
    int dx = newX - x1; int dy = newY - y1;
    x1 = newX; y1 = newY; x2 += dx; y2 += dy;
}
std::pair<int, int> LineShape::getPosition() const { return { x1, y1 }; }
void LineShape::scale(double factor) {
    int dx = x2 - x1; int dy = y2 - y1;
    x2 = x1 + static_cast<int>(dx * factor);
    y2 = y1 + static_cast<int>(dy * factor);
}

//Text
TextShape::TextShape(int x_coord, int y_coord, int fs) : x(x_coord), y(y_coord), fontSize(fs) {}
std::string TextShape::toSvg() const {
    std::string content = flags.count("--content") ? flags.at("--content") : "Text";
    std::string fillColor = flags.count("--fill") ? flags.at("--fill") : "black";
    std::stringstream ss;
    ss << "<text x=\"" << x << "\" y=\"" << y << "\" font-size=\"" << fontSize << "\" fill=\"" << fillColor << "\" font-family=\"Arial, sans-serif\">" << content << "</text>";
    return ss.str();
}
std::string TextShape::serialize() const {
    return "add text " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(fontSize) + flagsToString();
}
std::unique_ptr<Shape> TextShape::clone() const {
    auto s = std::make_unique<TextShape>(x, y, fontSize); s->flags = flags; return s;
}
void TextShape::setPosition(int newX, int newY) { x = newX; y = newY; }
std::pair<int, int> TextShape::getPosition() const { return { x, y }; }
void TextShape::scale(double factor) {
    if (factor <= 0) throw std::runtime_error("Text scale factor must be positive.");
    fontSize = static_cast<int>(fontSize * factor);
}

// Image
ImageShape::ImageShape(int x_coord, int y_coord, int w, int h) : x(x_coord), y(y_coord), width(w), height(h) {}
std::string ImageShape::toSvg() const {
    std::string path = flags.count("--path") ? flags.at("--path") : "image.png";
    std::stringstream ss;
    ss << "<image href=\"" << path << "\" x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height << "\" preserveAspectRatio=\"none\" />";
    return ss.str();
}
std::string ImageShape::serialize() const {
    return "add image " + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(width) + " " + std::to_string(height) + flagsToString();
}
std::unique_ptr<Shape> ImageShape::clone() const {
    auto s = std::make_unique<ImageShape>(x, y, width, height); s->flags = flags; return s;
}
void ImageShape::setPosition(int newX, int newY) { x = newX; y = newY; }
std::pair<int, int> ImageShape::getPosition() const { return { x, y }; }
void ImageShape::scale(double factor) {
    if (factor < 0) throw std::runtime_error("Scale factor cannot be negative.");
    width = static_cast<int>(width * factor);
    height = static_cast<int>(height * factor);
}

//Ellipse
EllipseShape::EllipseShape(int _cx, int _cy, int _rx, int _ry) : cx(_cx), cy(_cy), rx(_rx), ry(_ry) {}
std::string EllipseShape::toSvg() const {
    std::stringstream ss;
    ss << "<ellipse cx=\"" << cx << "\" cy=\"" << cy << "\" rx=\"" << rx << "\" ry=\"" << ry << "\"" << getSvgStyle() << " />";
    return ss.str();
}
std::string EllipseShape::serialize() const {
    return "add ellipse " + std::to_string(cx) + " " + std::to_string(cy) + " " + std::to_string(rx) + " " + std::to_string(ry) + flagsToString();
}
std::unique_ptr<Shape> EllipseShape::clone() const {
    auto s = std::make_unique<EllipseShape>(cx, cy, rx, ry); s->flags = flags; return s;
}
void EllipseShape::setPosition(int newX, int newY) { cx = newX; cy = newY; }
std::pair<int, int> EllipseShape::getPosition() const { return { cx, cy }; }
void EllipseShape::scale(double factor) {
    if (factor < 0) throw std::runtime_error("Scale factor cannot be negative.");
    rx = static_cast<int>(rx * factor);
    ry = static_cast<int>(ry * factor);
}

//Triangle
TriangleShape::TriangleShape(int _x1, int _y1, int _x2, int _y2, int _x3, int _y3) : x1(_x1), y1(_y1), x2(_x2), y2(_y2), x3(_x3), y3(_y3) {}
std::string TriangleShape::toSvg() const {
    std::stringstream ss;
    ss << "<polygon points=\"" << x1 << "," << y1 << " " << x2 << "," << y2 << " " << x3 << "," << y3 << "\"" << getSvgStyle() << " />";
    return ss.str();
}
std::string TriangleShape::serialize() const {
    return "add triangle " + std::to_string(x1) + " " + std::to_string(y1) + " " + std::to_string(x2) + " " + std::to_string(y2) + " " + std::to_string(x3) + " " + std::to_string(y3) + flagsToString();
}
std::unique_ptr<Shape> TriangleShape::clone() const {
    auto s = std::make_unique<TriangleShape>(x1, y1, x2, y2, x3, y3); s->flags = flags; return s;
}
void TriangleShape::setPosition(int newX, int newY) {
    int dx = newX - x1; int dy = newY - y1;
    x1 += dx; y1 += dy; x2 += dx; y2 += dy; x3 += dx; y3 += dy;
}
std::pair<int, int> TriangleShape::getPosition() const { return { x1, y1 }; }
void TriangleShape::scale(double factor) {
    x2 = x1 + static_cast<int>((x2 - x1) * factor);
    y2 = y1 + static_cast<int>((y2 - y1) * factor);
    x3 = x1 + static_cast<int>((x3 - x1) * factor);
    y3 = y1 + static_cast<int>((y3 - y1) * factor);
}

//Polygon
PolygonShape::PolygonShape(const std::vector<int>& pts) : points(pts) {}
std::string PolygonShape::toSvg() const {
    std::stringstream ss;
    ss << "<polygon points=\"";
    for (size_t i = 0; i < points.size(); ++i) ss << points[i] << (i % 2 == 0 ? "," : " ");
    ss << "\"" << getSvgStyle() << " />";
    return ss.str();
}
std::string PolygonShape::serialize() const {
    std::string s = "add polygon";
    for (int p : points) s += " " + std::to_string(p);
    return s + flagsToString();
}
std::unique_ptr<Shape> PolygonShape::clone() const {
    auto s = std::make_unique<PolygonShape>(points); s->flags = flags; return s;
}
void PolygonShape::setPosition(int newX, int newY) {
    if (points.empty()) return;
    int dx = newX - points[0]; int dy = newY - points[1];
    for (size_t i = 0; i < points.size(); i += 2) { points[i] += dx; points[i + 1] += dy; }
}
std::pair<int, int> PolygonShape::getPosition() const { if (points.empty()) return { 0,0 }; return { points[0], points[1] }; }
void PolygonShape::scale(double factor) {
    if (points.empty()) return;
    int ox = points[0], oy = points[1];
    for (size_t i = 2; i < points.size(); i += 2) {
        points[i] = ox + static_cast<int>((points[i] - ox) * factor);
        points[i + 1] = oy + static_cast<int>((points[i + 1] - oy) * factor);
    }
}

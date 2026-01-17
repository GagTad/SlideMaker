#include "SvgVisitor.h"
#include "Shape.h"
#include <sstream>

std::string SvgVisitor::getSvgString() const {
    return m_ss.str();
}

void SvgVisitor::reset() {
    m_ss.str("");
    m_ss.clear();
}


std::string SvgVisitor::getCommonStyle(const Shape& shape, bool isLine) {
    std::stringstream ss;
    ss << " style=\"";

    if (isLine) {
        ss << "fill:none;";
    }
    else {
        std::string fill = shape.getProperty("--fill");
        if (fill.empty()) fill = "black"; 
        ss << "fill:" << fill << ";";
    }

    std::string stroke = shape.getProperty("--color");
    if (stroke.empty()) {
        if (isLine) stroke = "black";
    }

    if (!stroke.empty()) {
        ss << "stroke:" << stroke << ";";
    }


    std::string width = shape.getProperty("--width");
    if (!width.empty()) {
        ss << "stroke-width:" << width << ";";
    }
    else if (isLine || !stroke.empty()) {
        ss << "stroke-width:1;";
    }

    ss << "\"";
    return ss.str();
}

void SvgVisitor::visit(const CircleShape& shape) {
    m_ss << "<circle cx=\"" << shape.getCx()
        << "\" cy=\"" << shape.getCy()
        << "\" r=\"" << shape.getRadius() << "\""
        << getCommonStyle(shape) << " />\n";
}

void SvgVisitor::visit(const RectangleShape& shape) {
    m_ss << "<rect x=\"" << shape.getX()
        << "\" y=\"" << shape.getY()
        << "\" width=\"" << shape.getWidth()
        << "\" height=\"" << shape.getHeight() << "\""
        << getCommonStyle(shape) << " />\n";
}

void SvgVisitor::visit(const LineShape& shape) {
    m_ss << "<line x1=\"" << shape.getX1()
        << "\" y1=\"" << shape.getY1()
        << "\" x2=\"" << shape.getX2()
        << "\" y2=\"" << shape.getY2() << "\""
        << getCommonStyle(shape, true) << " />\n";
}

void SvgVisitor::visit(const TextShape& shape) {
    std::string content = shape.getProperty("--content", "Text");
    m_ss << "<text x=\"" << shape.getX()
        << "\" y=\"" << shape.getY()
        << "\" font-size=\"" << shape.getFontSize() << "\""
        << getCommonStyle(shape) << ">"
        << content << "</text>\n";
}

void SvgVisitor::visit(const ImageShape& shape) {
    std::string path = shape.getProperty("--path", "");

    m_ss << "<image x=\"" << shape.getX()
        << "\" y=\"" << shape.getY()
        << "\" width=\"" << shape.getWidth()
        << "\" height=\"" << shape.getHeight() << "\" href=\"" << path << "\" />\n";
}

void SvgVisitor::visit(const EllipseShape& shape) {
    m_ss << "<ellipse cx=\"" << shape.getCx()
        << "\" cy=\"" << shape.getCy()
        << "\" rx=\"" << shape.getRx()
        << "\" ry=\"" << shape.getRy() << "\""
        << getCommonStyle(shape) << " />\n";
}

void SvgVisitor::visit(const TriangleShape& shape) {
    m_ss << "<polygon points=\""
        << shape.getX1() << "," << shape.getY1() << " "
        << shape.getX2() << "," << shape.getY2() << " "
        << shape.getX3() << "," << shape.getY3() << "\""
        << getCommonStyle(shape) << " />\n";
}

void SvgVisitor::visit(const PolygonShape& shape) {
    m_ss << "<polygon points=\"";
    const auto& pts = shape.getPoints();
    for (size_t i = 0; i < pts.size(); i += 2) {
        if (i + 1 < pts.size()) {
            m_ss << pts[i] << "," << pts[i + 1] << " ";
        }
    }
    m_ss << "\"" << getCommonStyle(shape) << " />\n";
}
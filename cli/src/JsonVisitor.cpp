#include "JsonVisitor.h"
#include "Shape.h"

std::string JsonVisitor::getJsonString() const {
    return m_ss.str();
}

void JsonVisitor::reset() {
    m_ss.str("");
    m_ss.clear();
}

std::string JsonVisitor::formatProps(const Shape& shape) {
    std::stringstream ss;
    const auto& props = shape.getProperties();
    if (!props.empty()) {
        ss << ", \"properties\": {";
        bool first = true;
        for (const auto& [key, val] : props) {
            if (!first) ss << ", ";
            ss << "\"" << key << "\": \"" << val << "\"";
            first = false;
        }
        ss << "}";
    }
    return ss.str();
}

void JsonVisitor::visit(const CircleShape& shape) {
    m_ss << "{ \"type\": \"circle\", \"cx\": " << shape.getCx()
        << ", \"cy\": " << shape.getCy()
        << ", \"r\": " << shape.getRadius()
        << formatProps(shape) << " }";
}

void JsonVisitor::visit(const RectangleShape& shape) {
    m_ss << "{ \"type\": \"rectangle\", \"x\": " << shape.getX()
        << ", \"y\": " << shape.getY()
        << ", \"w\": " << shape.getWidth()
        << ", \"h\": " << shape.getHeight()
        << formatProps(shape) << " }";
}

void JsonVisitor::visit(const LineShape& shape) {
    m_ss << "{ \"type\": \"line\", \"x1\": " << shape.getX1()
        << ", \"y1\": " << shape.getY1()
        << ", \"x2\": " << shape.getX2()
        << ", \"y2\": " << shape.getY2()
        << formatProps(shape) << " }";
}

void JsonVisitor::visit(const TextShape& shape) {
    m_ss << "{ \"type\": \"text\", \"x\": " << shape.getX()
        << ", \"y\": " << shape.getY()
        << ", \"fontSize\": " << shape.getFontSize()
        << formatProps(shape) << " }";
}

void JsonVisitor::visit(const ImageShape& shape) {
    m_ss << "{ \"type\": \"image\", \"x\": " << shape.getX()
        << ", \"y\": " << shape.getY()
        << ", \"w\": " << shape.getWidth()
        << ", \"h\": " << shape.getHeight()
        << formatProps(shape) << " }";
}

void JsonVisitor::visit(const EllipseShape& shape) {
    m_ss << "{ \"type\": \"ellipse\", \"cx\": " << shape.getCx()
        << ", \"cy\": " << shape.getCy()
        << ", \"rx\": " << shape.getRx()
        << ", \"ry\": " << shape.getRy()
        << formatProps(shape) << " }";
}

void JsonVisitor::visit(const TriangleShape& shape) {
    m_ss << "{ \"type\": \"triangle\", \"x1\": " << shape.getX1()
        << ", \"y1\": " << shape.getY1()
        << ", \"x2\": " << shape.getX2()
        << ", \"y2\": " << shape.getY2()
        << ", \"x3\": " << shape.getX3()
        << ", \"y3\": " << shape.getY3()
        << formatProps(shape) << " }";
}

void JsonVisitor::visit(const PolygonShape& shape) {
    m_ss << "{ \"type\": \"polygon\", \"points\": [";
    const auto& pts = shape.getPoints();
    for (size_t i = 0; i < pts.size(); ++i) {
        if (i > 0) m_ss << ", ";
        m_ss << pts[i];
    }
    m_ss << "]" << formatProps(shape) << " }";
}
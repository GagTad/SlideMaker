#include "XmlVisitor.h"
#include "Shape.h" 

std::string XmlVisitor::getXmlString() const {
    return m_ss.str();
}

void XmlVisitor::reset() {
    m_ss.str("");
    m_ss.clear();
}

std::string XmlVisitor::formatProps(const Shape& shape) {
    std::stringstream ss;
    const auto& props = shape.getProperties();
    for (const auto& [key, val] : props) {
        std::string cleanKey = key;
        if (cleanKey.rfind("--", 0) == 0) {
            cleanKey = cleanKey.substr(2);
        }
        ss << " " << cleanKey << "=\"" << val << "\"";
    }
    return ss.str();
}

void XmlVisitor::visit(const CircleShape& shape) {
    m_ss << "<shape type=\"circle\" cx=\"" << shape.getCx()
        << "\" cy=\"" << shape.getCy()
        << "\" r=\"" << shape.getRadius() << "\""
        << formatProps(shape) << " />";
}

void XmlVisitor::visit(const RectangleShape& shape) {
    m_ss << "<shape type=\"rectangle\" x=\"" << shape.getX()
        << "\" y=\"" << shape.getY()
        << "\" w=\"" << shape.getWidth()
        << "\" h=\"" << shape.getHeight() << "\""
        << formatProps(shape) << " />";
}

void XmlVisitor::visit(const LineShape& shape) {
    m_ss << "<shape type=\"line\" x1=\"" << shape.getX1()
        << "\" y1=\"" << shape.getY1()
        << "\" x2=\"" << shape.getX2()
        << "\" y2=\"" << shape.getY2() << "\""
        << formatProps(shape) << " />";
}

void XmlVisitor::visit(const TextShape& shape) {
    m_ss << "<shape type=\"text\" x=\"" << shape.getX()
        << "\" y=\"" << shape.getY()
        << "\" fontSize=\"" << shape.getFontSize() << "\""
        << formatProps(shape) << " />";
}

void XmlVisitor::visit(const ImageShape& shape) {
    m_ss << "<shape type=\"image\" x=\"" << shape.getX()
        << "\" y=\"" << shape.getY()
        << "\" w=\"" << shape.getWidth()
        << "\" h=\"" << shape.getHeight() << "\""
        << formatProps(shape) << " />";
}

void XmlVisitor::visit(const EllipseShape& shape) {
    m_ss << "<shape type=\"ellipse\" cx=\"" << shape.getCx()
        << "\" cy=\"" << shape.getCy()
        << "\" rx=\"" << shape.getRx()
        << "\" ry=\"" << shape.getRy() << "\""
        << formatProps(shape) << " />";
}

void XmlVisitor::visit(const TriangleShape& shape) {
    m_ss << "<shape type=\"triangle\""
        << " x1=\"" << shape.getX1() << "\" y1=\"" << shape.getY1() << "\""
        << " x2=\"" << shape.getX2() << "\" y2=\"" << shape.getY2() << "\""
        << " x3=\"" << shape.getX3() << "\" y3=\"" << shape.getY3() << "\""
        << formatProps(shape) << " />";
}

void XmlVisitor::visit(const PolygonShape& shape) {
    m_ss << "<shape type=\"polygon\" points=\"";
    const auto& pts = shape.getPoints();
    for (size_t i = 0; i < pts.size(); ++i) {
        if (i > 0) m_ss << " ";
        m_ss << pts[i];
    }
    m_ss << "\"" << formatProps(shape) << " />";
}
#include "Shape.h"

CircleShape::CircleShape(int cx, int cy, int r)
        : centerX(cx), centerY(cy), radius(r) {
}

std::string CircleShape::toSvg() const
{
    {
        std::stringstream ss;
        ss << "<circle cx=\"" << centerX << "\" cy=\"" << centerY
            << "\" r=\"" << radius << "\" stroke=\"black\" fill=\"transparent\" />";
        return ss.str();
    }
}

RectangleShape::RectangleShape(int x_coord, int y_coord, int w, int h)
    : x(x_coord), y(y_coord), width(w), height(h) {
}

std::string RectangleShape::toSvg() const
{
    std::stringstream ss;
    ss << "<rect x=\"" << x << "\" y=\"" << y
        << "\" width=\"" << width << "\" height=\"" << height
        << "\" stroke=\"black\" fill=\"transparent\" />";
    return ss.str();
}

LineShape::LineShape(int start_x, int start_y, int end_x, int end_y)
    : x1(start_x), y1(start_y), x2(end_x), y2(end_y) {
}

std::string LineShape::toSvg() const
{
    std::stringstream ss;
    ss << "<line x1=\"" << x1 << "\" y1=\"" << y1
        << "\" x2=\"" << x2 << "\" y2=\"" << y2
        << "\" stroke=\"black\" stroke-width=\"2\" />";
    return ss.str();
}

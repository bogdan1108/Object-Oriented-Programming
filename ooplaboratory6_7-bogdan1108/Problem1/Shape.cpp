#include "Shape.h"

Shape::Shape(float x, float y)
{
    m_x = x; m_y = y;
}

float Shape::area()
{
    return -1.0f;
}

std::string Shape::toString()
{
    return "center (" + std::to_string(m_x) + ", " + std::to_string(m_y) + "). ";
}

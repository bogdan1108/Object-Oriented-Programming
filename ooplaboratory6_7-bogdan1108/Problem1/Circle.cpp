#include "Circle.h"

Circle::Circle(float x, float y, float r): Shape{x, y}, m_radius{r}
{
}

float Circle::area()
{
	return 3.14159265f*m_radius*m_radius;
}

std::string Circle::toString()
{
	return Shape::toString() + " Radius: " + std::to_string(m_radius);
}

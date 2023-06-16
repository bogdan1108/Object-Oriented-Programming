#include "Square.h"

Square::Square(float x, float y, float side):Shape{x, y}
{
	m_side = side;
	m_vertices = new Point[4];
	m_vertices[0] = Point{ x - side / 2, y - side / 2 };
	m_vertices[1] = Point{ x - side / 2, y + side / 2 };
	m_vertices[2] = Point{ x + side / 2, y - side / 2 };
	m_vertices[3] = Point{ x + side / 2, y + side / 2 };
}

Square::~Square()
{
	if (m_vertices) {
		delete[] m_vertices;
		m_vertices = nullptr;
	}
}

Square::Square(const Square& other):Shape{other.m_x, other.m_y}
{
	m_side = other.m_side;
	m_vertices = new Point[4];
	for (unsigned int idx{ 0 }; idx < 4; ++idx)
		m_vertices[idx] = other.m_vertices[idx];
}

Square& Square::operator=(const Square& other)
{
	if (&other != this) {
		if (m_vertices)
			delete[] m_vertices;
		m_x = other.m_x;
		m_y = other.m_y;
		m_side = other.m_side;
		m_vertices = new Point[4];
		for (unsigned int idx{ 0 }; idx < 4; ++idx)
			m_vertices[idx] = other.m_vertices[idx];
	}
	return *this;
}

float Square::area()
{
	return m_side * m_side;
}

std::string Square::toString()
{
	return Shape::toString() + " Size: " + std::to_string(m_side);
}

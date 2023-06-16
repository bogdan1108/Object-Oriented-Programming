#include <string>
class Shape
{
public:
	Shape(float x, float y);
	virtual ~Shape() = default;
	virtual float area();
	virtual std::string toString();
protected:
	float m_x, m_y;
};


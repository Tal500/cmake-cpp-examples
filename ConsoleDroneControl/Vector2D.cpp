#include <ostream>
#include <cstdlib>
#include <cmath>
#include <stdexcept>

#include "./Vector2D.h"

Vector2D::Vector2D(int x, int y) : x(x), y(y) {
}

bool Vector2D::operator==(Vector2D other) const {
	return x == other.x && y == other.y;
}

bool Vector2D::operator!=(Vector2D other) const {
	return !(*this == other);
}

Vector2D Vector2D::operator+(Vector2D other) const {
	return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(Vector2D other) const {
	return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(int amount) const {
	return Vector2D(amount * x, amount * y);
}

std::ostream& operator<<(std::ostream& out, Vector2D vec)
{
	out << "(" << vec.x << "," << vec.y << ")";
	return out;
}
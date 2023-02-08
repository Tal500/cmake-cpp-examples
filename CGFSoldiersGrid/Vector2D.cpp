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

int Vector2D::lengthSquared() const {
	return x * x + y * y;
}

int Vector2D::reachableLengthTo(Vector2D other) const {
	if (x == other.x) {
		return std::abs(y - other.y);
	}
	else if (y == other.y)
	{
		return std::abs(x - other.x);
	}
	else {
		return Infinity;
	}
}

Vector2D Vector2D::simpleNormalizedDirectionTo(Vector2D other) const {
	if (x == other.x) {
		if (y < other.y) {
			return Vector2D(0, 1);
		}
		else {
			return Vector2D(0, -1);
		}
	}
	else if (y == other.y)
	{
		if (x < other.x) {
			return Vector2D(1, 0);
		}
		else {
			return Vector2D(-1, 0);
		}
	}
	else {
		throw std::invalid_argument("simpleNormalizedDirectionTo was called but there was no good direction!");
	}
}

Vector2D Vector2D::randInRange(int end) {
	return Vector2D(std::rand() % end, std::rand() % end);
}
#ifndef __VECTOR_2D_H
#define __VECTOR_2D_H

#include <ostream>

/**
 * A simple struct representing a 2D vector.
 *
 * We model the vector only by ints (i.e. not float/double) for simplicity to this project.
 *
 * Notice that we passing the the data by value and not by reference, it makes sense for this small byte sizes (64 bits on most platforms).
 */
struct Vector2D {
public:
	int x;
	int y;

	Vector2D(int x, int y);

	bool operator==(Vector2D other) const;
	bool operator!=(Vector2D other) const;

	Vector2D operator+(Vector2D other) const;

	Vector2D operator-(Vector2D other) const;

	Vector2D operator*(int amount) const;
};

std::ostream& operator<<(std::ostream& out, Vector2D vec);

#endif
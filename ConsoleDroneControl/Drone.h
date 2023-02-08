#ifndef __DRONE_H
#define __DRONE_H

#include <optional>

#include "./Vector2D.h"

class Drone {
public:
	Drone(int maxSpeed, Vector2D location);

	/**
	 * We want the destructor to be virtual so the inheritaed classes can be automatically free when stored by pointer.
	 * We furthermore want the destructor to be pure (i.e. =0) because class Drone is and should be pure,
		 i.e. can only create new objects only by inherited classes. (it's already happen because of the pure virtual `speed()`,
		 but still should be pure for a good practice).
	 */
	virtual ~Drone() = 0;// Pure virtual destructor

	int maxSpeed() { return _maxSpeed; }

	virtual int speed() = 0;

	Vector2D location() { return _location; }

	std::optional<Vector2D> destination() { return _destination; }
	void setDestination(Vector2D value) { _destination = value; }

	void tick();

private:
	int _maxSpeed;
	Vector2D _location;
	std::optional<Vector2D> _destination;
};

#endif
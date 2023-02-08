#include <cmath>

#include "./Drone.h"

Drone::Drone(int maxSpeed, Vector2D location) : _maxSpeed(maxSpeed), _location(location) {

}

// Still need to implement this destructor even though it's pure!
Drone::~Drone() {}

void Drone::tick() {
	if (!_destination) {
		// No need to fly to a place
		return;
	}
	// otherwise

	const Vector2D destination = *_destination;

	int left = this->speed();

	if (_location.x != destination.x) {
		// Fly on the x axis

		const int stepX = std::min(left, std::abs(destination.x - _location.x));
		_location.x += (destination.x > _location.x) ? stepX : -stepX;

		left -= stepX;
	}

	// Continuing flying if needed
	if (_location.y != destination.y) {
		// Fly on the y axis

		const int stepY = std::min(left, std::abs(destination.y - _location.y));
		_location.y += (destination.y > _location.y) ? stepY : -stepY;

		//left -= stepY;// Omitted since have no effect now
	}
}
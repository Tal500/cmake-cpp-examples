#include <stdexcept>

#include "./Drone.h"
#include "./Wolverine.h"

Wolverine::Wolverine(int maxSpeed, int currentPayloadWeight, Vector2D location) : Drone(maxSpeed, location), _currentPayloadWeight(currentPayloadWeight){
	if (currentPayloadWeight >= maxSpeed) {
		throw std::invalid_argument("The given payload weight isn't less than the max speed!");
	}
}

int Wolverine::speed() {
	return maxSpeed() - _currentPayloadWeight;
}
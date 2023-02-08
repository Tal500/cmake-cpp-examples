#ifndef __WOLVERINE_H
#define __WOLVERINE_H

#include "./Drone.h"

class Wolverine : public Drone {
public:
	Wolverine(int maxSpeed, int currentPayloadWeight, Vector2D location);

	int currentPayloadWeight() { return _currentPayloadWeight; }

	virtual int speed();

private:
	int _currentPayloadWeight;
};

#endif
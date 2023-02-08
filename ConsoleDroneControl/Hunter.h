#ifndef __HUNTER_H
#define __HUNTER_H

#include "./Drone.h"

class Hunter : public Drone {
public:
	Hunter(int maxSpeed, Vector2D location);

	virtual int speed();
};

#endif
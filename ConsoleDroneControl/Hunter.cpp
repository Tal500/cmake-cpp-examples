#include "./Drone.h"
#include "./Hunter.h"

Hunter::Hunter(int maxSpeed, Vector2D location) : Drone(maxSpeed, location) {

}

int Hunter::speed() {
	return maxSpeed();
}
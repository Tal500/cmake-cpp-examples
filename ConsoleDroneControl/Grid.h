#ifndef __GRID_H
#define __GRID_H

#include <memory>
#include <unordered_map>

#include "./Vector2D.h"
#include "./Drone.h"

/**
 * The grid of the battlefield
 */
class Grid {
public:
	typedef std::unordered_map<int, std::unique_ptr<Drone>> DroneMap;

	static constexpr int Length = 100;

	static constexpr int MinID = 1;
	static constexpr int MaxID = 9;

	Grid();

	void print() const;

	const Drone& getDrone(int id) const;
	Drone& getDrone(int id);

	void droneTakeoff(int id, std::unique_ptr<Drone> drone);

	void droneGoto(int id, Vector2D destination);

	void droneLand(int id);

	void tick();

private:
	static void idRangeValidation(int id);

	void printSeperator() const;

	DroneMap _drones;
};

#endif
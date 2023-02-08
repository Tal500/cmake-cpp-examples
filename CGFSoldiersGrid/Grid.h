#ifndef __GRID_H
#define __GRID_H

#include <vector>

#include "./Side.h"
#include "./Vector2D.h"
#include "./Soldier.h"

enum POINT_TYPE {
	POINT_TYPE_EMPTY = 0,
	POINT_TYPE_SIDE_ONE = SIDE_ONE,
	POINT_TYPE_SIDE_TWO = SIDE_TWO,
	POINT_TYPE_DEAD_SOLDIER = 3
};

/**
 * The grid of the battlefield
 */
class Grid {
public:
	Grid(int length, int soldierCount);

	int length() const;

	POINT_TYPE pointType(Vector2D point) const;

	// Not in use
	bool pointOnRange(Vector2D point) const;

	void print() const;

	void tick();

	const std::vector<Soldier>& getSoldiersOnSide(SIDE side) const;
	std::vector<Soldier>& getSoldiersOnSide(SIDE side);

	bool hasLivingSoldier(SIDE side) const;

private:
	Vector2D randFreePosition() const;

	void printSeperator() const;

	char pointTypeChar(Vector2D point) const;

	int _length;
	std::vector<Soldier> _soldiersOnSideOne;
	std::vector<Soldier> _soldiersOnSideTwo;
};

#endif
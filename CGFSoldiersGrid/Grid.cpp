#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "./Side.h"
#include "./Vector2D.h"
#include "./Soldier.h"
#include "./Grid.h"

Grid::Grid(int length, int soldierCount) : _length(length) {
	for (int i = 0; i < soldierCount; ++i) {
		_soldiersOnSideOne.push_back(Soldier(SIDE_ONE, randFreePosition()));
	}

	for (int i = 0; i < soldierCount; ++i) {
		_soldiersOnSideTwo.push_back(Soldier(SIDE_TWO, randFreePosition()));
	}
}

int Grid::length() const {
	return _length;
}

Vector2D Grid::randFreePosition() const {
	while (true) {
		const Vector2D proposedPosition = Vector2D::randInRange(_length);

		// If not colliding
		if (pointType(proposedPosition) == POINT_TYPE_EMPTY) {
			return proposedPosition;
		}
	}
}

void Grid::printSeperator() const {
	for (int i = 0; i < _length; ++i) {
		std::cout << "=";
	}

	std::cout << std::endl;
}

POINT_TYPE Grid::pointType(Vector2D point) const {
	// Note: This method isn't efficient, since it scan the whole lists per each point in the grid (the total work is O(lenght^2 * soldierCount)).
	// If we had a time, we might instead scan all the soldiers, and per each soldier "draw" its position in a 2D array,
	//   so the total work for the printing (for examaple) would be O(soldierCount + lenght^2).

	for (const Soldier& soldier : _soldiersOnSideOne) {
		if (soldier.position() == point) {
			if (soldier.isDead()) {
				return POINT_TYPE_DEAD_SOLDIER;
			}
			else
			{
				return POINT_TYPE_SIDE_ONE;
			}
		}
	}

	for (const Soldier& soldier : _soldiersOnSideTwo) {
		if (soldier.position() == point) {
			if (soldier.isDead()) {
				return POINT_TYPE_DEAD_SOLDIER;
			}
			else
			{
				return POINT_TYPE_SIDE_TWO;
			}
		}
	}

	// If not detected
	return POINT_TYPE_EMPTY;
}

bool Grid::pointOnRange(Vector2D point) const {
	return point.x >= 0 && point.x < _length&& point.y >= 0 && point.y < _length;
}

char Grid::pointTypeChar(Vector2D point) const {
	switch (pointType(point)) {
	case POINT_TYPE_EMPTY: return '#';
	case POINT_TYPE_SIDE_ONE: return '1';
	case POINT_TYPE_SIDE_TWO: return '2';
	case POINT_TYPE_DEAD_SOLDIER: return 'X';
	default: throw std::invalid_argument("Point enum value that was returned from pointType() is incorrect.");
	}
}

void Grid::print() const {
	printSeperator();

	for (int x = 0; x < _length; ++x) {
		for (int y = 0; y < _length; ++y) {
			std::cout << pointTypeChar(Vector2D(x, y));
		}

		std::cout << std::endl;
	}

	printSeperator();
}

void Grid::tick() {
	for (Soldier& soldier : _soldiersOnSideOne) {
		soldier.tick(*this);
	}

	for (Soldier& soldier : _soldiersOnSideTwo) {
		soldier.tick(*this);
	}
}

const std::vector<Soldier>& Grid::getSoldiersOnSide(SIDE side) const {
	switch (side)
	{
	case SIDE_ONE: return _soldiersOnSideOne;
	case SIDE_TWO: return _soldiersOnSideTwo;
	default: throw std::invalid_argument("Side enum value is incorrect.");
	}
}

std::vector<Soldier>& Grid::getSoldiersOnSide(SIDE side) {
	switch (side)
	{
	case SIDE_ONE: return _soldiersOnSideOne;
	case SIDE_TWO: return _soldiersOnSideTwo;
	default: throw std::invalid_argument("Side enum value is incorrect.");
	}
}

bool Grid::hasLivingSoldier(SIDE side) const {
	const std::vector<Soldier>& soldiers = getSoldiersOnSide(side);

	return std::find_if(soldiers.begin(), soldiers.end(), [](const Soldier& soldier) { return !soldier.isDead(); }) != soldiers.end();
}
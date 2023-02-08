#ifndef __SOLDIER_H
#define __SOLDIER_H

#include "./Side.h"
#include "./Vector2D.h"

class Grid;

/**
 * Represents a soldier in the game.
 */
class Soldier {
public:
	Soldier(SIDE side, Vector2D position);

	SIDE side() const;

	Vector2D position() const;

	int health() const;

	bool isDead() const;

	void shootOn();

	void tick(Grid& grid);

private:
	SIDE _side;
	Vector2D _position;
	int _health;
};

#endif
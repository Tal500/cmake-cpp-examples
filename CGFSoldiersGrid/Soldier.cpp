#include <cmath>
#include <algorithm>

#include "./Side.h"
#include "./Vector2D.h"
#include "./Soldier.h"
#include "./Grid.h"

constexpr int InitialHealth = 100;
constexpr int ShootingDamage = 50;
constexpr int MaxShootingRange = 10;
constexpr int MaxMovingStep = 10;

Soldier::Soldier(SIDE side, Vector2D position) : _side(side), _position(position), _health(InitialHealth) {
}

SIDE Soldier::side() const {
	return _side;
}

Vector2D Soldier::position() const {
	return _position;
}

int Soldier::health() const {
	return _health;
}

bool Soldier::isDead() const {
	return _health <= 0;
}

void Soldier::shootOn() {
	_health = std::max(0, _health - ShootingDamage);
}

void Soldier::tick(Grid& grid) {
	if (isDead()) {
		return;
	}
	// otherwise

	std::vector<Soldier>& opponentSideSoldiers = grid.getSoldiersOnSide(GetOppositeSide(_side));

	Soldier* nearestOopponentSoldiers = nullptr;
	int nearestLength = Vector2D::Infinity;

	for (Soldier& otherSoldier : opponentSideSoldiers) {
		if (otherSoldier.isDead()) {
			continue;
		}
		// otherwise

		const Vector2D otherSoldierPosition = otherSoldier.position();

		const int reachableLength = _position.reachableLengthTo(otherSoldierPosition);

		if (reachableLength <= MaxShootingRange && reachableLength < nearestLength) {

			// Check that it doesn't shoot throught a living ally!
			const Vector2D normalizedDirection = _position.simpleNormalizedDirectionTo(otherSoldierPosition);
			bool hitAlly = false;
			for (int dist = 1; dist < reachableLength; ++dist) {
				if (grid.pointType(_position + normalizedDirection * dist) == _side) {
					hitAlly = true;
					break;
				}
			}

			if (!hitAlly) {
				// Update the one we're shooting on
				nearestLength = reachableLength;
				nearestOopponentSoldiers = &otherSoldier;
			}
		}
	}

	if (nearestOopponentSoldiers != nullptr) {
		nearestOopponentSoldiers->shootOn();
	}

	// Move the soldier to a new position
	while (true) {
		// I assumed that the soldier can move here to any position in the 10X10 square. Didn't know if it means in the circle or only in X/Y axis.

		Vector2D proposedPosition = _position + Vector2D::randInRange(MaxMovingStep + 1) - Vector2D(MaxMovingStep / 2, MaxMovingStep / 2);
		proposedPosition.x = std::max(0, std::min(grid.length() - 1, proposedPosition.x));
		proposedPosition.y = std::max(0, std::min(grid.length() - 1, proposedPosition.y));

		if (grid.pointType(proposedPosition) == POINT_TYPE_EMPTY || proposedPosition == _position) {
			_position = proposedPosition;
			break;
		}
	}
}
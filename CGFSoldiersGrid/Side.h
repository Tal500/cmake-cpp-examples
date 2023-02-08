#ifndef __SIDES_H
#define __SIDES_H

enum SIDE {
	SIDE_ONE = 1,
	SIDE_TWO = 2
};

constexpr int SidesCount = 2;

inline SIDE GetOppositeSide(SIDE side) {
	return static_cast<SIDE>(SidesCount + 1 - side);
}

#endif
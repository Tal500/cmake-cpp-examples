#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>
#include <stdexcept>

#include "./Vector2D.h"
#include "./Drone.h"
#include "./Grid.h"

Grid::Grid() {
}

void Grid::idRangeValidation(int id) {
	if (!(MinID <= id && id <= MaxID)) {
		throw std::invalid_argument("ID isn't in the range 1-9!");
	}
}

void Grid::printSeperator() const {
	for (int i = 0; i < Length; ++i) {
		std::cout << "=";
	}

	std::cout << std::endl;
}

void Grid::print() const {
	printSeperator();

	constexpr char BlankDisplay = '*';

	// We use a static-sized array on the stack frame for performance reasons,
	//  we can modify it or use other structure if we need it to be with dynamic size (i.e. create a custom class of Array2D).
	char display[Length][Length];
	// all elements initialized to *.
	for (int y = 0; y < Length; ++y) {
		for (int x = 0; x < Length; ++x) {
			display[y][x] = BlankDisplay;
		}
	}

	for (const auto& [id, drone] : _drones) {
		const char idChar = id + '0';

		const Vector2D location = drone->location();
		display[location.y][location.x] = idChar;

		const std::optional<Vector2D> destinationOptional = drone->destination();
		if (!destinationOptional) {
			continue;
		}
		// otherwise

		const Vector2D destination = *destinationOptional;
		if (location == destination) {
			continue;
		}
		// otherwise

		// Print destination tracking
		Vector2D currentPoint = location;
		constexpr char TurningChar = '&';
		constexpr char ArrivalChar = 'X';

		const auto printDisplay = [&display, &currentPoint](char displayChar) {
			char& currentChar = display[currentPoint.y][currentPoint.x];

			// If not having important mark already
			if (!(('0' <= currentChar && currentChar <= '9') || currentChar == ArrivalChar)) {
				currentChar = displayChar;
			}
		};
		const auto printDisplayOnX = [printDisplay, &currentPoint, destination](char stepingChar) {
			if (currentPoint.x != destination.x) {
				printDisplay(stepingChar);
			}
			else {
				if (currentPoint.y != destination.y) {
					printDisplay(TurningChar);
				}
				else {
					printDisplay(ArrivalChar);
				}
			}
		};
		const auto printDisplayOnY = [printDisplay, &currentPoint, destination](char stepingChar) {
			if (currentPoint.y != destination.y) {
				printDisplay(stepingChar);
			}
			else {
				printDisplay(ArrivalChar);
			}
		};

		while (currentPoint.x != destination.x) {
			// Move on the x axis
			if (destination.x > currentPoint.x) {
				currentPoint.x += 1;
				printDisplayOnX('>');
			}
			else {
				currentPoint.x -= 1;
				printDisplayOnX('<');
			}
		}

		while (currentPoint.y != destination.y) {
			// Move on the y axis
			if (destination.y > currentPoint.y) {
				currentPoint.y += 1;
				printDisplayOnY('V');
			}
			else {
				currentPoint.y -= 1;
				printDisplayOnY('^');
			}
		}
	}

	// Print the grid display
	for (int y = 0; y < Length; ++y) {
		for (int x = 0; x < Length; ++x) {
			std::cout << display[y][x];
		}

		std::cout << std::endl;
	}

	printSeperator();
}

const Drone& Grid::getDrone(int id) const {
	idRangeValidation(id);

	try {
		return *_drones.at(id).get();
	}
	catch (std::out_of_range) {
		throw std::invalid_argument("Drone ID doesn't exist!");
	}
}

Drone& Grid::getDrone(int id) {
	idRangeValidation(id);

	try {
		return *_drones.at(id).get();
	}
	catch (std::out_of_range) {
		throw std::invalid_argument("Drone ID doesn't exist!");
	}
}

void Grid::droneTakeoff(int id, std::unique_ptr<Drone> drone) {
	idRangeValidation(id);

	const Vector2D location = drone->location();

	if (!(0 <= location.x && location.x < Length && 0 <= location.y && location.y < Length)) {
		throw std::invalid_argument("Location is out of range!");
	}

	const auto& [it, added] = _drones.insert({ id, std::move(drone) });

	if (!added) {
		throw std::invalid_argument("Drone ID is already taken!");
	}
}

void Grid::droneGoto(int id, Vector2D destination) {
	if (!(0 <= destination.x && destination.x < Length && 0 <= destination.y && destination.y < Length)) {
		throw std::invalid_argument("Destination is out of range!");
	}

	getDrone(id).setDestination(destination);
}

void Grid::droneLand(int id) {
	idRangeValidation(id);

	if (_drones.erase(id) == 0)
	{
		throw std::invalid_argument("Drone ID doesn't exist!");
	}
}

void Grid::tick() {
	for (auto& [id, drone] : _drones) {
		drone->tick();
	}
}
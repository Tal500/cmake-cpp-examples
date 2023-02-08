#include <array>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

#include "./Drone.h"
#include "./Hunter.h"
#include "./Wolverine.h"
#include "./Grid.h"

void transformToLowerCases(std::string& str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

class CommandOption {
public:
	CommandOption(std::string&& command, std::string&& description, bool (*method)(Grid& grid, std::stringstream& s)) : _command(command), _commandLowerCases(command),
		_description(description), _method(method) {

		transformToLowerCases(_commandLowerCases);
	}

	const std::string& command() const { return _command; }

	const char* commandDisplay() const { return _command.empty() ? "(Blank - Pressing Enter)" : _command.c_str(); }

	const std::string& commandLowerCases() const { return _commandLowerCases; }

	const std::string& description() const { return _description; }

	bool call(Grid& grid, std::stringstream& s) const {
		return _method(grid, s);
	}

private:
	std::string _command;
	std::string _commandLowerCases;
	std::string _description;
	bool (*_method)(Grid& grid, std::stringstream& s);
};

const std::array options{
	CommandOption("", "Tick the simulation", [](Grid& grid, std::stringstream& s) {
		grid.tick();
		return true;
	}),
	CommandOption("Print", "Print the map", [](Grid& grid, std::stringstream& s) {
		grid.print();
		return true;
	}),
	CommandOption("Takeoff", "Create a new drone on a given location (Parameters: ID TYPE LOCATION_X LOCATION_Y MAX_SPEED and optional PAYLOAD_WEIGHT, where TYPE is 'hunter' or 'wolverine')", [](Grid& grid, std::stringstream& s) {
		int id;
		s >> id;

		std::string type;
		s >> type;
		transformToLowerCases(type);

		int locationX;
		s >> locationX;

		int locationY;
		s >> locationY;

		const Vector2D location(locationX, locationY);

		int maxSpeed;
		s >> maxSpeed;

		std::unique_ptr<Drone> drone;
		if (type == "hunter") {
			drone.reset(new Hunter(maxSpeed, location));
		}
		else if (type == "wolverine") {
			int payloadWeight;
			s >> payloadWeight;

			drone.reset(new Wolverine(maxSpeed, payloadWeight, location));
		}
		else {
			throw std::invalid_argument("Drone type is invalid!");
		}

		grid.droneTakeoff(id, std::move(drone));

		std::cout << "Drone launched!" << std::endl;
		return true;
	}),
	CommandOption("GetLocation", "Get drone location (Parameter: ID)", [](Grid& grid, std::stringstream& s) {
		int id;
		s >> id;

		std::cout << "Drone location: " << grid.getDrone(id).location() << std::endl;
		return true;
	}),
	CommandOption("GoTo", "Set drone destination (Parameter: ID DESTINATION_X DESTINATION_Y)", [](Grid& grid, std::stringstream& s) {
		int id;
		s >> id;

		int destinationX;
		s >> destinationX;

		int destinationY;
		s >> destinationY;

		const Vector2D destination(destinationX, destinationY);

		grid.droneGoto(id, destination);

		std::cout << "Drone new destination: " << destination << std::endl;
		return true;
	}),
	CommandOption("Land", "Remove the drone (Parameter: ID)", [](Grid& grid, std::stringstream& s) {
		int id;
		s >> id;

		grid.droneLand(id);

		std::cout << "Drone landed!" << std::endl;
		return true;
	}),
	CommandOption("Help", "Display the help", [](Grid& grid, std::stringstream& s) {
		// The help listing is handling outside, due to initialization issue.
		return true;
	}),
	CommandOption("Exit", "Exit the simulation", [](Grid& grid, std::stringstream& s) {
		return false;
	}),
};

void printCommands() {
	for (int i = 0; i < options.size(); ++i) {
		const CommandOption& option = options[i];
		std::cout << (i + 1) << ". " << option.commandDisplay() << " - " << option.description() << std::endl;
	}
}

bool step(Grid& grid) {
	std::string fullCommand;
	//std::cin.ignore();// TODO: Remove?
	std::getline(std::cin, fullCommand);

	std::stringstream s(fullCommand);

	std::string command;
	s >> command;
	transformToLowerCases(command);

	if (command == "help") {
		// Implementing this outside because of initialization issue.
		printCommands();
	}

	const auto it = std::find_if(options.begin(), options.end(), [&command](const CommandOption& option) { return option.commandLowerCases() == command; });
	if (it == options.end()) {
		std::cerr << "Bad command were given! Try again" << std::endl;
		return true;
	}
	else {
		try {
			return it->call(grid, s);
		}
		catch (const std::exception& exception) {
			std::cerr << "Exception during command excecution: " << exception.what() << std::endl;
			return true;
		}
	}
}

int main()
{
	printCommands();

	Grid grid;

	while (step(grid)) {}
}

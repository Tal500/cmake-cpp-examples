#include <iostream>
#include <chrono>
#include <thread>

#include "./Side.h"
#include "./Grid.h"

constexpr int GridLength = 100;
constexpr int MaxInterationCount = 50;
constexpr int MilisecondsTickPeriod = 20;

int main()
{
	// If we want non-determinism:
	//std::srand(std::std::time(nullptr));

	int soldiersCount;

	std::cout << "Enter soldiers count:" << std::endl;
	std::cin >> soldiersCount;

	Grid grid(GridLength, soldiersCount);

	for (int i = 0; i < MaxInterationCount && grid.hasLivingSoldier(SIDE_ONE) && grid.hasLivingSoldier(SIDE_TWO); ++i) {
		grid.print();

		std::this_thread::sleep_for(std::chrono::milliseconds(MilisecondsTickPeriod));

		grid.tick();
	}

	grid.print();

	return 0;
}

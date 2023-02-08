# CMakeList.txt : CMake project for ConsoleDroneControl, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("ConsoleDroneControl")

# Add source to this project's executable.
add_executable (ConsoleDroneControl "main.cpp" "Drone.h" "Vector2D.cpp" "Vector2D.h" "Drone.cpp" "Wolverine.h" "Hunter.cpp" "Wolverine.cpp"  "Grid.cpp" "Grid.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ConsoleDroneControl PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

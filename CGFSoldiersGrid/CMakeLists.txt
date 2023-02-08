# CMakeList.txt : CMake project for CGFSoldiersGrid, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CGFSoldiersGrid")

# Add source to this project's executable.
add_executable (CGFSoldiersGrid "main.cpp"  "Grid.h" "Side.h" "Soldier.h" "Vector2D.h" "Soldier.cpp" "Grid.cpp" "Vector2D.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CGFSoldiersGrid PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeProject1")

SET(SOURCE
  "main.cpp"
 "MemoStore.cpp")

SET(HEADERS
 "MemoStore.h"
 "MemoChoice.h")

ADD_EXECUTABLE(CMakeProject1 ${SOURCE} ${HEADERS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

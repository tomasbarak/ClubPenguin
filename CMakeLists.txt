cmake_minimum_required(VERSION 3.20)
project (ClubPenguin)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(SFML 2.5 COMPONENTS graphics system REQUIRED)
add_executable(ClubPenguin main.cpp functions.h functions.cpp penguinMovement.h)
target_link_libraries(ClubPenguin sfml-graphics)

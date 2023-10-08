// buildMaze.h

#ifndef BUILDMAZE_H
#define BUILDMAZE_H

// Include any necessary headers here
#include <iostream>
#include <mcpp/mcpp.h>
#include <vector>
#include <chrono>
#include <thread>

// Declare the function prototype
void executeBuildMaze(int build_x, int build_y, int build_z, int envLength, int envWidth, const std::vector<std::vector<char>>& envStructure);
void cleanupArea(const mcpp::Coordinate& loc1, const mcpp::Coordinate& loc2);

#endif // BUILDMAZE_H
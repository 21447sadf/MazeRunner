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
void saveOrigBlocks(int build_x, int build_y, int build_z, int envLength, int envWidth);
void executeBuildMaze(int build_x, int build_y, int build_z, int envLength, int envWidth, const std::vector<std::vector<char>>& envStructure);
void reverseBuildMaze(int build_x, int build_y, int build_z, int envLength, int envWidth);

#endif // BUILDMAZE_H
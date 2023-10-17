#include "buildMaze.h"
#include "readMaze.h"

std::vector<std::vector<int>> vec; // Define a vector to store the heights

void executeBuildMaze(int build_x, int build_y, int build_z, int envLength, int envWidth, const std::vector<std::vector<char>>& envStructure) {
    // Establish Connection To Minecraft
    mcpp::MinecraftConnection mc;

    // Teleport Player 10 Blocks Above the basePoint of the Maze
    mcpp::Coordinate newPos(build_x, build_y + 10, build_z);
    mc.setPlayerPosition(newPos);
    
    // Flatten the Maze Area
    mcpp::Coordinate location1(build_x, build_y, build_z);
    mcpp::Coordinate location2(build_x + envLength, build_y, build_z + envWidth);
    // std::vector<std::vector<int>> 
    vec = mc.getHeights(location1, location2);
    for (int row = 0; row < envLength; row++) {
        for (int col = 0; col < envWidth; col++) {
            mcpp::Coordinate curLoc(build_x + row, vec[row][col], build_z + col);
            mcpp::Coordinate fixedLoc(build_x + row, build_y - 1, build_z + col);
            mcpp::BlockType curBlock = mc.getBlock(curLoc);
            mcpp::BlockType airBlock(0);
            if (vec[row][col] == build_y) {
                mc.setBlock(curLoc, airBlock);
            }
            else if (vec[row][col] != build_y) {
                mc.setBlock(fixedLoc, curBlock);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for 50 milliseconds
        }
    }

    // Build Maze
    mcpp::Coordinate coord(build_x, build_y, build_z);
    for (int height = 1; height <= 3; height++) {
        for (int row = 0; row < envLength; row++) {
            for (int col = 0; col < envWidth; col++) {
                mc.setBlock(coord+mcpp::Coordinate(row, 0, col), mcpp::Blocks::AIR);
                if (envStructure[row][col] == 'x') {
                    mc.setBlock(coord+mcpp::Coordinate(row, 0, col), mcpp::Blocks::ACACIA_WOOD_PLANK);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for 50 milliseconds
            }
        }
        coord = mcpp::Coordinate(build_x, build_y + height, build_z);
    }
}

    void reverseBuildMaze(int build_x, int build_y, int build_z, int envLength, int envWidth) {
    // Establish Connection To Minecraft
    mcpp::MinecraftConnection mc;

    // Remove the Maze Blocks
    mcpp::Coordinate coord(build_x, build_y, build_z);
    for (int height = 1; height <= 3; height++) {
        for (int row = 0; row < envLength; row++) {
            for (int col = 0; col < envWidth; col++) {
                mc.setBlock(coord + mcpp::Coordinate(row, 0, col), mcpp::Blocks::AIR);
                std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for 50 milliseconds
            }
        }
        coord = mcpp::Coordinate(build_x, build_y + height, build_z);
    }

    // Restore the Original Blocks
    mcpp::Coordinate location1(build_x, build_y, build_z);
    mcpp::Coordinate location2(build_x + envLength, build_y, build_z + envWidth);
    // std::vector<std::vector<int>> vec = mc.getHeights(location1, location2);
    for (int row = 0; row < envLength; row++) {
        for (int col = 0; col < envWidth; col++) {
            mcpp::Coordinate curLoc(build_x + row, vec[row][col], build_z + col);
            mcpp::Coordinate fixedLoc(build_x + row, build_y - 1, build_z + col);
            // mcpp::BlockType curBlock = mc.getBlock(curLoc);
            mcpp::BlockType originalBlock = mc.getBlock(fixedLoc);
            
            if (vec[row][col] == build_y) {
                mc.setBlock(curLoc, originalBlock);
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for 50 milliseconds
        }
    }
}   
#include "buildMaze.h"
#include "readMaze.h"

std::vector<std::vector<int>> vec; // Define a vector to store the heights
std::vector<std::vector<std::vector<mcpp::BlockType>>> blocks;
int height = 0;
int row = 0;
int col = 0;


void saveOrigBlocks(int build_x, int build_y, int build_z, int envLength, int envWidth) {
    mcpp::MinecraftConnection mc;
    //Save Cuboid of Original Blocks before Flatenning
    mcpp::Coordinate origLoc1(build_x, build_y - 1, build_z);
    mcpp::Coordinate origLoc2(build_x + envLength, build_y + 4, build_z + envWidth);
    blocks = mc.getBlocks(origLoc1, origLoc2);
}

void executeBuildMaze(int build_x, int build_y, int build_z, int envLength, int envWidth, const std::vector<std::vector<char>>& envStructure) {
    // Establish Connection To Minecraft
    mcpp::MinecraftConnection mc;

    // Teleport Player 10 Blocks Above the basePoint of the Maze
    mcpp::Coordinate newPos(build_x, build_y + 10, build_z);
    mc.setPlayerPosition(newPos);

    // for (int h = 0; h < 4; h++) {
    //     for (int i = 0; i < envLength; i++) {
    //         for (int j = 0; j < envWidth; j++) {
    //             std::cout << blocks[h][i][j] << " ";
    //         }
    //         std::cout << std::endl;
    //     }
    //     std::cout << std::endl;
    // }


    // Flatten the Maze Area
    mcpp::Coordinate flatLoc1(build_x, build_y - 1, build_z);
    mcpp::Coordinate flatLoc2(build_x + envLength, build_y, build_z + envWidth);
    // std::vector<std::vector<int>> 
    vec = mc.getHeights(flatLoc1, flatLoc2);
    for (row = 0; row < envLength; row++) {
        for (col = 0; col < envWidth; col++) {
            mcpp::Coordinate curLoc(build_x + row, vec[row][col], build_z + col);
            mcpp::Coordinate fixedLoc(build_x + row, build_y - 1, build_z + col);
            mcpp::BlockType curBlock = mc.getBlock(curLoc);
            if (vec[row][col] != build_y - 1) {
                mc.setBlock(fixedLoc, curBlock);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for 50 milliseconds
        }
    }

    // Remove Above
    // mcpp::Coordinate corner1(build_x, build_y, build_z);
    // mcpp::Coordinate corner2(build_x + envLength, build_y + 3, build_z + envWidth);
    // mc.setBlocks(corner1, corner2, mcpp::Blocks::AIR);
    mcpp::Coordinate removeCoord(build_x, build_y, build_z);
    for (height = 1; height <= 3; height++) {
        for (row = 0; row < envLength; row++) {
            for (col = 0; col < envWidth; col++) {
                mc.setBlock(removeCoord + mcpp::Coordinate(row, 0, col), mcpp::Blocks::AIR);
                std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for 50 milliseconds
            }
        }
        removeCoord = mcpp::Coordinate(build_x, build_y + height, build_z);
    }

    // Build Maze
    mcpp::Coordinate coord(build_x, build_y, build_z);
    for (height = 1; height <= 3; height++) {
        for (row = 0; row < envLength; row++) {
            for (col = 0; col < envWidth; col++) {
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

    // Replace Original Blocks
    mcpp::Coordinate origCoord(build_x, build_y - 1, build_z);
    for (height = 1; height <= 4; height++) {
        for (row = 0; row < envLength; row++) {
            for (col = 0; col < envWidth; col++) {
                mc.setBlock(origCoord + mcpp::Coordinate(row, 0, col), blocks[height - 1][row][col]);
                std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for 50 milliseconds
            }
        }
        origCoord = mcpp::Coordinate(build_x, build_y - 1 + height, build_z);
    }

    // Remove the Maze Blocks
    // mcpp::Coordinate coord(build_x, build_y, build_z);
    // for (int height = 1; height <= 3; height++) {
    //     for (int row = 0; row < envLength; row++) {
    //         for (int col = 0; col < envWidth; col++) {
    //             mc.setBlock(coord + mcpp::Coordinate(row, 0, col), mcpp::Blocks::AIR);
    //             std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for 50 milliseconds
    //         }
    //     }
    //     coord = mcpp::Coordinate(build_x, build_y + height, build_z);
    // }

    // // Restore the Original Blocks
    // mcpp::Coordinate location1(build_x, build_y, build_z);
    // mcpp::Coordinate location2(build_x + envLength, build_y, build_z + envWidth);
    // // std::vector<std::vector<int>> vec = mc.getHeights(location1, location2);
    // for (int row = 0; row < envLength; row++) {
    //     for (int col = 0; col < envWidth; col++) {
    //         mcpp::Coordinate curLoc(build_x + row, vec[row][col], build_z + col);
    //         mcpp::Coordinate fixedLoc(build_x + row, build_y - 1, build_z + col);
    //         // mcpp::BlockType curBlock = mc.getBlock(curLoc);
    //         mcpp::BlockType originalBlock = mc.getBlock(fixedLoc);
            
    //         if (vec[row][col] == build_y) {
    //             mc.setBlock(curLoc, originalBlock);
    //         }
            
    //         std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for 50 milliseconds
    //     }
    }
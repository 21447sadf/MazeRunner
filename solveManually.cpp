#include "solveManually.h"

void executeSolveManually(int build_x, int build_y, int build_z, int envLength, int envWidth, const std::vector<std::vector<char>>& envStructure, bool mode) {
    if (mode == 1) {
    for (int row = 0; row < envLength; row++) {
        for (int col = envWidth - 1; col >= 0; col--) {
            if (envStructure[row][col] == '.') { // Assuming ' ' represents an empty cell
                int playerX = build_x + row;
                int playerZ = build_z + col;
                int playerY = build_y; // Adjust the Y coordinate to avoid being inside blocks

                mcpp::MinecraftConnection mc;
                mcpp::Coordinate playerPos(playerX, playerY, playerZ);
                mc.setPlayerPosition(playerPos);
                break;
            }
        }
    }
    std::cout << "Maze ready to Solve..." << std::endl;
    }

    else {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Step 1: Determine available empty cells
    std::vector<std::pair<int, int>> availableCells; // Store empty cell coordinates (row, col)

    for (int row = 0; row < envLength; row++) {
        for (int col = 0; col < envWidth; col++) {
            if (envStructure[row][col] == '.') { // Assuming ' ' represents an empty cell
                availableCells.push_back(std::make_pair(row, col));
            }
        }
    }

    if (availableCells.empty()) {
        std::cout << "No empty cells found in the maze!" << std::endl;
        return;
    }

    // Step 2: Randomly select one of the available empty cells
    int randomIndex = std::rand() % availableCells.size();
    std::pair<int, int> selectedCell = availableCells[randomIndex];

    // Step 3: Teleport the player to the selected empty cell
    int playerX = build_x + selectedCell.first;
    int playerZ = build_z + selectedCell.second;
    int playerY = build_y; // Adjust the Y coordinate to avoid being inside blocks

    mcpp::MinecraftConnection mc;
    mcpp::Coordinate playerPos(playerX, playerY, playerZ);
    mc.setPlayerPosition(playerPos);
    std::cout << "Maze ready to Solve..." << std::endl;
    }
}
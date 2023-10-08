#include "readMaze.h"

// Constructor to initialize member variables
readMaze::readMaze() {
    build_x = 0;
    build_y = 0;
    build_z = 0;
    envLength = 0;
    envWidth = 0;
    // envStructure = nullptr;
}

// readMaze::~readMaze() {
//     for (int i = 0; i < envLength; i++) {
//         delete[] envStructure[i];
//     }
//     delete[] envStructure;
// }

void readMaze::executeReadMaze() {
    // basePoint of Maze
    // int build_x = 0;
    // int build_y = 0;
    // int build_z = 0;

    std::cout << "Enter the basePoint of maze:" << std::endl;

    std::cin >> build_x;
    std::cin >> build_y;
    std::cin >> build_z;

    // Length & Width of Maze
    // int envLength = 0;
    // int envWidth = 0;

    std::cout << "Enter the length and width of maze:" << std::endl;

    std::cin >> envLength;
    std::cin >> envWidth;

    // Maze Structure
    // char envStructure[envLength][envWidth];
    envStructure.resize(envLength, std::vector<char>(envWidth));
    char readChar;

    std::cout << "Enter the maze structure:" << std::endl;

    for (int row = 0; row < envLength; row++) {
        for (int col = 0; col < envWidth; col++) {
            std::cin >> readChar;
            envStructure[row][col] = readChar;
        }
    }

    // Print Information
    std::cout << "Maze read successfully" << std::endl;
    std::cout << "**Printing Maze**" << std::endl;
    std::cout << "BasePoint: (" << build_x << ", " << build_y << ", " << build_z << ")" << std::endl;
    std::cout << "Structure:" << std::endl;
    for (int row = 0; row < envLength; row++) {
        for (int col = 0; col < envWidth; col++) {
            std::cout << envStructure[row][col];
        }
        std::cout << std::endl;
    }
    std::cout << "**End Printing Maze**" << std::endl;
}

int readMaze::getX() const {
    return build_x;
}

int readMaze::getY() const {
    return build_y;
}

int readMaze::getZ() const {
    return build_z;
}

int readMaze::getLength() const {
    return envLength;
}

int readMaze::getWidth() const {
    return envWidth;
}

const std::vector<std::vector<char>>& readMaze::getEnvStructure() const {
    return envStructure;
}
#include "readMaze.h"

void executeReadMaze() {
    // basePoint of Maze
    int build_x = 0;
    int build_y = 0;
    int build_z = 0;

    std::cout << "Enter the basePoint of maze:" << std::endl;

    std::cin >> build_x;
    std::cin >> build_y;
    std::cin >> build_z;

    // Length & Width of Maze
    int envLength = 0;
    int envWidth = 0;

    std::cout << "Enter the length and width of maze:" << std::endl;

    std::cin >> envLength;
    std::cin >> envWidth;

    // Maze Structure
    char envStructure[envLength][envWidth];
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
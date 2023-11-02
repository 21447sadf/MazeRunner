#include <iostream>
#include <limits>
#include <mcpp/mcpp.h>

//Function to get start point from user
mcpp::Coordinate getBasePoint(void) {
    //Declare inputs
    int xPoint = 0;
    int yPoint = 0;
    int zPoint = 0;

    //Loop variable
    bool validInput = false;

    // Loop to prompt+check base point input
    std::cout << "Enter the basePoint of maze" << std::endl;
        while (!validInput) {
        try {
            if (!(std::cin >> xPoint) || !(std::cin >> yPoint) || !(std::cin >> zPoint)) {
                throw std::invalid_argument("Invalid input. Please enter integers:");
            }
            else {
                validInput = true;
            }
        }
         catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear();  // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
        }
    }

    //Create basePoint coordinate
    mcpp::Coordinate basePoint(xPoint, yPoint, zPoint);

    return basePoint;
}

//Function to get maze length and width from user
std::pair<int, int> getMazeDimensions(void) {
    int z_length = 0;
    int x_length = 0;

    //Loop to prompt+check user length and width input
    bool validInput = false;
    std::cout << "Enter length and width of maze:" << std::endl;
    while (!validInput) {
        try {
            if (!(std::cin >> z_length) || !(std::cin >> x_length)) {
                throw std::invalid_argument("Invalid input. Please enter integers:");
            }
            else if ((z_length % 2 == 0) || (x_length % 2 == 0)) { //If inputs are even
                throw std::invalid_argument("Dimensions must be odd and positive. Please re-enter:");
            }
            else if ((z_length < 3) || (z_length > 99) || (x_length < 3) || (z_length > 99)) { //Inputs not between 3-99
                throw std::invalid_argument("Dimensions exceed allowable limits (3-99). Please re-enter:");
            }
            else {
                validInput = true;
            }
        }
         catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear();  // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
        } 
    }

    return std::make_pair(z_length, x_length);
}

void printMazeInTerminal(std::vector<std::vector<char>> charMaze, int x, int y, int z) {
    int xlength = charMaze.size();
    int zlength = charMaze.at(0).size();
    std::cout << "**Printing Maze**" << std::endl
              << "BasePoint: (" << x << ", " 
                                << y << ", " 
                                << z << ")" << std::endl
              << "Structure: " << std::endl;
    //Print generated maze
    for (int i = 0; i < xlength; i++) {
        for (int j = 0; j < zlength; j++) {
            std::cout << charMaze.at(i).at(j);
        }
        std::cout << std::endl;
    }

    //Print End message
    std::cout << "**End Printing Maze**" << std::endl;
}
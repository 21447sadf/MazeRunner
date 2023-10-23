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
    std::cout << "Enter base point of maze" << std::endl;
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
    std::cout << "Enter length (z) and width (x) of maze:" << std::endl;
    while (!validInput) {
        try {
            if (!(std::cin >> z_length) || !(std::cin >> x_length)) {
                throw std::invalid_argument("Invalid input. Please enter integers:");
            }
            else if ((z_length % 2 == 0) || (x_length % 2 == 0) || (z_length < 0) || (x_length < 0)) { //If inputs are even or negative
                throw std::invalid_argument("Length and width values must be odd and positive. Please re-enter:");
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

    return std::make_pair(x_length, z_length);
}
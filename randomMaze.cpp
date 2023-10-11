#include <iostream> 
#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"
#include <vector>
#include <random>

enum DIRECTIONS{
    UP,
    LEFT,
    RIGHT,
    DOWN
};

void setStartingPoint(std::vector<std::vector<char>> &inputMaze) {
    // Choose random wall:
    // 0 = Top
    // 1 = Right
    // 2 = Bottom 
    // 3 = Left

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> wall_Distrib(0, 3);
    int Wall = wall_Distrib(gen);

    int numCols = inputMaze.at(0).size();
    int numRows = inputMaze.size();
    int position;

    if ((Wall == 0) || (Wall == 2)) {
        std::uniform_int_distribution<> positionDistribution(1, numCols - 2);
        position = positionDistribution(gen);
        if (Wall == 0) {
            inputMaze.at(1).at(position) = '.';
        }
        else if (Wall == 2) {
            inputMaze.at(numRows - 2).at(position) = '.';
        }
    }
    else if ((Wall == 1) || (Wall == 3)) {
        std::uniform_int_distribution<> positionDistribution(1, numRows - 2);
        position = positionDistribution(gen);
        if (Wall == 1) {
            inputMaze.at(position).at(numCols - 2) = '.';
        }
        else if (Wall == 3) {
            inputMaze.at(position).at(1) = '.';
        }
    }
}

bool isValidMove(std::vector<std::vector<char>> &inputMaze, unsigned int Z_Coord, unsigned int X_Coord) {
    //Check if current cell exceeds maze boundaries
    if ((X_Coord >= inputMaze.size() - 1) || (X_Coord == 0)) { 
        return false;
    }
    else if ((Z_Coord >= inputMaze.at(0).size() - 1) || (Z_Coord == 0)) {
        return false;
    }

    //Check if current cell is already carved as path '.'
    if (inputMaze.at(X_Coord).at(Z_Coord) == '.') {
        return false;
    }

    //In all other cases, cell is valid
    return true;
}

void createEntrance(std::vector<std::vector<char>> &inputMaze, unsigned int startZ, unsigned int startX) {
    //If start position is at:
    if ((startZ + 2) == inputMaze.at(0).size()) { //Right wall
        inputMaze.at(startX).at(startZ + 1) = '.';
    }
    else if (startZ == 1) { // Left wall
        inputMaze.at(startX).at(0) = '.';
    }
    else if (startX == 1) {//T Top wall
        inputMaze.at(0).at(startZ) = '.';
    }
    else if (startX + 2 == inputMaze.size()) {// Bottom wall
        inputMaze.at(startX + 1).at(startZ) = '.';
    }

    // NOTE: MIGHT NEED TO ADD CONDITION FOR CORNERS 
}

std::vector<int> findNeighbors(std::vector<std::vector<char>> inputMaze, int currZ, int currX) {
    //Declare output
    std::vector<int> neighbors;

    if (isValidMove(inputMaze, currZ, currX - 1)) {  //Check UP
        neighbors.push_back(0);
    }
    if (isValidMove(inputMaze, currZ - 1, currX)) {  //Check LEFT
        neighbors.push_back(1);
    }
    if (isValidMove(inputMaze, currZ + 1, currX)) {  //Check RIGHT
        neighbors.push_back(2);
    }
    if (isValidMove(inputMaze, currZ, currX + 1)) {  //Check DOWN
        neighbors.push_back(3);
    }

    return neighbors; 
}

void moveCell(std::vector<std::vector<char>> &inputMaze, int &Z, int &X, int direction) {
    if (direction == UP) {
        std::cout << "UP" << std::endl;
        --X;
    }
    else if (direction == LEFT) {
        std::cout << "LEFT" << std::endl;
        --Z;
    }
    else if (direction == RIGHT) {
        std::cout << "RIGHT" << std::endl;
        ++Z;
    }
    else if (direction == DOWN) {
        std::cout << "DOWN" << std::endl;
        ++X;
    }
}

void recursiveBackTrack(std::vector<std::vector<char>> &inputMaze, int currZ, int currX) {
    // Generate random direction
    // 0 = UP
    // 1 = LEFT
    // 2 = RIGHT 
    // 3 = DOWN
    std::random_device rd;
    std::mt19937 gen(rd());
    int direction;
    // int basePoint_Z = currZ;
    // int basePoint_X = currX;

    //Find neighbors of current cell
        std::vector<int> neighbors = findNeighbors(inputMaze, currZ, currX);
        //Print neighbors 
        for (unsigned int i = 0; i < neighbors.size(); i++) {
            std::cout << neighbors.at(i) << " ";
        }
        std::cout << std::endl;
        //Pick random neighbor
        std::uniform_int_distribution<> distrib_direction(0, neighbors.size() - 1);
        direction = distrib_direction(gen);
        moveCell(inputMaze, currZ, currX, neighbors.at(direction));

        //Check if cell is valid
        if (isValidMove(inputMaze, currZ, currX)) {
            inputMaze.at(currX).at(currZ) = '.';
        }

        int i = 0;
    while (i < 10) {
        //TEST IF LOOP IS RUNNING
        std::cout << "LOOP RUNNING" << std::endl;
        //Find neighbors of current cell
        std::vector<int> neighbors = findNeighbors(inputMaze, currZ, currX);
        //Pick random neighbor
        std::uniform_int_distribution<> distrib_direction(0, neighbors.size() - 1);
        direction = distrib_direction(gen);
        //Move cell in generated direction
        moveCell(inputMaze, currZ, currX, neighbors.at(direction));
        //Check if cell is valid
        if (isValidMove(inputMaze, currZ, currX)) {
            inputMaze.at(currX).at(currZ) = '.';
        }

        i++;
    }
}

// bool validBaseCoordinate(int &userInput) {

//     while (std::cin.fail()) { //While input is non-integer values
//         std::cin.clear();
//         std::cin.ignore(1000, '\n');
//         std::cout << "Invalid input - Ensure length and width are positive" << std::endl;
//     }
//     return true;
// }

std::vector<std::vector<char>> randomMaze(void) {

    // curState = ST_RandomMaze;

    //Declare maze as 2D vector
    std::vector<std::vector<char>> maze;

    //Declare inputs
    int xPoint = 0;
    int yPoint = 0;
    int zPoint = 0;
    int z_length = 0;
    int x_length = 0;

    //Input base point
    std::cout << "Enter base point of maze" << std::endl;
    std::cin >> xPoint;
    std::cin >> yPoint;
    std::cin >> zPoint;

    //Input length and width
    std::cout << "Enter z-length and x-length of maze" << std::endl;
    std::cin >> z_length;
    std::cin >> x_length;

    //Check z and x-length are positive
    // while (z_length < 0) {
    //     std::cin >> z_length;
    //     validateUserInput();
    // }
    
    // while (x_length < 0) {
    //     std::cin >> x_length;
    //     validateUserInput();
    // }

    // //Create maze intiialised with 'X' chars
    // for (int i = 0; i < x_length; i++) {
    //     std::vector<char> row(z_length);
    //     maze.push_back(row);
    //     for (unsigned int j = 0; j < row.size(); j++) {
    //         maze.at(i).at(j) = 'X';
    //         std::cout << maze.at(i).at(j) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // //Set starting point
    // setStartingPoint(maze);

    // int startZ = 0;
    // int startX = 0;

    // // TEST: Output modified maze
    // std::cout << std::endl;
    // for (int i = 0; i < x_length; i++) {
    //     std::vector<char> row(z_length);
    //     for (unsigned int j = 0; j < row.size(); j++) {
    //         std::cout << maze.at(i).at(j) << " ";
    //         if (maze.at(i).at(j) == '.') { //TEST
    //             startZ = j;
    //             startX = i;
    //         }
    //     }
    //     std::cout << std::endl;
    // }

    // TEST: Set maze entrance
    createEntrance(maze, startZ, startX);
    std::cout << std::endl;
    for (int i = 0; i < x_length; i++) {
        std::vector<char> row(z_length);
        for (unsigned int j = 0; j < row.size(); j++) {
            std::cout << maze.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

    // TEST: Recursive Backtrack to carve first cell
    recursiveBackTrack(maze, startZ, startX);
    std::cout << std::endl;
    for (int i = 0; i < x_length; i++) {
        std::vector<char> row(z_length);
        for (unsigned int j = 0; j < row.size(); j++) {
            std::cout << maze.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

    return maze;
}

int main(void) {
    std::vector<std::vector<char>> result = randomMaze();

    return EXIT_SUCCESS;
}



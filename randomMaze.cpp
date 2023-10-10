#include <iostream> 
#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"
#include <vector>
#include <random>
// #include "mazeRunner.cpp"

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

bool isValid(std::vector<std::vector<char>> &inputMaze, unsigned int Z_Coord, unsigned int X_Coord) {
    //Check if current cell exceeds maze boundaries
    if ((X_Coord >= inputMaze.size()) || (X_Coord == 0)) { 
        return false;
    }
    else if ((Z_Coord >= inputMaze.at(0).size()) || (Z_Coord == 0)) {
        return false;
    }

    //Check if current cell is already carved as path '.'
    if (inputMaze.at(X_Coord).at(Z_Coord) == '.') {
        return false;
    }

    //In all other cases, cell is valid
    return true;
}

void recursiveBackTrack(std::vector<std::vector<char>> &inputMaze, int currZ, int currX) {
    // Generate random direction
    // 0 = UP
    // 1 = LEFT
    // 2 = RIGHT 
    // 3 = DOWN
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib_direction(0, 3);
    int direction = distrib_direction(gen);
    int nextCell_Z = currZ;
    int nextCell_X = currX;

    //Move cell in generated direction
    if (direction == UP) {
        std::cout << "UP" << std::endl;
        nextCell_X = currX - 1;
    }
    else if (direction == LEFT) {
        std::cout << "LEFT" << std::endl;
        nextCell_Z = currZ - 1;
    }
    else if (direction == RIGHT) {
        std::cout << "RIGHT" << std::endl;
        nextCell_Z = currZ + 1;
    }
    else if (direction == DOWN) {
        std::cout << "DOWN" << std::endl;
        nextCell_X = currX + 1;
    }

    //Check if cell is valid
    if (isValid(inputMaze, nextCell_Z, nextCell_X)) {
        inputMaze.at(nextCell_X).at(nextCell_Z) = '.';
    }
    std::cout << "Done" << std::endl;
}

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

    //Create maze intiialised with 'X' chars
    for (int i = 0; i < x_length; i++) {
        std::vector<char> row(z_length);
        maze.push_back(row);
        for (unsigned int j = 0; j < row.size(); j++) {
            maze.at(i).at(j) = 'X';
            std::cout << maze.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

    //Set starting point
    setStartingPoint(maze);

    int startZ = 0;
    int startX = 0;

    // TEST: Output modified maze
    std::cout << std::endl;
    for (int i = 0; i < x_length; i++) {
        std::vector<char> row(z_length);
        for (unsigned int j = 0; j < row.size(); j++) {
            std::cout << maze.at(i).at(j) << " ";
            if (maze.at(i).at(j) == '.') { //TEST
                startZ = j;
                startX = i;
            }
        }
        std::cout << std::endl;
    }

    // TEST: Recursive Backtrack to carve first cell
    recursiveBackTrack(maze, startZ, startX);
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


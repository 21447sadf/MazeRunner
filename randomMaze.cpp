#include <iostream> 
#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"
#include <vector>
#include <random>
// #include "mazeRunner.cpp"

enum DIRECTIONS{
    UP,
    DOWN,
    RIGHT,
    LEFT
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
        std::uniform_int_distribution<> positionDistribution(1, numCols - 1);
        position = positionDistribution(gen);
        if (Wall == 0) {
            inputMaze.at(1).at(position) = '.';
        }
        else if (Wall == 2) {
            inputMaze.at(numRows - 1).at(position) = '.';
        }
    }
    else if ((Wall == 1) || (Wall == 3)) {
        std::uniform_int_distribution<> positionDistribution(1, numRows - 1);
        position = positionDistribution(gen);
        if (Wall == 1) {
            inputMaze.at(position).at(numCols - 2) = '.';
        }
        else if (Wall == 3) {
            inputMaze.at(position).at(1) = '.';
        }
    }
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

    // //Generate random starting coordinate
    // int max_z = z_length - 1; //MIGHT NEED TO REVIEW X AND Z DIRECTIONS WHEN IMPLEMENTING IN MC
    // int random_z = 0;
    // int max_x = x_length - 1;
    // int random_x = 0;

    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<> distrib_z(1, max_z);
    // random_z = distrib_z(gen);
    // std::uniform_int_distribution<> distrib_x(1, max_x);
    // random_x = distrib_x(gen);
    // std::cout << random_x << " " << random_z << std::endl;
    
    // //Set starting point in maze to '.'
    // maze.at(random_z).at(random_x) = '.';

    //Set starting point
    setStartingPoint(maze);

    // TEST: Output modified maze
    std::cout << std::endl;
    for (int i = 0; i < x_length; i++) {
        std::vector<char> row(z_length);
        for (unsigned int j = 0; j < row.size(); j++) {
            std::cout << maze.at(i).at(j) << " ";
        }
        std::cout << std::endl;
    }

    // //Generate random direction
    // std::uniform_int_distribution<> distrib_direction(0, 3);
    // // int direction = distrib_direction(gen);
    // int direction = 0;
    // if (direction == UP) {
    //     maze.at(random_z+1).at(random_x) = '.';
    //     std::cout << "Entrance created";
    // }

    // //TEST: Output modified maze
    // for (int i = 0; i < width; i++) {
    //     std::vector<char> row(length);
    //     for (unsigned int j = 0; j < row.size(); j++) {
    //         std::cout << maze.at(i).at(j) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    return maze;
}

int main(void) {
    std::vector<std::vector<char>> result = randomMaze();

    return EXIT_SUCCESS;
}


#include <iostream> 
#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"
#include <vector>
#include <random>
#include <stack>
#include <utility>
#include <algorithm>

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

    // //Check if cell is already visited
    // if (visited.at(X_Coord).at(Z_Coord)) {
    //     return false;
    // }

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

std::vector<int> findNeighbors(std::vector<std::vector<char>> inputMaze, int currZ, int currX, std::vector<std::vector<bool>> visited) {
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
std::vector<std::pair<int, int>> directions = { {0, -2}, {0, 2}, {-2, 0}, {2, 0} };
std::vector<std::vector<bool>> visited;
visited.resize(inputMaze.size(), std::vector<bool>(inputMaze[0].size(), false));

    // Shuffle the directions randomly
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(directions.begin(), directions.end(), gen);

    for (const auto& direction : directions) {
        int newZ = currZ + direction.first;
        int newX = currX + direction.second;

        if (isValidMove(inputMaze, newZ, newX)) {
            if (inputMaze[newX][newZ] == 'X') {
                // Mark the new cell as a path
                inputMaze[newX][newZ] = '.';

                // Remove the wall between the current cell and the new cell
                inputMaze[currX + direction.first / 2][currZ + direction.second / 2] = '.';

                recursiveBackTrack(inputMaze, newZ, newX);
            }
        }
    }
    // int direction;
    // std::stack<std::pair<int, int>> pathStack;
    // std::vector<std::vector<bool>> visited;
    // pathStack.push(std::make_pair(currZ, currX));
    // visited.resize(inputMaze.size(), std::vector<bool>(inputMaze[0].size(), false));

    // while (!pathStack.empty()) {
    //     // Find neighbors of the current cell
    //     std::vector<int> neighbors = findNeighbors(inputMaze, currZ, currX, visited);

    //     // Move cells if neighbors are not empty
    //     if (!neighbors.empty()) {

    //         std::random_device rd;
    //         std::mt19937 gen(rd());
    //         std::uniform_int_distribution<> distrib_direction(0, neighbors.size() - 1);
    //         direction = neighbors.at(distrib_direction(gen));

    //         moveCell(inputMaze, currZ, currX, direction);
    //         inputMaze.at(currX).at(currZ) = '.';
    //         visited.at(currX).at(currZ) = true;
    //         pathStack.push(std::make_pair(currZ, currX));

    //     } else if (neighbors.empty()) {
    //         // Backtrack to the previous cell with unvisited neighbors
    //         bool foundPreviousCell = false;
    //         while (!pathStack.empty() && !foundPreviousCell) {
    //             std::pair<int, int> prevCell = pathStack.top();
    //             pathStack.pop();
    //             currZ = prevCell.first;
    //             currX = prevCell.second;

    //             // Check if the previous cell has unvisited neighbors
    //             if (!visited.at(currX).at(currZ) && !findNeighbors(inputMaze, currZ, currX, visited).empty()) {
    //                 foundPreviousCell = true;
    //             }
    //         }

    //         if (!foundPreviousCell) {
    //             // If no such cell is found, exit the loop
    //             break;
    //         }
    //     } else {
    //         // If there are no cells left to backtrack to, exit the loop
    //         break;
    //     }
    // }
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

// #include <iostream>
// #include <vector>
// #include <random>
// #include <ctime>
// #include <algorithm>

// enum class Direction {
//     UP, DOWN, LEFT, RIGHT
// };

// const int MAZE_SIZE = 11; // Adjust the size as needed

// // Helper function to check if a cell is within the maze bounds
// bool isValidCell(int x, int y) {
//     return x >= 0 && x < MAZE_SIZE && y >= 0 && y < MAZE_SIZE;
// }

// // Helper function to shuffle directions randomly
// std::vector<Direction> shuffleDirections() {
//     std::vector<Direction> directions = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
//     std::random_device rd;
//     std::mt19937 g(rd());
//     std::shuffle(directions.begin(), directions.end(), g);
//     return directions;
// }

// // Recursive function to generate the maze
// void generateMaze(std::vector<std::vector<char>>& maze, int x, int y) {
//     std::vector<Direction> directions = shuffleDirections();

//     for (const auto& direction : directions) {
//         int dx = 0, dy = 0;

//         switch (direction) {
//             case Direction::UP:
//                 dy = -2;
//                 break;
//             case Direction::DOWN:
//                 dy = 2;
//                 break;
//             case Direction::LEFT:
//                 dx = -2;
//                 break;
//             case Direction::RIGHT:
//                 dx = 2;
//                 break;
//         }

//         int nx = x + dx;
//         int ny = y + dy;

//         if (isValidCell(nx, ny) && maze[ny][nx] == ' ') {
//             // Mark the path
//             maze[ny][nx] = '.';
//             maze[y + dy / 2][x + dx / 2] = '.';
//             generateMaze(maze, nx, ny);
//         }
//     }
// }

// int main() {
//     // Initialize the maze
//     std::vector<std::vector<char>> maze(MAZE_SIZE, std::vector<char>(MAZE_SIZE, ' '));

//     // Seed the random number generator
//     std::srand(static_cast<unsigned>(std::time(nullptr)));

//     // Set a random starting point
//     int startX = std::rand() % (MAZE_SIZE / 2) * 2;
//     int startY = std::rand() % (MAZE_SIZE / 2) * 2;

//     // Generate the maze starting from the random point
//     generateMaze(maze, startX, startY);

//     // Print the maze
//     for (int i = 0; i < MAZE_SIZE; i++) {
//         for (int j = 0; j < MAZE_SIZE; j++) {
//             std::cout << maze[i][j] << ' ';
//         }
//         std::cout << '\n';
//     }

//     return 0;
// }


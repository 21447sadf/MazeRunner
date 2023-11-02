#include <iostream> 
#include <vector>
#include <random>
#include <utility>
#include <algorithm>

//Function to generate a random number 
int generateRandomOddNumber(int min, int max) {
    //Setup random device with min and max as limits
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);

    //Declare random number
    int randomNum;

    //Generate numbers until an odd value is generated
    do {
        randomNum = distribution(gen);
    } while (randomNum % 2 == 0); // Ensure it's an odd number

    return randomNum;
}

//Function to set start point of maze
std::pair<int, int> setStartingPoint(std::vector<std::vector<char>> &inputMaze, bool mode) {
    if (mode == 1) {
        return std::make_pair(1, 1);
    }
    //Start point variable
    std::pair<int, int> startPoint;

    //Set up random device to select a wall                 // Walls are indexed as follows
    std::random_device rd;                                  // 0 = Top
    std::mt19937 gen(rd());                                 // 1 = Right
    std::uniform_int_distribution<> wall_Distrib(0, 3);     // 2 = Bottom
    int Wall = wall_Distrib(gen);                           // 3 = Left

    //Declare number of rows and columns
    int numCols = inputMaze.at(0).size();
    int numRows = inputMaze.size();

    // If top or bottom wall selected
    if ((Wall == 0) || (Wall == 2)) { 
        //Generate random odd number between min (1) and max Z (columns - 2)
        int Z = generateRandomOddNumber(1, numCols - 2);
        //If top wall is selected
        if (Wall == 0) {
            //Set start point (1, Z)
            inputMaze.at(1).at(Z) = '.';
            startPoint = std::make_pair(Z, 1);
        }
        //If bottom wall is selected
        else if (Wall == 2) {
            //Set start point (X - 2, Z)
            inputMaze.at(numRows - 2).at(Z) = '.';
            startPoint = std::make_pair(Z, numRows - 2);
        }
    }
    // Else if left or right wall selected
    else if ((Wall == 1) || (Wall == 3)) { 
        //Generate random odd number between min and max X
        int X = generateRandomOddNumber(1, numRows - 2);
        //If right wall selected
        if (Wall == 1) {
            inputMaze.at(X).at(numCols - 2) = '.';
            startPoint = std::make_pair(numCols - 2, X);
        }
        //If left wall selection
        else if (Wall == 3) {
            inputMaze.at(X).at(1) = '.';
            startPoint = std::make_pair(1, X);
        }
    }
    return startPoint;

}

//Function to check whether a cell is valid 
bool isValid(std::vector<std::vector<char>> &inputMaze, int Z_Coord, int X_Coord, int direction) { 
    int rows = inputMaze.size();
    int columns = inputMaze.at(0).size();
    //Check if current cell exceeds maze boundaries
    if ((X_Coord >= rows - 1) || (X_Coord <= 0)) { 
        return false;
    }
    else if ((Z_Coord >= columns - 1) || (Z_Coord <= 0)) {
        return false;
    }
    else {
        //Check if current cell's wall is already carved as path '.'
        if (direction == 0) { //UP
            if ((inputMaze.at(X_Coord).at(Z_Coord) == '.') || (inputMaze.at(X_Coord+1).at(Z_Coord) == '.')) {  // Check for 'X' and '_' UP
            return false;
            }
        }
        else if (direction == 1) { //RIGHT 
            if ((inputMaze.at(X_Coord).at(Z_Coord) == '.') || (inputMaze.at(X_Coord).at(Z_Coord-1) == '.')) {
            return false;
            }
        }
        else if (direction == 2) { //DOWN
            if ((inputMaze.at(X_Coord).at(Z_Coord) == '.') || (inputMaze.at(X_Coord-1).at(Z_Coord) == '.')) {
            return false;
            }
        }
        else if (direction == 3) { //LEFT
            if (((inputMaze.at(X_Coord).at(Z_Coord) == '.')) || (inputMaze.at(X_Coord-1).at(Z_Coord + 1) == '.')) {
                return false;
            }
        }
    }

    //In all other cases, cell is valid
    return true;
}

//Function to create maze entrance
void createEntrance(std::vector<std::vector<char>> &inputMaze, int startZ, int startX, bool mode) {
    //Set rows and columns
    int rows = inputMaze.size();
    int columns = inputMaze.at(0).size();

    if (mode == 0) { //NORMAL MODE
        //If start position is at:
        if ((startZ + 2) == columns) { //Right wall
            inputMaze.at(startX).at(startZ + 1) = '.';
        }
        else if (startZ == 1) { // Left wall
            inputMaze.at(startX).at(0) = '.';
        }
        else if (startX == 1) {//T Top wall
            inputMaze.at(0).at(startZ) = '.';
        }
        else if (startX + 2 == rows) {// Bottom wall
            inputMaze.at(startX + 1).at(startZ) = '.';
        }

    }
    else if (mode == 1) { //TEST MODE
        inputMaze.at(1).at(0) = '.';
    }
}

//Function to return vector with unvisited neighbors of current cell
std::vector<std::pair<int, int>> unvisitedNeighbors(std::vector<std::vector<char>> maze, int Z, int X) {
    std::vector<std::pair<int, int>> neighbors;

    // if UP is valid
    if (isValid(maze, Z, X - 2, 0)) {
        //Add to neighbors
        neighbors.push_back(std::make_pair(Z, X - 2));
    }

    //if RIGHT is valid
    if (isValid(maze, Z + 2, X, 1)) {
        //Add to neighbors
        neighbors.push_back(std::make_pair(Z + 2, X));
    }

    //if DOWN is valid
    if (isValid(maze, Z, X + 2, 2)) {
        //Add to neighbors
        neighbors.push_back(std::make_pair(Z, X + 2));
    }

    //if LEFT is valid
    if (isValid(maze, Z - 2, X, 3)) {
        //Add to neighbors
        neighbors.push_back(std::make_pair(Z - 2, X));
    }

return neighbors;
}

//Function to carve path through maze
void carveMaze(std::vector<std::vector<char>> &maze, int Z, int X, std::vector<std::pair<int, int>> &path, bool mode) {
    //Carve path on current cell
    maze.at(X).at(Z) = '.';

    //Variables to store coordinates of next cell on path
    int nextZ;
    int nextX;

    // Generate all neighbors and shuffle
    std::vector<std::pair<int, int>> unvisitedneighbors = unvisitedNeighbors(maze, Z, X);
    std::random_device rd;
    std::mt19937 gen(rd());

    //NORMAL MODE - Shuffle to change order of directions
    if (mode == 0) {  
        std::shuffle(unvisitedneighbors.begin(), unvisitedneighbors.end(), gen);
    }
    //TEST MODE - Do nothing, neighbors are in order UP, RIGHT, DOWN, LEFT

    // BASE CASE: No unvisited neighbors and path isn't empty
    if (unvisitedneighbors.empty() && !path.empty()) { 
        //Backtrack to previous cell
        path.pop_back();
        //If path is not empty after backtracking
        if (!path.empty()) {
            std::pair<int, int> prevCell = path.back();
            nextZ = prevCell.first;
            nextX = prevCell.second;
            //RECURSIVE STEP: Call buildMaze on previous cell
            carveMaze(maze, nextZ, nextX, path, mode);
        }
    }
    else {
        // BASE CASE: While there are unvisited neighbors
        if (!unvisitedneighbors.empty()) {
            //Choose a random neighbor and extract its coordinates
            std::pair<int, int> direction = unvisitedneighbors.at(unvisitedneighbors.size() - 1);
            unvisitedneighbors.pop_back();
            nextZ = direction.first;
            nextX = direction.second;

            //Remove wall between current cell and neighbor
            if ((nextX - X == -2) && (nextZ - Z == 0)) {  // neighbor is UP
                maze.at(nextX + 1).at(nextZ) = '.';
            }
            else if ((nextX - X == 0) && (nextZ - Z == -2)) {  // neighbor is LEFT
                maze.at(nextX).at(nextZ + 1) = '.';
            }
            else if ((nextX - X == 0) && (nextZ - Z == 2)) {  // neighbor is RIGHT
                maze.at(nextX).at(nextZ - 1) = '.';
            }
            else if ((nextX - X == 2) && (nextZ - Z == 0)) {  // neighbor is DOWN
                maze.at(nextX - 1).at(nextZ) = '.';
            }
            //Add cell to path of visited cells
            path.push_back(std::make_pair(nextZ, nextX));
            //RECURSIVE STEP: Call buildMaze on next cell
            carveMaze(maze, nextZ, nextX, path, mode);
        }
    }
} 

//Function to generate a random maze
std::vector<std::vector<char>> genMaze(int x_length, int z_length, bool mode) {

    //Declare maze as 2D vector
    std::vector<std::vector<char>> maze;

    //Initialise maze
    for (int i = 0; i < x_length; i++) {
        std::vector<char> row(z_length);
        maze.push_back(row);
        //If even row, initialise it to 'XXXX...'
        if ((i % 2) == 0) {
            for (unsigned int j = 0; j < row.size(); j++) {
                maze.at(i).at(j) = 'x';
            }
        }
        //If uneven row, initialise it to 'X_X_X...'
        else if ((i % 2) == 1) {
            for (unsigned int j = 0; j < row.size(); j++) {
                maze.at(i).at(j) = ((j % 2) == 0) ? ('x') : ('_');
            }
        }
    }

    // Set starting point
    std::pair<int, int> startPoint = setStartingPoint(maze, mode);

    int startZ = startPoint.first;
    int startX = startPoint.second;

    //Set maze entrance
    createEntrance(maze, startZ, startX, mode);

    //Initialise path and add start point
    std::vector<std::pair<int, int>> path;
    path.push_back(std::make_pair(startZ, startX));

    //Build maze
    carveMaze(maze, startZ, startX, path, mode);

    //Output "Maze generated successfully" 
    std::cout << "Maze generated successfully" << std::endl;

    return maze;
}
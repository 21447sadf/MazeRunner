#include <iostream> 
#include <mcpp/mcpp.h>
#include <vector>
#include <random>
#include <utility>
#include <algorithm>

//ASSUMPTIONS:
//Terrain is made of one blocktype
//No more than one obstacle (existing as a cuboid object on the ground) is present on terrain

//Function to generate a random number 
int E1_generateRandomOddNumber(int min, int max) {
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
std::pair<int, int> E1_setStartingPoint(std::vector<std::vector<char>> &inputMaze) {
    //Start point variable
    std::pair<int, int> startPoint;

    //Declare number of rows and columns
    int numCols = inputMaze.at(0).size();
    int numRows = inputMaze.size();

    //TOP WALL
    int Z = generateRandomOddNumber(1, numCols - 2);
    int X = generateRandomOddNumber(1, numRows - 2);
    if ((inputMaze[0][Z] == 'x') && (inputMaze[1][Z] != ' ')) {
        inputMaze[1][Z] = '.';
        startPoint = std::make_pair(Z, 1);
    }
    //BOTTOM WALL
    else if ((inputMaze[numRows - 1][Z] == 'x') && (inputMaze[numRows - 2][Z] != ' ')) {
        inputMaze[numRows - 2][Z] = '.';
        startPoint = std::make_pair(Z, numRows - 2);
    }
    //RIGHT WALL
    else if ((inputMaze[X][numCols - 1] == 'x') && ((inputMaze[X][numCols - 2]) != ' ')) {
        inputMaze[X][numCols - 2] = '.';
        startPoint = std::make_pair(numCols - 2, X);
    }
    else if ((inputMaze[X][0] = 'x') && (inputMaze[X][1] != ' ')) {
        inputMaze[X][1] = '.';
        startPoint = std::make_pair(1, X);
    }
    return startPoint;

}

//Function to check whether a cell is valid 
bool E1_isValid(std::vector<std::vector<char>> &inputMaze, int Z_Coord, int X_Coord, int direction) { 
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
        //Check if current cell's wall is already carved as path '.' or cell is 'x'
        if (direction == 0) { //UP
            if ((inputMaze.at(X_Coord).at(Z_Coord) != '_') || (inputMaze.at(X_Coord+1).at(Z_Coord) != 'x')) {  // Check for 'X' and '_' UP
            return false;
            }
        }
        else if (direction == 1) { //RIGHT 
            if ((inputMaze.at(X_Coord).at(Z_Coord) != '_') || (inputMaze.at(X_Coord).at(Z_Coord-1) != 'x')) {
            return false;
            }
        }
        else if (direction == 2) { //DOWN
            if ((inputMaze.at(X_Coord).at(Z_Coord) != '_') || (inputMaze.at(X_Coord-1).at(Z_Coord) != 'x')) {
            return false;
            }
        }
        else if (direction == 3) { //LEFT
            if (((inputMaze.at(X_Coord).at(Z_Coord) != '_')) || (inputMaze.at(X_Coord-1).at(Z_Coord + 1) != 'x')) {
                return false;
            }
        }
    }

    //In all other cases, cell is valid
    return true;
}

//Function to create maze entrance
void E1_createEntrance(std::vector<std::vector<char>> &inputMaze, int startZ, int startX) {
    //Set rows and columns
    int rows = inputMaze.size();
    int columns = inputMaze.at(0).size();

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

//Function to return vector with unvisited neighbors of current cell
std::vector<std::pair<int, int>> E1_unvisitedNeighbors(std::vector<std::vector<char>> maze, int Z, int X) {
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

bool slopeIsValid(mcpp::Coordinate basePoint, int X, int Y, int nextX, int nextY) {
    return false;
}

//Function to carve path through maze
void E1_carveMaze(std::vector<std::vector<char>> &maze, mcpp::Coordinate basePoint, int Z, int X, std::vector<std::pair<int, int>> &path) {
    mcpp::MinecraftConnection mc;
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
    std::shuffle(unvisitedneighbors.begin(), unvisitedneighbors.end(), gen);

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
            E1_carveMaze(maze, basePoint, nextZ, nextX, path);
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

            //Height on current cell
            int currHeight = mc.getHeight(basePoint.x + X, basePoint.z + Z);

            //Check slope between current cell and neighbor < 1
            //IF this condition is met:
            //Remove wall between current cell and neighbor
            //ELSE IF condition is not met
            //Set a wall on neighbor
            if ((nextX - X == -2) && (nextZ - Z == 0)) {  // neighbor is UP
                if (abs(mc.getHeight(basePoint.x + nextX + 1, basePoint.z + nextZ) - currHeight) <= 1 &&
                   (abs(mc.getHeight(basePoint.x + nextX + 1, basePoint.z + nextZ) - mc.getHeight(basePoint.x + nextX, basePoint.z + nextZ)) <= 1)) {
                    maze.at(nextX + 1).at(nextZ) = '.';
                    path.push_back(std::make_pair(nextZ, nextX));
                }
                //ELSE: 
                //Backtrack to previous cell
                else {
                    // maze.at(nextX + 2).at(nextZ) = 'x';
                    path.pop_back();
                    nextZ = path.back().first;
                    nextX = path.back().second;
                }
            }
            else if ((nextX - X == 0) && (nextZ - Z == -2)) {  // neighbor is LEFT
                if ((abs(mc.getHeight(basePoint.x + nextX, basePoint.z + nextZ + 1) - currHeight) <= 1) &&
                   (abs(mc.getHeight(basePoint.x + nextX, basePoint.z + nextZ + 1) - mc.getHeight(basePoint.x + nextX, basePoint.z + nextZ)) <= 1)) {
                    maze.at(nextX).at(nextZ + 1) = '.';
                    path.push_back(std::make_pair(nextZ, nextX));
                }
                else {
                    // maze.at(nextX).at(nextZ + 2) = 'x';
                    path.pop_back();
                    nextZ = path.back().first;
                    nextX = path.back().second;
                }
            }
            else if ((nextX - X == 0) && (nextZ - Z == 2)) {  // neighbor is RIGHT
                if ((abs(mc.getHeight(basePoint.x + nextX, basePoint.z + nextZ - 1) - currHeight) <= 1) &&
                   (abs(mc.getHeight(basePoint.x + nextX, basePoint.z + nextZ - 1) - mc.getHeight(basePoint.x + nextX, basePoint.z + nextZ)) <= 1)) {
                    maze.at(nextX).at(nextZ - 1) = '.';
                    path.push_back(std::make_pair(nextZ, nextX));
                }
                else {
                    // maze.at(nextX).at(nextZ - 2) = 'x';
                    path.pop_back();
                    nextZ = path.back().first;
                    nextX = path.back().second;
                }
            }
            else if ((nextX - X == 2) && (nextZ - Z == 0)) {  // neighbor is DOWN
                if ((abs(mc.getHeight(basePoint.x + nextX - 1, basePoint.z + nextZ) - currHeight) <= 1) &&
                   (abs(mc.getHeight(basePoint.x + nextX - 1, basePoint.z + nextZ) - mc.getHeight(basePoint.x + nextX, basePoint.z + nextZ)) <= 1)) {
                    maze.at(nextX - 1).at(nextZ) = '.';
                    path.push_back(std::make_pair(nextZ, nextX));
                }
                else {
                    path.pop_back();
                    nextZ = path.back().first;
                    nextX = path.back().second;
                }
            }
            //Add cell to path of visited cells
            // path.push_back(std::make_pair(nextZ, nextX));
            //RECURSIVE STEP: Call buildMaze on next cell
            E1_carveMaze(maze, basePoint, nextZ, nextX, path);
        }
    }
} 

// //Function to find obstacles coordinates in MC (x, z)
// std::pair<int, int> findObstacleCoord(mcpp::Coordinate basePoint, int xLength, int zLength) {
//     mcpp::MinecraftConnection mc;

//         for (int z = 0; z < zLength; z++) {
//             for (int x = 0; x < xLength; x++) {
//                 mcpp::BlockType ground = mc.getBlock(basePoint + mcpp::Coordinate(x, -1, z));
//                 int height = mc.getHeight(basePoint.x + x, basePoint.z + z);
//                 //If block at height of area is not the same as ground, obstacle is present
//                 if (!(ground == mc.getBlock(mcpp::Coordinate(basePoint.x + x, height, basePoint.z + z)))) {
//                     return std::make_pair(x + 1, z + 1);
//                 }
//                 }
//             }
//     return std::make_pair(0, 0);
// }

// //Returns -1 for invalid environment, otherwise returns length of obstacle as an odd number
// int isTerrainSuitable(mcpp::Coordinate basePoint, int xLength, int zLength) {
//     mcpp::MinecraftConnection mc;

//     int currLength = 0;
//     int currWidth = 0;
//     int maxLength = 0;
//     int maxWidth = 0;
//     int obstDimension;

//     // CHECK: Basepoint is in air
//     if (mc.getBlock(basePoint + mcpp::Coordinate(0, -1, 0)) == mcpp::Blocks::AIR) {
//         return -1;
//     }
    
//         for (int x = 0; x < xLength; x++) {
//             for (int z = 0; z < zLength; z++) {
//                 mcpp::BlockType ground = mc.getBlock(basePoint + mcpp::Coordinate(x, -1, z));
//                 int height = mc.getHeight(basePoint.x + x, basePoint.z + z);
//                 //If block at height of area is not the same as ground, obstacle is present
//                 if (!(ground == mc.getBlock(mcpp::Coordinate(basePoint.x + x, height, basePoint.z + z)))) {
//                     currLength++;
//                 }
//             }
//             //Update the max length of obstacle
//             if (currLength > maxLength) {
//                 maxLength = currLength;
//             }
//             currLength = 0;
//         }

//         for (int z = 0; z < zLength; z++) {
//             for (int x = 0; x < xLength; x++) {
//                 mcpp::BlockType ground = mc.getBlock(basePoint + mcpp::Coordinate(x, -1, z));
//                 int height = mc.getHeight(basePoint.x + x, basePoint.z + z);
//                 //If block at height of area is not the same as ground, obstacle is present
//                 if (!(ground == mc.getBlock(mcpp::Coordinate(basePoint.x + x, height - 1, basePoint.z + z)))) {
//                     currWidth++;
//                 }
//                 }
//                 //Update max width of obstacle
//                 if (currWidth > maxWidth) {
//                     maxWidth = currWidth;
//                 }
//                 currWidth = 0;
//             }

//         //Set object length with larger dimension
//         obstDimension = (maxWidth >= maxLength) ? (maxWidth) : (maxLength);

//         //If even, change to odd length
//         if (obstDimension % 2 == 0) {
//             obstDimension += 1;
//         }
    

//     return obstDimension;
// }

//Function to generate a random maze
std::vector<std::vector<char>> E1_genMaze(mcpp::Coordinate basePoint, int x_length, int z_length) {
    
    // //Set maze length to larger value/convert to odd
    // int largerLength = 0;
    // largerLength = (x_length >= z_length) ? (x_length) : (z_length);
    // largerLength = (largerLength % 2 == 0) ? (largerLength + 1) : (largerLength);

    // //Set x_length and z_length to new val
    // x_length = largerLength;
    // z_length = largerLength;

    //Declare maze as 2D vector
    std::vector<std::vector<char>> maze;

    // //Check if terrain is suitable and find coords of obstacle
    // int obstLength = isTerrainSuitable(basePoint, x_length, z_length);
    // std::pair<int, int> coord = findObstacleCoord(basePoint, x_length, z_length);
    // int obstStartX = coord.first;
    // int obstStartZ = coord.second;

    // // //Return empty maze if terrain isn't suitable 
    // if (obstLength == -1) {
    //     return maze;
    // }

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

    //Scan MC Terrain and block out obstacles from maze
    mcpp::MinecraftConnection mc;
    mcpp::BlockType ground = mc.getBlock(mcpp::Coordinate(basePoint.x, basePoint.y - 1, basePoint.z));
    for (int i = 0; i < x_length; i++)  {
        for (int j = 0; j < z_length; j++) {
            //Height of terrain
            int currHeight = mc.getHeight(basePoint.x + i, basePoint.z + j);

            //Heighest block on terrain
            mcpp::BlockType obstacle = mc.getBlock(mcpp::Coordinate(basePoint.x + i, currHeight, basePoint.z + j));
            
            //Block out obstacle from maze with 'x'
            if (!(obstacle == ground)) {
                std::cout << "An obstacle was found" << std::endl;
                //If cell is '_', set to ' '
                if (maze.at(i).at(j) == '_') {
                    maze.at(i).at(j) = ' ';
                }
                //If cell is set 'x', set to ' ' and set surrounding cells to 'x'
                else if (maze.at(i).at(j) == 'x') {
                    //Set obstacle cell to ' ' 
                    maze.at(i).at(j) = ' ';
                    //Right neighbor
                    if (j + 1 < z_length) {
                        //If cell is '_', set to 'x'
                        if (maze.at(i).at(j + 1) == '_') {
                            maze.at(i).at(j + 1) = 'x';
                        }
                    }
                    //Left neighbor
                    if (j - 1 > 0) {
                        //If cell is '_', set to 'x'
                        if (maze.at(i).at(j - 1) == '_') {
                            maze.at(i).at(j - 1) = 'x';
                        }
                    }
                    //Up neighbor
                    if (i - 1 > 0) {
                        //If cell is '_', set to 'x'
                        if (maze.at(i - 1).at(j) == '_') {
                            maze.at(i - 1).at(j) = 'x';
                        }
                    }
                    //Down neighbor
                    if (i + 1 < x_length) {
                        //If cell is '_', set to 'x'
                        if (maze.at(i + 1).at(j) == '_') {
                            maze.at(i + 1).at(j) = 'x';
                        }
                    }
                }
            }
        }
    }

    // //Block out obstacle area with ' '
    // for (int i = 0; i < x_length; i++) {
    //     for (int j = 0; j < z_length; j++) {
    //         //Clear obstacle area
    //         if (j >= obstStartZ - 1 && (j < obstStartZ + obstLength - 1)) {
    //          if ((i >= obstStartX - 1) && (i < obstStartX - 1 + obstLength)) {
    //             maze.at(i).at(j) = ' ';
    //         }
    //         }
    //         //Create border around obstacle
    //         //Bottom and top border
    //         if ((i == obstStartX - 2) || (i == obstStartX + obstLength - 1)) {
    //             if (j >= obstStartZ - 2 && (j < obstStartZ + obstLength)) {
    //                 maze.at(i).at(j) = 'x';
    //             }
    //         }
    //         //Left and right border
    //         else if ((i > obstStartX - 2) && (i < obstStartX + obstLength - 1)) {
    //             if ((j == obstStartZ - 2) || (j == obstStartZ + obstLength - 1)) {
    //                 maze.at(i).at(j) = 'x';
    //             }
    //         }
    //     }
    // }

    // Set starting point
    std::pair<int, int> startPoint = E1_setStartingPoint(maze);

    int startZ = startPoint.first;
    int startX = startPoint.second;

    //Set maze entrance
    E1_createEntrance(maze, startZ, startX);

    //Initialise path and add start point
    std::vector<std::pair<int, int>> path;
    path.push_back(std::make_pair(startZ, startX));

    // Carve paths through maze
    E1_carveMaze(maze, basePoint, startZ, startX, path);

    //Output "Maze generated successfully" 
    std::cout << "Maze generated successfully" << std::endl;

    return maze;
}
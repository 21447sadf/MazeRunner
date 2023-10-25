#include "Maze.h"
#include <random>
#include <thread>
#include <chrono>

//Default constructor
Maze::Maze() {
    //Initialise all class variables to zero - maze vector will have size of zero
    this->basePoint = mcpp::Coordinate(0, 0, 0); //Maze vertex
    this->xlength = 0;
    this->zlength = 0;
    this->mode = 0;
}

//Overloaded constructor
Maze::Maze(mcpp::Coordinate basePoint, unsigned int xlen, 
                                    unsigned int zlen,
                                    bool mode
                                    , std::vector<std::vector<char>> charMaze)
{
    //Set basePoint
    this->basePoint = basePoint;
    this->xlength = xlen;
    this->zlength = zlen;
    this->mode = mode;
    this->mazeOfCharacters = charMaze;
}

//Build maze
void Maze::buildMazeInMC(std::vector<std::vector<char>> mazeOfCharacters) { //DONE

    //TP to 10 units above basepoint:
    mc.setPlayerPosition(basePoint + mcpp::Coordinate(0, 10, 0));

    //Build maze in MC - print each set of 3 vertical blocks 
    //Set wall and air blocks
    mcpp::BlockType WALL(5, 4);
    mcpp::BlockType AIR(0);

    for (int x = 0; x < xlength; x++) {
        for (int z = 0; z < zlength; z++) {
            //If maze char is a wall
            if (mazeOfCharacters.at(x).at(z) == 'x') {
                //Set three MC blocks for wall
                mc.setBlocks(basePoint + mcpp::Coordinate(x, 0, z),
                             basePoint + mcpp::Coordinate(x, 2, z), WALL);
            }
            //Otherwise set three air blocks for path
            else if (mazeOfCharacters.at(x).at(z) == '.') {
                mc.setBlocks(basePoint + mcpp::Coordinate(x, 0, z), 
                            basePoint + mcpp::Coordinate(x, 2, z), AIR);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    //Print success message
    std::cout << "Success! Maze built in Minecraft" << std::endl;
}

//Function to store original heights of terrain area
void Maze::saveTerrain() { 
    //Save vector of original heights before Flatenning
    mcpp::Coordinate origLoc1 = basePoint;
    mcpp::Coordinate origLoc2(basePoint.x + xlength, basePoint.y, basePoint.z + zlength);
    this->heights = mc.getHeights(origLoc1, origLoc2);
}

void Maze::flattenTerrain() { //DONE - NEEDS TESTING
    //Terrain is flattened by individually flattening the column at each x by z blocks

    for (int x = 0; x < xlength; x++) {
        for (int z = 0; z < zlength; z++) {
            //Get terrain block
            mcpp::Coordinate ground(basePoint.x + x, heights[x][z], basePoint.z + z);
            mcpp::BlockType terrainBlock = mc.getBlock(ground);
            //If terrain block is below basePoint, fill terrain
            if (heights[x][z] < basePoint.y) {
                mc.setBlocks(mcpp::Coordinate(basePoint.x + x, heights[x][z], basePoint.z + z), 
                             mcpp::Coordinate(basePoint.x + x, basePoint.y, basePoint.z + z), terrainBlock);
            }
            //If terrain block is above basePoint, remove terrain
            else if (heights[x][z] > basePoint.y) {
                mc.setBlocks(mcpp::Coordinate(basePoint.x + x, basePoint.y, basePoint.z + z),
                             mcpp::Coordinate(basePoint.x + x, heights[x][z], basePoint.z + z), mcpp::Blocks::AIR);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for 50 milliseconds
        }
    }
}

//Function to restore terrain
void Maze::reverseTerrain() { 

//Get terrain block
    for (int i = 3; i >= 0; i--) {
        for (int x = 0; x < xlength; x++) {
            for (int z = 0; z < zlength; z++) {
                mc.setBlock(basePoint + mcpp::Coordinate(x, i, z), mcpp::Blocks::AIR);
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
        }
    }
    for (int x = 0; x < xlength; x++) {
        for (int z = 0; z < zlength; z++) {
            //Get terrain block
            mcpp::Coordinate ground(basePoint.x + x, basePoint.y - 1, basePoint.z + z); //BLOCKS NOT BEING READ CORRECTLY
            mcpp::BlockType terrainBlock = mc.getBlock(ground);
            //If current terrain is lower than previous, add blocks
            if (basePoint.y < heights[x][z]) {
                mc.setBlocks(mcpp::Coordinate(basePoint.x + x, basePoint.y, basePoint.z + z),
                             mcpp::Coordinate(basePoint.x + x, heights[x][z], basePoint.z + z), terrainBlock);
            }
            else if (basePoint.y == heights[x][z]) {
                mc.setBlock(mcpp::Coordinate(basePoint.x + x, basePoint.y, basePoint.z + z), terrainBlock);
            }
            //If current terrain is higher than previous, remove terrain
            else if (basePoint.y > heights[x][z]) {
                mc.setBlocks(mcpp::Coordinate(basePoint.x + x, heights[x][z] + 1, basePoint.z + z),
                             mcpp::Coordinate(basePoint.x + x, basePoint.y, basePoint.z + z), mcpp::Blocks::AIR);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Delay for 50 milliseconds
        }
    }
}

void Maze::printMazeInTerminal() {
    std::cout << "**Printing Maze**" << std::endl
              << "BasePoint: (" << std::to_string(basePoint.x) << ", " 
                                << std::to_string(basePoint.y) << ", " 
                                << std::to_string(basePoint.z) << ")" << std::endl
              << "Structure: " << std::endl;
    //Print generated maze
    for (int i = 0; i < xlength; i++) {
        for (int j = 0; j < zlength; j++) {
            std::cout << mazeOfCharacters.at(i).at(j);
        }
        std::cout << std::endl;
    }

    //Print End message
    std::cout << "**End Printing Maze**" << std::endl;
}

Maze::~Maze()
{
}
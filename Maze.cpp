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
}

void Maze::setMazeParameters(mcpp::Coordinate basePoint, int xlength, int zlength) {
    this->basePoint = basePoint;
    this->xlength = xlength;
    this->zlength = zlength;
}

//Build maze
void Maze::buildMazeInMC(std::vector<std::vector<char>> charMaze) { 
    std::cout << "Building maze..." << std::endl;

    //TP to 10 units above basepoint:
    mc.setPlayerPosition(basePoint + mcpp::Coordinate(0, 10, 0));

    //Save current terrain 
    saveTerrain();
    //Flatten terrain in MC
    flattenTerrain();

    //Build maze in MC - print each set of 3 vertical blocks 
    //Set wall and air blocks
    mcpp::BlockType WALL(5, 4);
    mcpp::BlockType AIR(0);

    for (int x = 0; x < xlength; x++) {
        for (int z = 0; z < zlength; z++) {
            //If maze char is a wall
            if (charMaze.at(x).at(z) == 'x') {
                //Set three MC blocks for wall
                mc.setBlocks(basePoint + mcpp::Coordinate(x, 0, z),
                             basePoint + mcpp::Coordinate(x, 2, z), WALL);
            }
            //Otherwise set three air blocks for path
            else if (charMaze.at(x).at(z) == '.') {
                mc.setBlocks(basePoint + mcpp::Coordinate(x, 0, z), 
                            basePoint + mcpp::Coordinate(x, 2, z), AIR);
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    //Print success message
    std::cout << "Success! Maze building complete." << std::endl;
}

//Function to store original heights of terrain area
void Maze::saveTerrain() { 
    //Save vector of original heights before Flatenning
    mcpp::Coordinate origLoc1 = basePoint;
    mcpp::Coordinate origLoc2(basePoint.x + xlength, basePoint.y, basePoint.z + zlength);
    this->heights = mc.getHeights(origLoc1, origLoc2);
}

void Maze::flattenTerrain() {
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

//Tells user it is reverting the maze area
std::cout << "Reverting maze area..." << std::endl; 

//Undo Maze Blocks
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

//Function to restore terrain
void Maze::E1_reverseMaze() { 

    mcpp::BlockType WALL(5, 4);
    mcpp::BlockType AIR(0);

    std::cout << "Reverting maze area..." << std::endl; 

//Reverse maze blocks
    for (int x = 0; x < xlength; x++) {
        for (int z = 0; z < zlength; z++) {
            //Get current height on maze 
            //This will be different throughout since maze is built on slopes
            int currHeight = mc.getHeight(basePoint.x + x, basePoint.z + z);

            //Check the block found at the current height and 2 blocks beneath for walls and revert to air
            for (int y = currHeight; y > currHeight - 3; y--) {
                if (mc.getBlock(mcpp::Coordinate(basePoint.x + x, y, basePoint.z + z)) == WALL) {
                    mc.setBlock(mcpp::Coordinate(basePoint.x + x, y, basePoint.z + z), AIR);
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
}

void Maze::E1_buildMazeInMC(std::vector<std::vector<char>> charMaze) { 
    std::cout << "Building maze..." << std::endl;

    //TP to 10 units above basepoint:
    mc.setPlayerPosition(basePoint + mcpp::Coordinate(0, 10, 0));

    //Build maze in MC - print each set of 3 vertical blocks 
    //Set wall and air blocks
    mcpp::BlockType WALL(5, 4);
    mcpp::BlockType AIR(0);

    for (int x = 0; x < xlength; x++) {
        for (int z = 0; z < zlength; z++) {
            //If maze char is a wall
            if (charMaze.at(x).at(z) == 'x') {
                //Get height of ground to build wall on
                int currHeight = mc.getHeight(basePoint.x + x, basePoint.z + z);
                //Set ACACIA walls only if blocks are air
                for (int i = 1; i <= 3; i++) {
                    //If block is air, set to wall
                    if (mc.getBlock(mcpp::Coordinate(basePoint.x + x, currHeight + i, basePoint.z + z)) == mcpp::Blocks::AIR) {
                        mc.setBlock(mcpp::Coordinate(basePoint.x + x, currHeight + i, basePoint.z + z), WALL);
                    }
                }
            }
            //Else if maze char is air
            else if (charMaze.at(x).at(z) == '.') {
                //If block has slope of 1, increase height
                int height = mc.getHeight(x, z);
                mc.setBlocks(mcpp::Coordinate(basePoint.x + x, height, basePoint.z + z), 
                            mcpp::Coordinate(basePoint.x + x, height + 2, basePoint.z + z), AIR);
            }
            //Otherwise if ' ' (obstacle), leave as is
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    //Print success message
    std::cout << "Success! Maze building complete." << std::endl;
}


Maze::~Maze()
{
}
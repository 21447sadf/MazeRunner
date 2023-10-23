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

//Set basePoint
void Maze::setBasePoint(mcpp::Coordinate user_basePoint) {
    this->basePoint = user_basePoint;
}

//Set xlength 
void Maze::setXLength(int user_xlength) {
    this->xlength = user_xlength;
}

//Set zlength
void Maze::setZLength(int user_zlength) {
    this->zlength = user_zlength;
}

//Set mode
void Maze::setMode(bool user_mode) {
    this->mode = user_mode;
}

//Set mazeOfCharacters
void Maze::setMazeOfCharacters(std::vector<std::vector<char>> maze) {
    this->mazeOfCharacters = maze;
}

//Build maze
void Maze::buildMazeInMC(std::vector<std::vector<char>> mazeOfCharacters) {
    //Set to flying mode

    //TP to 10 units above basepoint:
    mc.setPlayerPosition(basePoint + mcpp::Coordinate(0, 10, 0));

    //FLATTEN TERRAIN
    flattenTerrain(basePoint, xlength, zlength);

    //Build maze in MC - print each layer above the other
    //Set wall and air blocks
    mcpp::BlockType wall(5, 4);
    mcpp::BlockType air(0);

    mcpp::Coordinate currBlock = basePoint;
    for (int i = 0; i < 3; i++) {
        for (int x = 0; x < xlength; x++) {
            for (int z = 0; z < zlength; z++) {
                //If maze char is a wall
                if (mazeOfCharacters.at(x).at(z) == 'x') {
                    //Set MC block to wall
                    mc.setBlock(currBlock + mcpp::Coordinate(x, i, z), wall);
                }
                //Otherwise if maze char is an empty path
                else if (mazeOfCharacters.at(x).at(z) == '.') {
                    mc.setBlock(currBlock + mcpp::Coordinate(x, i, z), air);
                }
                // std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }

    //Print success message
    std::cout << "Success! Maze built in Minecraft" << std::endl;
}

void Maze::flattenTerrain (mcpp::Coordinate startPoint, int xLength, int zLength) {
    //Terrain is flattened by individually flattening the column at each x by z block:

    //Terrain coordinate
    mcpp::Coordinate terrain;

    //Height of terrain(y)
    int terrainHeight;

    //Air block
    mcpp::BlockType air(0);


    for (int i = 0; i < xLength; i++) {
        for (int j = 0; j < zLength; j++) {
            //Set coordinate for current terrain to check
            terrain = basePoint + mcpp::Coordinate(i, 0, j);
            
            //Get height of current terrain 
            terrainHeight = mc.getHeight(terrain.x, terrain.z);

            //Set ground coordinate on current terrain
            terrain.y = terrainHeight;

            //Ground block of terrain to level
            mcpp::BlockType groundBlock = mc.getBlock(terrain);
            //If terrain's height < maze height (basePoint.y)
            while (terrainHeight < startPoint.y) { //TRY startPoint.y - 1
                //Fill up to maze's height
                terrain = terrain + mcpp::Coordinate(0, 1, 0);
                mc.setBlock(terrain, groundBlock);
                ++terrainHeight;
            }
            //Or if terrain's height > maze height (basePoint.y)
            while (terrainHeight > startPoint.y) {
                terrain = terrain - mcpp::Coordinate(0, -1, 0);
                mc.setBlock(terrain, air);
                --terrainHeight;
            }
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
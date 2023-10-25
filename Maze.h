#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <mcpp/mcpp.h>

class Maze
{

public:
    //Default constructor
    Maze();

    //Overloaded constructor
    Maze(mcpp::Coordinate basePoint, unsigned int xlen, 
                                        unsigned int zlen,
                                        bool mode
                                        , std::vector<std::vector<char>> charMaze);
    //Set functions
    // void setBasePoint(mcpp::Coordinate user_basePoint);
    // void setXLength(int user_xlength);
    // void setZLength(int user_zlength);
    // void setMode(bool user_mode);
    // void setMazeOfCharacters(std::vector<std::vector<char>> maze);

    //build maze function
    void buildMazeInMC(std::vector<std::vector<char>> maze);

    void saveTerrain();

    //Flatten and store current terrain function
    void flattenTerrain ();

    //Function to undo maze in MC
    void reverseTerrain();

    // void reverseTerrain(std::vector<std::vector<mcpp::Coordinate>> mazeTerrain);

    //Print maze function
    void printMazeInTerminal();
    
    //Destructor 
    ~Maze();

private:
    /* data */
    mcpp::Coordinate basePoint; //Maze vertex
    mcpp::MinecraftConnection mc;
    int xlength;
    int zlength;
    std::vector<std::vector<std::vector<mcpp::BlockType>>> originalTerrain; // TESTING
    std::vector<std::vector<int>> heights;
    std::vector<std::vector<char>> mazeOfCharacters;
    //Set to normal mode (0) by default
    bool mode = 0;
};




#endif //ASSIGN_MAZE_H

#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <mcpp/mcpp.h>

class Maze
{

public:
    //Default constructor
    Maze();

    //Set maze parameters
    void setMazeParameters(mcpp::Coordinate basePoint, int xlength, int zlength);

    //build maze function
    void buildMazeInMC(std::vector<std::vector<char>> charMaze);

    void saveTerrain();

    //Flatten and store current terrain function
    void flattenTerrain ();

    //Function to undo maze in MC
    void reverseTerrain();

    //Functions for E1
    void E1_reverseMaze();
    void E1_buildMazeInMC(std::vector<std::vector<char>> charMaze);
    
    //Destructor 
    ~Maze();

private:
    /* data */
    mcpp::Coordinate basePoint; //Maze vertex
    mcpp::MinecraftConnection mc;
    int xlength;
    int zlength;
    std::vector<std::vector<int>> heights;
};




#endif //ASSIGN_MAZE_H

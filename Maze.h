#ifndef ASSIGN_MAZE_H
#define ASSIGN_MAZE_H

#include <vector>
#include <mcpp/mcpp.h>

class Maze
{

public:
    //Default constructor
    Maze(mcpp::Coordinate basePoint, unsigned int xlen, 
                                        unsigned int zlen,
                                        bool mode);
    
    //Destructor 
    ~Maze();

private:
    /* data */
    mcpp::Coordinate basePoint;
    mcpp::Coordinate startPoint;
    int xlength;
    int zlength;
    //Set to normal mode (0) by default
    bool mode = 0;

};




#endif //ASSIGN_MAZE_H

#ifndef ASSIGN3_AGENT_H
#define ASSIGN3_AGENT_H

#include <iostream>
#include <vector>
#include <mcpp/mcpp.h>

#define MOVE_XPLUS mcpp::Coordinate(1,0,0)
#define MOVE_XMINUS mcpp::Coordinate(-1,0,0)
#define MOVE_ZPLUS mcpp::Coordinate(0,0,1)
#define MOVE_ZMINUS mcpp::Coordinate(0,0,-1)

enum solveAlgorithm{
        RIGHT_HAND_FOLLOW,
        BREATH_FIRST_SEARCH,
};

enum AgentOrientation{
    X_PLUS,
    Z_PLUS,
    X_MINUS,
    Z_MINUS
};

class Agent
{

public:
    //Constructor gets player's current location
    Agent(mcpp::Coordinate startLoc);
    ~Agent();

    //Function to set player orientation
    void orientPlayer();

    // std::vector<bool> wallsAroundBlock(mcpp::Coordinate &location);
    // std::vector<mcpp::Coordinate> Agent::wallsAroundBlock(mcpp::Coordinate location);

   AgentOrientation findForwardDirection(mcpp::Coordinate currloc);

    mcpp::Coordinate moveForward(mcpp::Coordinate loc);

    void updateRightWall(mcpp::Coordinate loc);

    std::vector<mcpp::Coordinate> findPath();

private:
    /* data */
    mcpp::MinecraftConnection mc;
    mcpp::Coordinate playerLoc;
    std::vector<mcpp::Coordinate> path;
    mcpp::Coordinate rightWall;

};



#endif //ASSIGN3_AGENT_H
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

    void turnRight(AgentOrientation &currDirection);
    mcpp::Coordinate advanceForward(mcpp::Coordinate currBlock, AgentOrientation currDirection);
    bool isWallInFront(mcpp::Coordinate currBlock, AgentOrientation orientation);
    bool isWallToRight(mcpp::Coordinate currBlock, AgentOrientation orientation);
    bool endReached(mcpp::Coordinate currBlock);

    void showEscapeRoute();

private:
    /* data */
    mcpp::MinecraftConnection mc;
    mcpp::Coordinate playerLoc;
    AgentOrientation agentdirection;

};



#endif //ASSIGN3_AGENT_H
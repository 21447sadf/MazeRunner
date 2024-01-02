#ifndef ASSIGN3_AGENT_H
#define ASSIGN3_AGENT_H

#include <iostream>
#include <vector>
#include <mcpp/mcpp.h>
#include <queue>


#define MOVE_XPLUS mcpp::Coordinate(1,0,0)
#define MOVE_XMINUS mcpp::Coordinate(-1,0,0)
#define MOVE_ZPLUS mcpp::Coordinate(0,0,1)
#define MOVE_ZMINUS mcpp::Coordinate(0,0,-1)

enum solveAlgorithm{
        RIGHT_HAND_FOLLOW,
        BREADTH_FIRST_SEARCH,
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
    Agent(mcpp::Coordinate startLoc, bool mode);
    ~Agent();

    //Function to set player orientation
    void orientPlayer();
    // Vector to store visited blocks during BFS
    //std::vector<BlockInfo> visitedBlocks;
    std::vector<mcpp::Coordinate> path; // added vector to store the path to print shortest path
    void turnRight(AgentOrientation &currDirection);
    mcpp::Coordinate advanceForward(mcpp::Coordinate currBlock, AgentOrientation currDirection);
    bool isWallInFront(mcpp::Coordinate currBlock, AgentOrientation orientation);
    bool isWallToRight(mcpp::Coordinate currBlock, AgentOrientation orientation);
    bool endReached(mcpp::Coordinate currBlock);
    void WallFollow();
    // function that finds shortest path
    int shortestPath();
    void doRightHandFollow();
    void showEscapeRoute(std::string algorithm);
    // void shortestPathToExit(const mcpp::Coordinate& exitLoc);
    //void shortestPath(const mcpp::Coordinate);
     // BlockInfo struct for BFS
    // struct BlockInfo
    // {
    //     mcpp::Coordinate coordinate; // Block coordinate
    //     int distance;                // Stores distance from the start block
    //     mcpp::Coordinate previous;   // Reference to the previous block in the path
    // };
    private:
    /* data */
    mcpp::MinecraftConnection mc;
    mcpp::Coordinate playerLoc;
    AgentOrientation agentdirection;
    bool mode;

    
};



#endif //ASSIGN3_AGENT_H
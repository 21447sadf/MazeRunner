#include "Agent.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mcpp/mcpp.h>

Agent::Agent(mcpp::Coordinate startLoc)
{
    this->playerLoc = startLoc;
    this->playerLoc.x = startLoc.x;
    this->playerLoc.y = startLoc.y;
    this->playerLoc.z = startLoc.z;
    mc.setPlayerPosition(this->playerLoc);
    
}

void Agent::orientPlayer() { 

    //Coordinates to check around player
    mcpp::Coordinate X_PLUS = playerLoc + MOVE_XPLUS;
    mcpp::Coordinate X_MINUS = playerLoc + MOVE_XMINUS;
    mcpp::Coordinate Z_PLUS = playerLoc + MOVE_ZPLUS;
    mcpp::Coordinate Z_MINUS = playerLoc + MOVE_ZMINUS;

    mcpp::Coordinate directions[4] = {X_PLUS, Z_MINUS, X_MINUS, Z_PLUS};

    //Set player to initially face +x direction
    mc.doCommand("tp @s " + std::to_string(playerLoc.x) + " " + std::to_string(playerLoc.y) + " " + std::to_string(playerLoc.z)
                  + " facing " + std::to_string(X_PLUS.x) + " " + std::to_string(X_PLUS.y) + " " + std::to_string(X_PLUS.z));

    //Set string command for wall at X+1: face block at Z - 1
    std::string X_PLUS_COMMAND = "teleport @s " + std::to_string(playerLoc.x) 
                                           + " " + std::to_string(playerLoc.y) 
                                           + " " + std::to_string(playerLoc.z) + " facing"
                                           + " " + std::to_string(Z_MINUS.x)
                                           + " " + std::to_string(Z_MINUS.y)
                                           + " " + std::to_string(Z_MINUS.z);

    //Set string command for wall at X-1: face block at Z + 1
    std::string X_MINUS_COMMAND = "teleport @s " + std::to_string(playerLoc.x)  //WORKS
                                            + " " + std::to_string(playerLoc.y) 
                                            + " " + std::to_string(playerLoc.z) + " facing"
                                            + " " + std::to_string(Z_PLUS.x)
                                            + " " + std::to_string(Z_PLUS.y)
                                            + " " + std::to_string(Z_PLUS.z);

    //Set string command for wall at Z+1: face block at X + 1
    std::string Z_PLUS_COMMAND = "teleport @s " + std::to_string(playerLoc.x) //WORKS
                                            + " " + std::to_string(playerLoc.y) 
                                            + " " + std::to_string(playerLoc.z) + " facing"
                                            + " " + std::to_string(X_PLUS.x)
                                            + " " + std::to_string(X_PLUS.y)
                                            + " " + std::to_string(X_PLUS.z);

    //Set string command for wall at Z-1: face block at X - 1
    std::string Z_MINUS_COMMAND = "teleport @s " + std::to_string(playerLoc.x) //WORKS
                                      + " " + std::to_string(playerLoc.y) + " " 
                                            + std::to_string(playerLoc.z) + " facing"
                                            + " " + std::to_string(X_MINUS.x)
                                            + " " + std::to_string(X_MINUS.y)
                                            + " " + std::to_string(X_MINUS.z);

    std::string commands[4] = {X_PLUS_COMMAND, Z_MINUS_COMMAND, X_MINUS_COMMAND, Z_PLUS_COMMAND};


    //Set air block type to compare with
    mcpp::BlockType air(0);

    int i = 0;
    mcpp::Coordinate checkDir = directions[i];
    std::string command = commands[i];

    while (!(mc.getBlock(checkDir) == air)) {
        
    //If wall block is in X+1 Position:
    if (!(mc.getBlock(checkDir) == air)) {
        mc.doCommand(command);
        rightWall = checkDir; //NEEDS TESTING
        std::cout << i << " " << command << std::endl;
    } 
        ++i;
        checkDir = directions[i];
        command = commands[i];
    }
}

// std::vector<bool> Agent::wallsAroundBlock(mcpp::Coordinate &location) { //MIGHT CHANGE TO FUNCTION TO CHECK FOR DEAD ENDS
//     std::vector<bool> walls;

//     //Set air block type to compare with
//     mcpp::BlockType air(0);

//     //Coordinates to check around player
//     mcpp::Coordinate X_PLUS = location + MOVE_XPLUS;
//     mcpp::Coordinate X_MINUS = location + MOVE_XMINUS;
//     mcpp::Coordinate Z_PLUS = location + MOVE_ZPLUS;
//     mcpp::Coordinate Z_MINUS = location + MOVE_ZMINUS;

//     //Set and add bool for block at X+1 to vector
//     bool x_plus_block = (!(mc.getBlock(X_PLUS) == air)) ? (true):(false);
//     walls.push_back(x_plus_block);

//     //Set and add bool for block at X-1 to vector
//     bool x_minus_block = (!(mc.getBlock(X_MINUS) == air)) ? (true):(false);
//     walls.push_back(x_minus_block);

//     //Set and add bool for block at Z+1 to vector
//     bool z_plus_block = (!(mc.getBlock(Z_PLUS) == air)) ? (true):(false);
//     walls.push_back(z_plus_block);

//     //Set and add bool for block at Z-1 to vector
//     bool z_minus_block = (!(mc.getBlock(Z_MINUS) == air)) ? (true):(false);
//     walls.push_back(z_minus_block);

//     return walls;
// }

AgentOrientation Agent::findForwardDirection(mcpp::Coordinate currloc){
    mcpp::BlockType air(0);
    AgentOrientation forward = X_PLUS;

    //Coordinates to check around player
    mcpp::Coordinate x_plus = playerLoc + MOVE_XPLUS;
    mcpp::Coordinate x_minus = playerLoc + MOVE_XMINUS;
    mcpp::Coordinate z_plus = playerLoc + MOVE_ZPLUS;
    mcpp::Coordinate z_minus = playerLoc + MOVE_ZMINUS;

    // ORDER: X_PLUS, Z_MINUS, X_MINUS, Z_PLUS

    if (mc.getBlock(x_plus) == air) {
        forward = X_PLUS;
        std::cout << "Next block is in x+1" << std::endl;
    }
    else if (mc.getBlock(z_minus) == air) {
        forward = Z_MINUS;
    }
    else if (mc.getBlock(x_minus) == air) {
        forward = X_MINUS;
    }
    else if (mc.getBlock(z_plus) == air) {
        forward = Z_PLUS;
    }
    return forward;
}

mcpp::Coordinate Agent::moveForward(mcpp::Coordinate loc) {
    mcpp::Coordinate nextBlock = loc;
    // ORDER: X_PLUS, Z_MINUS, X_MINUS, Z_PLUS
    if (findForwardDirection(loc) == X_PLUS) {
        nextBlock = loc + MOVE_XPLUS;
    }
    else if (findForwardDirection(loc) == Z_MINUS) {
        nextBlock = loc + MOVE_ZMINUS;
    }
    else if (findForwardDirection(loc) == X_MINUS) {
        nextBlock = loc + MOVE_XMINUS;
    }
    else if (findForwardDirection(loc) == Z_PLUS) {
        nextBlock = loc + MOVE_ZPLUS;
    }

    return nextBlock;
}

void Agent::updateRightWall(mcpp::Coordinate in_loc) {
    // ORDER: X_PLUS, Z_MINUS, X_MINUS, Z_PLUS
    if (findForwardDirection(in_loc) == X_PLUS) {
        rightWall = rightWall + MOVE_XPLUS;
    }
    else if (findForwardDirection(in_loc) == Z_MINUS) {
        rightWall = rightWall + MOVE_ZMINUS;
    }
    else if (findForwardDirection(in_loc) == X_MINUS) {
        rightWall = rightWall + MOVE_XMINUS;
    }
    else if (findForwardDirection(in_loc) == Z_PLUS) {
        rightWall = rightWall + MOVE_ZPLUS;
    }
}

std::vector<mcpp::Coordinate> Agent::findPath() {
    //Initialise path to return
    std::vector<mcpp::Coordinate> escapeRoute;

    //Orient player
    orientPlayer();

    //Loop variable 
    bool entranceNotFound = true;

    //Current block on route
    mcpp::Coordinate currBlock = playerLoc;
    
    mcpp::BlockType air(0);
    mcpp::BlockType LIME_CARPET(171, 5);

    //Search starts at the right wall set in orientPlayer()
    // Each time a new path block is found, it is added to escapeRoute and rightWall is changed. 


    //While there are wall blocks in any direction around the player
    while (entranceNotFound) {
        mcpp::Coordinate forwardBlock = moveForward(currBlock);
        if (mc.getBlock(rightWall) == air) {
            // turn 90 clockwise (i.e. turn right)
            //advance forward
            currBlock = rightWall;
        }
        else if (!(mc.getBlock(rightWall) == air) && (mc.getBlock(forwardBlock) == air)) { //WORKS
            //advance forward
            currBlock = moveForward(currBlock);
        }
        else if (!(mc.getBlock(rightWall) == air) && !(mc.getBlock(forwardBlock) == air)) { //CONDITION CORRECTLY IDENTIFIED BUT TURN LEFT INCORRECT
            //turn 90 anti-clockwise (left)
            //Determine which direction forwardBlock is on
            std::cout << " CURRENT: " << std::to_string(currBlock.x) << " " << std::to_string(currBlock.y) << " " << std::to_string(currBlock.z) << std::endl;
            currBlock = moveForward(currBlock); //CURRBLOCK NOT BEING UPDATED CORRECTLY
            std::cout << "TURN LEFT" << std::to_string(currBlock.x) << " " << std::to_string(currBlock.y) << " " << std::to_string(currBlock.z) << std::endl;
        }
        updateRightWall(currBlock);
        std::cout << "NEW_RIGHT WALL:" << std::to_string(rightWall.x) << " " << std::to_string(rightWall.y) << " " << std::to_string(rightWall.z) << std::endl;
        //Add currBlock to path
        escapeRoute.push_back(currBlock);
        
        //Set lime carpet block
        mc.setBlock(currBlock, LIME_CARPET);

        //Time delay of 1 sec
        std::this_thread::sleep_for(std::chrono::seconds(1));

        mc.setBlock(currBlock, air);

        //tp @s location ~135 0 for 90 clockwise
    }

    return escapeRoute;
}

Agent::~Agent()
{

}
//test 
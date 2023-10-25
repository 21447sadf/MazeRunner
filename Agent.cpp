#include "Agent.h"
#include <iostream>
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
    playerLoc = mc.getPlayerPosition();

    //Coordinates to check around player
    mcpp::Coordinate x_plus = playerLoc + MOVE_XPLUS;
    mcpp::Coordinate x_minus = playerLoc + MOVE_XMINUS;
    mcpp::Coordinate z_plus = playerLoc + MOVE_ZPLUS;
    mcpp::Coordinate z_minus = playerLoc + MOVE_ZMINUS;

    mcpp::Coordinate directions[4] = {x_plus, z_plus, x_minus, z_minus};

    //Set player to initially face +x direction
    mc.doCommand("tp @s " + std::to_string(playerLoc.x) + " " + std::to_string(playerLoc.y) + " " + std::to_string(playerLoc.z)
                  + " facing " + std::to_string(x_plus.x) + " " + std::to_string(x_plus.y) + " " + std::to_string(x_plus.z));

    //Set string command for wall at X+1: face block at Z - 1
    std::string X_PLUS_COMMAND = "teleport @s " + std::to_string(playerLoc.x) 
                                           + " " + std::to_string(playerLoc.y) 
                                           + " " + std::to_string(playerLoc.z) + " facing"
                                           + " " + std::to_string(z_minus.x)
                                           + " " + std::to_string(z_minus.y)
                                           + " " + std::to_string(z_minus.z);

    //Set string command for wall at X-1: face block at Z + 1
    std::string X_MINUS_COMMAND = "teleport @s " + std::to_string(playerLoc.x)  //WORKS
                                            + " " + std::to_string(playerLoc.y) 
                                            + " " + std::to_string(playerLoc.z) + " facing"
                                            + " " + std::to_string(z_plus.x)
                                            + " " + std::to_string(z_plus.y)
                                            + " " + std::to_string(z_plus.z);

    //Set string command for wall at Z+1: face block at X + 1
    std::string Z_PLUS_COMMAND = "teleport @s " + std::to_string(playerLoc.x) //WORKS
                                            + " " + std::to_string(playerLoc.y) 
                                            + " " + std::to_string(playerLoc.z) + " facing"
                                            + " " + std::to_string(x_plus.x)
                                            + " " + std::to_string(x_plus.y)
                                            + " " + std::to_string(x_plus.z);

    //Set string command for wall at Z-1: face block at X - 1
    std::string Z_MINUS_COMMAND = "teleport @s " + std::to_string(playerLoc.x) //WORKS
                                      + " " + std::to_string(playerLoc.y) + " " 
                                            + std::to_string(playerLoc.z) + " facing"
                                            + " " + std::to_string(x_minus.x)
                                            + " " + std::to_string(x_minus.y)
                                            + " " + std::to_string(x_minus.z);

    std::string commands[4] = {X_PLUS_COMMAND, Z_PLUS_COMMAND, X_MINUS_COMMAND, Z_MINUS_COMMAND};
    // AgentOrientation orientations[4] = {X_PLUS, Z_PLUS, X_MINUS, Z_MINUS};


    //Set air block type to compare with
    mcpp::BlockType air(0);
    AgentOrientation startOrientation = X_PLUS;

    int i = 0;
    mcpp::Coordinate checkDir = directions[i];
    std::string command = commands[i];


    for (i = 0; i < 4; i++) {
        checkDir = directions[i];
        command = commands[i];
        if (!(mc.getBlock(checkDir) == air)) {
            mc.doCommand(command);
        }
        ++i;
        turnRight(startOrientation);
        std::cout << startOrientation << std::endl;
    }
}

//Function to turn right 
void Agent::turnRight(AgentOrientation &currDirection) {
    currDirection = static_cast<AgentOrientation>((currDirection + 1) % 4);
}

mcpp::Coordinate Agent::advanceForward(mcpp::Coordinate currBlock, AgentOrientation currDirection) {
    mcpp::Coordinate nextBlock;
    if (currDirection == X_PLUS) {
        nextBlock = currBlock + MOVE_XPLUS;
    }
    else if (currDirection == Z_PLUS) {
        nextBlock = currBlock + MOVE_ZPLUS;
    }
    else if (currDirection == X_MINUS) {
        nextBlock = currBlock + MOVE_XMINUS;
    }
    else if (currDirection == Z_MINUS) {
        nextBlock = currBlock + MOVE_ZMINUS;
    }
    return nextBlock;
}

//Function to check if there is wall in front
bool Agent::isWallInFront(mcpp::Coordinate currBlock, AgentOrientation orientation) {
    mcpp::BlockType air(0);
    bool isWall = true;
    //If orientation is X_PLUS
    if (orientation == X_PLUS) {
        //Check for wall on X + 1
        isWall = (mc.getBlock(currBlock + MOVE_XPLUS) == mcpp::Blocks::ACACIA_WOOD_PLANK);
    }
    else if (orientation == Z_PLUS) {
        isWall = (mc.getBlock(currBlock + MOVE_ZPLUS) == mcpp::Blocks::ACACIA_WOOD_PLANK);
    }
    else if (orientation == X_MINUS) {
        isWall = (mc.getBlock(currBlock + MOVE_XMINUS) == mcpp::Blocks::ACACIA_WOOD_PLANK);
    }
    else if (orientation == Z_MINUS) {
        isWall = (mc.getBlock(currBlock + MOVE_ZMINUS) == mcpp::Blocks::ACACIA_WOOD_PLANK);
    }
    return isWall;
}

//Function to check if there is wall in front
bool Agent::isWallToRight(mcpp::Coordinate currBlock, AgentOrientation orientation) {
    mcpp::BlockType air(0);
    bool isWall = true;
    //If orientation is X_PLUS
    if (orientation == X_PLUS) {
        //Check for wall on Z + 1
        isWall = (!(mc.getBlock(currBlock + MOVE_ZPLUS) == air));
    }
    else if (orientation == Z_PLUS) {
        isWall = (!(mc.getBlock(currBlock + MOVE_XMINUS) == air));
    }
    else if (orientation == X_MINUS) {
        isWall = (!(mc.getBlock(currBlock + MOVE_ZMINUS) == air));
    }
    else if (orientation == Z_MINUS) {
        isWall = (!(mc.getBlock(currBlock + MOVE_XPLUS) == air));
    }
    return isWall;
}

//Function to check if entrance of maze has been reached
bool Agent::endReached(mcpp::Coordinate currBlock) {
    bool mazeSolved = true;
    mcpp::BlockType air(0);
    //Check if blocks in all 4 orientations are air
    //If walls aren't ACACIA_WOOD_PLANK, mazeSolved is false
    // X + 1
    if (mc.getBlock(currBlock + MOVE_XPLUS) == mcpp::Blocks::ACACIA_WOOD_PLANK) {
        mazeSolved = false;
    }
    else if (mc.getBlock(currBlock + MOVE_ZPLUS) == mcpp::Blocks::ACACIA_WOOD_PLANK) {
        mazeSolved = false;
    }
    else if (mc.getBlock(currBlock + MOVE_XMINUS) == mcpp::Blocks::ACACIA_WOOD_PLANK) {
        mazeSolved = false;
    }
    else if (mc.getBlock(currBlock + MOVE_ZMINUS) == mcpp::Blocks::ACACIA_WOOD_PLANK) {
        mazeSolved = false;
    }
    return mazeSolved;
}

void Agent::showEscapeRoute() {

    //Orient player
    orientPlayer();

    //Loop variable 
    bool mazeEscaped = false;

    //Current block on route
    mcpp::Coordinate currBlock = playerLoc;
    
    mcpp::BlockType air(0);
    mcpp::BlockType LIME_CARPET(171, 5);

    //Search starts at the right wall set in orientPlayer()
    // Each time a new path block is found, it is added to escapeRoute and rightWall is changed. 

    //Variable to store Step No. - for printing in loop
    int stepNumber = 0;

    //While there are wall blocks in any direction around the player
    while (!mazeEscaped) {
        //If there is no wall to the right
        if (!isWallToRight(currBlock, agentdirection)) {
            //turn right
            turnRight(agentdirection);
        }
        //If no wall in front (empty path)
        if (!isWallInFront(currBlock, agentdirection)) {
            //Move forward
            currBlock = advanceForward(currBlock, agentdirection);
            //Set lime carpet block
            mc.setBlock(currBlock, LIME_CARPET);
            //Print current block step
            std::cout << "Step[" << stepNumber + 1 << "]: (" << std::to_string(currBlock.x) << ", "
                                                             << std::to_string(currBlock.y) << ", "
                                                             << std::to_string(currBlock.z) << ")" << std::endl;
            //Time delay of 1 sec than change to air
            std::this_thread::sleep_for(std::chrono::seconds(2));
            mc.setBlock(currBlock, air);
        }
        //Otherwise, a wall exists and we turn left
        else {
            //Turn left = Turn right three times
            turnRight(agentdirection);
            turnRight(agentdirection);
            turnRight(agentdirection);
        }
        //Check if maze is solved
        mazeEscaped = endReached(currBlock);
        ++stepNumber;
    }

}

Agent::~Agent()
{

}
//test 
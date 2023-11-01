#include "Agent.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <mcpp/mcpp.h>
#include <queue>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <thread>

Agent::Agent(mcpp::Coordinate startLoc, bool mode)
{
    this->playerLoc = startLoc;
    this->playerLoc.x = startLoc.x;
    this->playerLoc.y = startLoc.y;
    this->playerLoc.z = startLoc.z;
    mc.setPlayerPosition(this->playerLoc);
    this->mode = mode;
}

void Agent::orientPlayer()
{
    playerLoc = mc.getPlayerPosition();

    // Coordinates to check around player
    mcpp::Coordinate x_plus = playerLoc + MOVE_XPLUS;
    mcpp::Coordinate x_minus = playerLoc + MOVE_XMINUS;
    mcpp::Coordinate z_plus = playerLoc + MOVE_ZPLUS;
    mcpp::Coordinate z_minus = playerLoc + MOVE_ZMINUS;

    mcpp::Coordinate directions[4] = {x_plus, z_plus, x_minus, z_minus};

    // Set player to initially face +x direction
    mc.doCommand("tp @s " + std::to_string(playerLoc.x) + " " + std::to_string(playerLoc.y) + " " + std::to_string(playerLoc.z) + " facing " + std::to_string(x_plus.x) + " " + std::to_string(x_plus.y) + " " + std::to_string(x_plus.z));

    // Set string command for wall at X+1: face block at Z - 1
    std::string X_PLUS_COMMAND = "teleport @s " + std::to_string(playerLoc.x) + " " + std::to_string(playerLoc.y) + " " + std::to_string(playerLoc.z) + " facing" + " " + std::to_string(z_minus.x) + " " + std::to_string(z_minus.y) + " " + std::to_string(z_minus.z);

    // Set string command for wall at X-1: face block at Z + 1
    std::string X_MINUS_COMMAND = "teleport @s " + std::to_string(playerLoc.x) // WORKS
                                  + " " + std::to_string(playerLoc.y) + " " + std::to_string(playerLoc.z) + " facing" + " " + std::to_string(z_plus.x) + " " + std::to_string(z_plus.y) + " " + std::to_string(z_plus.z);

    // Set string command for wall at Z+1: face block at X + 1
    std::string Z_PLUS_COMMAND = "teleport @s " + std::to_string(playerLoc.x) // WORKS
                                 + " " + std::to_string(playerLoc.y) + " " + std::to_string(playerLoc.z) + " facing" + " " + std::to_string(x_plus.x) + " " + std::to_string(x_plus.y) + " " + std::to_string(x_plus.z);

    // Set string command for wall at Z-1: face block at X - 1
    std::string Z_MINUS_COMMAND = "teleport @s " + std::to_string(playerLoc.x) // WORKS
                                  + " " + std::to_string(playerLoc.y) + " " + std::to_string(playerLoc.z) + " facing" + " " + std::to_string(x_minus.x) + " " + std::to_string(x_minus.y) + " " + std::to_string(x_minus.z);

    std::string commands[4] = {X_PLUS_COMMAND, Z_PLUS_COMMAND, X_MINUS_COMMAND, Z_MINUS_COMMAND};
    // AgentOrientation orientations[4] = {X_PLUS, Z_PLUS, X_MINUS, Z_MINUS};

    // Set air block type to compare with
    mcpp::BlockType air(0);
    AgentOrientation startOrientation = X_PLUS;

    int i = 0;
    mcpp::Coordinate checkDir = directions[i];
    std::string command = commands[i];

    if (mode == 0)
    {
        for (i = 0; i < 4; i++)
        {
            checkDir = directions[i];
            command = commands[i];
            if (!(mc.getBlock(checkDir) == air))
            {
                mc.doCommand(command);
            }
            ++i;
            turnRight(startOrientation);
        }
    }
    else if (mode == 1)
    {
        // Face negative z axis:
        mc.doCommand(X_PLUS_COMMAND);
        startOrientation = Z_MINUS;
        while (!isWallToRight(playerLoc, startOrientation))
        {
            turnRight(startOrientation);
        }
    }
}

// Function to turn right
void Agent::turnRight(AgentOrientation &currDirection)
{
    currDirection = static_cast<AgentOrientation>((currDirection + 1) % 4);
}

mcpp::Coordinate Agent::advanceForward(mcpp::Coordinate currBlock, AgentOrientation currDirection)
{
    mcpp::Coordinate nextBlock;
    if (currDirection == X_PLUS)
    {
        nextBlock = currBlock + MOVE_XPLUS;
    }
    else if (currDirection == Z_PLUS)
    {
        nextBlock = currBlock + MOVE_ZPLUS;
    }
    else if (currDirection == X_MINUS)
    {
        nextBlock = currBlock + MOVE_XMINUS;
    }
    else if (currDirection == Z_MINUS)
    {
        nextBlock = currBlock + MOVE_ZMINUS;
    }
    return nextBlock;
}
// Function to check if there is wall in front
//  Helper function to check if there is a wall in front of the player
bool Agent::isWallInFront(mcpp::Coordinate currBlock, AgentOrientation orientation)
{
    mcpp::BlockType air(0);
    bool isWall = true;
    if (orientation == X_PLUS)
    {
        isWall = (mc.getBlock(currBlock + MOVE_XPLUS) == mcpp::Blocks::ACACIA_WOOD_PLANK);
    }
    else if (orientation == Z_PLUS)
    {
        isWall = (mc.getBlock(currBlock + MOVE_ZPLUS) == mcpp::Blocks::ACACIA_WOOD_PLANK);
    }
    else if (orientation == X_MINUS)
    {
        isWall = (mc.getBlock(currBlock + MOVE_XMINUS) == mcpp::Blocks::ACACIA_WOOD_PLANK);
    }
    else if (orientation == Z_MINUS)
    {
        isWall = (mc.getBlock(currBlock + MOVE_ZMINUS) == mcpp::Blocks::ACACIA_WOOD_PLANK);
    }
    return isWall;
}

// Helper function to check if there is a wall to the right of the player
bool Agent::isWallToRight(mcpp::Coordinate currBlock, AgentOrientation orientation)
{
    mcpp::BlockType air(0);
    bool isWall = true;
    if (orientation == X_PLUS)
    {
        isWall = !(mc.getBlock(currBlock + MOVE_ZPLUS) == air);
    }
    else if (orientation == Z_PLUS)
    {
        isWall = !(mc.getBlock(currBlock + MOVE_XMINUS) == air);
    }
    else if (orientation == X_MINUS)
    {
        isWall = !(mc.getBlock(currBlock + MOVE_ZMINUS) == air);
    }
    else if (orientation == Z_MINUS)
    {
        isWall = !(mc.getBlock(currBlock + MOVE_XPLUS) == air);
    }
    return isWall;
}

// Helper function to check if the entrance of the maze has been reached
bool Agent::endReached(mcpp::Coordinate currBlock)
{
    bool mazeSolved = true;
    mcpp::BlockType air(0);
    if (mc.getBlock(currBlock + MOVE_XPLUS) == mcpp::Blocks::ACACIA_WOOD_PLANK)
    {
        mazeSolved = false;
    }
    else if (mc.getBlock(currBlock + MOVE_ZPLUS) == mcpp::Blocks::ACACIA_WOOD_PLANK)
    {
        mazeSolved = false;
    }
    else if (mc.getBlock(currBlock + MOVE_XMINUS) == mcpp::Blocks::ACACIA_WOOD_PLANK)
    {
        mazeSolved = false;
    }
    else if (mc.getBlock(currBlock + MOVE_ZMINUS) == mcpp::Blocks::ACACIA_WOOD_PLANK)
    {
        mazeSolved = false;
    }
    return mazeSolved;
}

void Agent::WallFollow()
{

    // //Orient player
    orientPlayer();
    // Loop variable
    bool mazeEscaped = false;

    // Current block on route
    mcpp::Coordinate currBlock = playerLoc;

    mcpp::BlockType air(0);
    mcpp::BlockType LIME_CARPET(171, 5);

    // Search starts at the right wall set in orientPlayer()
    //  Each time a new path block is found, it is added to escapeRoute and rightWall is changed.

    // Variable to store Step No. - for printing in loop
    int stepNumber = 0;

    // While there are wall blocks in any direction around the player
    while (!mazeEscaped)
    {
        // If there is no wall to the right
        if (!isWallToRight(currBlock, agentdirection))
        {
            // turn right
            turnRight(agentdirection);
        }
        // If no wall in front (empty path)
        if (!isWallInFront(currBlock, agentdirection))
        {
            // Move forward
            currBlock = advanceForward(currBlock, agentdirection);
            // Set lime carpet block
            mc.setBlock(currBlock, LIME_CARPET);
            // Print current block step
            std::cout << "Step[" << stepNumber + 1 << "]: (" << std::to_string(currBlock.x) << ", "
                      << std::to_string(currBlock.y) << ", "
                      << std::to_string(currBlock.z) << ")" << std::endl;
            // Time delay of 1 sec than change to air
            std::this_thread::sleep_for(std::chrono::seconds(2));
            mc.setBlock(currBlock, air);
        }
        // Otherwise, a wall exists and we turn left
        else
        {
            // Turn left = Turn right three times
            turnRight(agentdirection);
            turnRight(agentdirection);
            turnRight(agentdirection);
        }
        // Check if maze is solved
        mazeEscaped = endReached(currBlock);
        ++stepNumber;
    }
}
// BFS structure
//This information is essential for path reconstruction.
//  Extend the BlockInfo structure to include a reference to the previous block
struct BlockInfo
{
    mcpp::Coordinate coordinate; // Block coordinate
    int distance;                // Stores distance from the start block
    mcpp::Coordinate previous;   // Reference to the previous block in the path
};
// Updated shortestPath function
int Agent::shortestPath()
{
    // Orients the player
    orientPlayer();
    //We use a queue (std::queue) to explore neighboring blocks. BFS explores blocks level by level,
    // visiting all blocks at the current level before moving to the next level.
    // Create a queue for visited blocks
    std::queue<BlockInfo> q;

    // Create a vector for visited blocks to efficiently look up BlockInfo
    // Each BlockInfo object in the visitedBlocks vector stores information 
    //about a block that the agent has visited during the exploration.
    //This includes the block's coordinate, the distance from the starting block, and a reference to the previous block in the path. 
    //The reference to the previous block (previous field) is crucial for reconstructing the path,
    //as it allows the agent to trace its steps backward from the exit to the starting point.
    std::vector<BlockInfo> visitedBlocks;

    // Add the player's current location to the queue
    BlockInfo start = {playerLoc, 0, playerLoc};
    q.push(start);

    // Initialize the visited list
    visitedBlocks.push_back(start);
     // Define block types for 'air' and 'Lime Carpet'
    mcpp::BlockType air(0);
    mcpp::BlockType LIME_CARPET(171, 5);
     int stepNumber = 1; // Initialize the step number
      // Continue the process while there are blocks in the queue
      //Inside this loop, it dequeues a block, examines its neighbors, 
      //and enqueues unvisited neighboring blocks that are accessible
    while (!q.empty())
    {
        BlockInfo curr = q.front();

        // If the current location is the exit, stop and reconstruct the path
        if (endReached(curr.coordinate))
        {
            std::vector<mcpp::Coordinate> path;

            // Reconstruct the path by following the "previous" references
            //When the agent reaches the exit block and determines that it has found the shortest path, 
            // it enters a path reconstruction phase. During this phase, 
            //the code uses the visitedBlocks vector to backtrack from the exit block to the starting block by following the previous references. 
            //This process effectively reconstructs the sequence of blocks the agent traversed to reach the exit
            while (curr.coordinate.x != playerLoc.x || curr.coordinate.y != playerLoc.y || curr.coordinate.z != playerLoc.z)
            {
                path.push_back(curr.coordinate);
              
                // Adjust the brightness of the Lime Carpet (glow effect)
                // mc.setBlock(curr.coordinate, LIME_CARPET);
                // std::this_thread::sleep_for(std::chrono::seconds(2));
                // mc.setBlock(curr.coordinate, mcpp::Blocks::AIR);
               

                // Time delay of 1 sec
                std::this_thread::sleep_for(std::chrono::seconds(1));
                // Look up the BlockInfo associated with the previous coordinate
                for (const BlockInfo &block : visitedBlocks)
                {
                    if (block.coordinate.x == curr.previous.x && block.coordinate.y == curr.previous.y && block.coordinate.z == curr.previous.z)
                    {
                        curr = block;
                        break;
                    }
                }
            }

            // Add the player's starting location to the path
            path.push_back(playerLoc);
            // Why did it not
            // Reverse the path to get it from start to exit
            std::reverse(path.begin(), path.end());
            // Once the path is reconstructed, the code prints it out step by step,
            // indicating each block's coordinates
            // Print the path
            // TO DO print it in reverse 
            std::cout << "Shortest path:" << std::endl;
            for (const mcpp::Coordinate &coord : path)
            {
                 // Print each step with its number
                 std::cout << "Step[" << stepNumber << "] (" << coord.x << ", " << coord.y << ", " << coord.z << ")" << std::endl;
                stepNumber++; // Increment the step number
                 // Adjust the brightness of the Lime Carpet (glow effect)
                mc.setBlock(coord, LIME_CARPET);
                std::this_thread::sleep_for(std::chrono::seconds(2));
                mc.setBlock(coord, mcpp::Blocks::AIR);
            }

            return path.size() - 1; // The number of steps is the path size - 1
        }

        // Otherwise dequeue the front cell in the queue and enqueue its adjacent cell
        q.pop();
        //Inside the loop,
        // it iterates over the neighboring blocks (neighbor) in different directions (X_PLUS, Y_MINUS, etc.).
        // For each neighbor, it checks if it's an "air" block and hasn't been visited. 
        //If it meets these criteria, it enqueues the neighbor for future exploration. 
        //This loop explores all the neighbors at the current level before moving on to the next level of neighbors.
        for (int i = X_PLUS; i <= Z_MINUS; ++i)
        {
            mcpp::Coordinate neighbor = advanceForward(curr.coordinate, static_cast<AgentOrientation>(i));

            // If neighbor is an air block and not visited, enqueue it
            if ((mc.getBlock(neighbor) == mcpp::Blocks::AIR))
            {
                bool alreadyVisited = false;
                 // Check if the neighbor has already been visited
                for (const BlockInfo &block : visitedBlocks)
                {
                    if (block.coordinate == neighbor)
                    {
                        alreadyVisited = true;
                        break;
                    }
                }

                if (!alreadyVisited)
                {
                    // Create a new BlockInfo for the adjacent block
                    BlockInfo adjBlock = {neighbor, curr.distance + 1, curr.coordinate};
                    // Enqueue the adjacent block
                    q.push(adjBlock);
                    visitedBlocks.push_back(adjBlock);
                }
            }
        }
    }
      // If no path is found, return -1
    return -1;
}

void Agent::showEscapeRoute(std::string algorithm) {
    if (algorithm == "RIGHT_HAND_FOLLOW") {
        WallFollow();
    }
    else if (algorithm == "BREADTH_FIRST_SEARCH") {
        shortestPath();
        
    }
}


// adding a main
Agent::~Agent()
{
}
// test
#include <iostream>
#include <utility>
#include <cstring>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"
#include "readMaze.h"
#include "buildMaze.h"
#include "solveManually.h"

#include <limits>
#include "getUserInput.h"


#include "genMaze.h"


#define NORMAL_MODE 0
#define TESTING_MODE 1

enum States{
    ST_Main,
    ST_GenMaze, //Generate Maze menu - 1
    ST_GetMaze, //Dummy message  - 2
    ST_SolveMaze, //Solve maze menu - 3
    ST_Creators, //Team info - 4
    ST_Exit,      // Exit message - 5 
    ST_RandomMaze
};

int main(int numParams, char* arguments[]){

    bool mode = NORMAL_MODE;
    //read Mode
    for (int i = 1; i < numParams; i++) {
        if (std::strcmp(arguments[i], "-testMode") == 0) {
            mode = TESTING_MODE;
        }
    }

    mcpp::MinecraftConnection mc; 
    mc.doCommand("time set day"); 

    //Get player location
    mcpp::Coordinate playerLoc = mc.getPlayerPosition();

    //Agent, Maze and readMaze objects
    Agent player(playerLoc, mode);
    Maze maze;
    readMaze rm;

    bool mazeBuilt = false;
    bool mazeGenerated = false;
    bool solveMan = false;

    //Maze parameters
    std::vector<std::vector<char>> charMaze;
    mcpp::Coordinate basePoint;
    std::pair<int, int> mazeDimensions;

    States curState = ST_Main;
    int option;

    printStartText();
    
    //State machine for menu        
    while (curState != ST_Exit)
    {
        // Main Menu
        printMainMenu();
        std::cin >> option;

        // Generate Maze Menu
        if (option == 1) {
            curState = ST_GetMaze;
            printGenerateMazeMenu();
            std::cin >> option;
            if (option == 1) {
                // Do Read Maze from terminal
                rm.executeReadMaze();
                basePoint = mcpp::Coordinate(rm.getX(), rm.getY(), rm.getZ());
                mazeDimensions = std::make_pair(rm.getLength(), rm.getWidth());
                charMaze = rm.getEnvStructure();
                mazeGenerated = true;
            }
            else if (option == 2) {
                basePoint = getBasePoint();
                mazeDimensions = getMazeDimensions();
                charMaze = genMaze(mazeDimensions.first, mazeDimensions.second, mode);
                printMazeInTerminal(charMaze, basePoint.x, basePoint.y, basePoint.z);
                mazeGenerated = true;
            }
            else if (option == 3) {
                // Do Back (Return to Main Menu)
                curState = ST_Main;
            }
            else {
                std::cout << std::endl;
                std::cout << "Input Error: Enter a number between 1 and 3 ....";
                // Clear the error state of cin and ignore any remaining characters in the input buffer
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        // Build Maze 
        else if (option == 2) {
            //Do Build Maze in MineCraft
            // Maze generated but not built
            if (mazeGenerated && !mazeBuilt) {
                maze.setMazeParameters(basePoint, mazeDimensions.first, mazeDimensions.second);
                maze.buildMazeInMC(charMaze);
                // mazeGenerated = false;
                mazeBuilt = true;
                }
            // Maze generated and built
            else if (mazeGenerated && mazeBuilt) {
                maze.reverseTerrain();
                maze.setMazeParameters(basePoint, mazeDimensions.first, mazeDimensions.second);
                maze.buildMazeInMC(charMaze);
                // mazeGenerated = false;
                mazeBuilt = true;
            }
            else {
                std::cout << "Maze not defined! Generate maze before building." << std::endl;
            }
        }

        // Solve Maze Menu
        else if (option == 3) {
            curState = ST_SolveMaze;
            while (curState == ST_SolveMaze) {
            printSolveMazeMenu();
            std::cin >> option;
            if (option == 1) {
                if (mazeBuilt) {
                    // Do Solve Manually - NOTE: Doesnt work for random maze
                    executeSolveManually(basePoint.x, basePoint.y, basePoint.z, mazeDimensions.first, mazeDimensions.second, charMaze, mode);
                    solveMan = true;
                }
                else {
                    std::cout << "Build Maze before solving." << std::endl;
                }
            }
            else if (option == 2) {
                // Do Show Escape Route
                if (solveMan) {
                    player.showEscapeRoute();
                    solveMan = false;
                }
                else {
                    std::cout << "Initialize player using Solve Manually." << std::endl;
                }
            }
            else if (option == 3) {
                // Do Back (Return to Main Menu)
                curState = ST_Main;
            }
            else {
                std::cout << std::endl;
                std::cout << "Input Error: Enter a number between 1 and 3 ....";
                // Clear the error state of cin and ignore any remaining characters in the input buffer
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            } 
        }

        // Show Team Information
        else if (option == 4) {
            curState = ST_Creators;
            printTeamInfo();
        }

        // Exit
        else if (option == 5) {
            curState = ST_Exit;
        }

        // Input Error - if a value other than between 1 and 5 is inputted
        else {
            std::cout << std::endl;
            std::cout << "Input Error: Enter a number between 1 and 5 ....";
            std::cout << std::endl;
            curState = ST_Main;

            // Clear the error state of cin and ignore any remaining characters in the input buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    // Do Minecraft Reversal Here
    if (mazeBuilt) {
        maze.reverseTerrain();
    }

    // Print Exit Message
    printExitMassage();

    return EXIT_SUCCESS;

}
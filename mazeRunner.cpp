#include <iostream>
#include <utility>
#include <cstring>
#include <limits>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "getUserInput.h"

#include "Maze.h"
#include "Agent.h"
#include "readMaze.h"
#include "solveManually.h"
#include "genMaze.h"
#include "genMaze_E1.h"



#define NORMAL_MODE 0
#define TESTING_MODE 1
#define E1_MODE 2       //Build without flattening
#define E2_MODE 3       //Show shortest path

enum States{
    ST_Main,        //Main menu
    ST_GenMaze,     //Generate Maze menu - 1
    ST_GetMaze,     //Build Maze in MC  - 2
    ST_SolveMaze,   //Solve maze menu - 3
    ST_Creators,    //Team info - 4
    ST_Exit,        //Exit program - 5 
    ST_RandomMaze   //Generate random maze
};

int main(int numParams, char* arguments[]){

    bool mode = NORMAL_MODE;
    int enhancement = -1;

    //Error message for more than 2 parameters
    if (numParams > 2) {
        std::cerr << "Usage: " << arguments[0] << " <mode_option>" << std::endl;
        return 1; 
    }

    // //read Mode
    for (int i = 1; i < numParams; i++) {
        if (std::strcmp(arguments[i], "-testMode") == 0) {
            mode = TESTING_MODE;
        }
        else if (std::strcmp(arguments[i], "-E1") == 0) {
            enhancement = E1_MODE;
        }
        else if (std::strcmp(arguments[i], "-E2") == 0) {
            enhancement = E2_MODE;
        }
    }

    //Set solve algorithm for E2_MODE
    std::string solveAlgorithm = (enhancement == E2_MODE) ? ("BREADTH_FIRST_SEARCH") : ("RIGHT_HAND_FOLLOW");

    mcpp::MinecraftConnection mc; 
    mc.doCommand("time set day"); 

    //Get player location
    mcpp::Coordinate playerLoc = mc.getPlayerPosition();

    //Agent, Maze and readMaze objects
    Agent player(playerLoc, mode);
    Maze maze;
    readMaze rm;

    //Variables to monitor the mazes generated, built and solved
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
                // do not run read maze in E1
                if (enhancement == 2) {
                    std::cout << "Please use generate random maze for E1..." << std::endl;
                }
                else {
                    rm.executeReadMaze();
                    basePoint = mcpp::Coordinate(rm.getX(), rm.getY(), rm.getZ());
                    mazeDimensions = std::make_pair(rm.getLength(), rm.getWidth());
                    charMaze = rm.getEnvStructure();
                    mazeGenerated = true;
                }
            }
            else if (option == 2) {
                // Do generate random maze
                basePoint = getBasePoint();
                mazeDimensions = getMazeDimensions();
                // Program in E1_MODE
                if (enhancement == 2) {
                    charMaze = E1_genMaze(basePoint, mazeDimensions.first, mazeDimensions.second);
                    if (charMaze.size() == 0) {
                        std::cout << "MC environment not suitable. Please choose another area..." << std::endl;
                    }
                    else {
                        printMazeInTerminal(charMaze, basePoint.x, basePoint.y, basePoint.z);
                    }
                }
                // If program in NORMAL / TESTING / E2
                else {
                    charMaze = genMaze(mazeDimensions.first, mazeDimensions.second, mode);
                    printMazeInTerminal(charMaze, basePoint.x, basePoint.y, basePoint.z);
                }
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
            // Do Build Maze in MineCraft
            // Maze generated but not built
            if (mazeGenerated && !mazeBuilt) {
                //E1
                if (enhancement == 2) {
                    maze.setMazeParameters(basePoint, mazeDimensions.first, mazeDimensions.second);
                    maze.E1_buildMazeInMC(charMaze);
                }
                //E2, NORMAL, TEST MODE
                else {
                    maze.setMazeParameters(basePoint, mazeDimensions.first, mazeDimensions.second);
                    maze.buildMazeInMC(charMaze);
                }
                mazeBuilt = true;
            }
            // Maze generated and built
            else if (mazeGenerated && mazeBuilt) {
                //E1
                if (enhancement == 2) {
                    maze.E1_reverseMaze();
                    maze.setMazeParameters(basePoint, mazeDimensions.first, mazeDimensions.second);
                    maze.E1_buildMazeInMC(charMaze);
                }
                //E2, NORMAL, TEST MODE
                else {
                    maze.reverseTerrain();
                    maze.setMazeParameters(basePoint, mazeDimensions.first, mazeDimensions.second);
                    maze.buildMazeInMC(charMaze);
                }
                mazeBuilt = true;
            }
            else {
                std::cout << "Maze not defined! Generate maze before building." << std::endl;
            }
        }

        // Solve Maze Menu
        else if (option == 3) {
            if (!mazeBuilt){
                std::cout << "Build Maze before attempting to solve." << std::endl;
            }
            else {
                curState = ST_SolveMaze;
                while (curState == ST_SolveMaze) {
                    printSolveMazeMenu();
                    std::cin >> option;
                    if (option == 1) {
                        if (mazeBuilt) {
                            // Do Solve Manually
                            executeSolveManually(basePoint.x, basePoint.y, basePoint.z, mazeDimensions.first, mazeDimensions.second, charMaze, mode);
                            solveMan = true;
                        }
                    }
                    else if (option == 2) {
                        // Do Show Escape Route
                        if (solveMan) {
                            player.showEscapeRoute(solveAlgorithm);
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
        // E1
        if (enhancement == 2) {
            maze.E1_reverseMaze();
        }
        // E2, NORMAL, TEST MODE
        else {
            maze.reverseTerrain();
        }
    }

    // Print Exit Message
    printExitMassage();

    return EXIT_SUCCESS;

}
#include <iostream>
#include <utility>
#include <cstring>

// #include <mcpp/mcpp.h>

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
    ST_GenMaze, //Generate Maze menu - 1 ADDED BY ME
    ST_GetMaze, //Dummy message  - 2
    ST_SolveMaze, //Solve maze menu - 3
    ST_Creators, //Team info - 4
    ST_Exit,      // Exit message - 5 
    ST_RandomMaze
};

//TO DO: ADD ERROR MESSAGES FOR INVALID INT INPUTS

int main(int numParams, char* arguments[]){

    // bool mode = NORMAL_MODE;
    //read Mode

    int option;
    bool mazeGenerated = false;
    bool mazeBuilt = false;
    bool solveMan = false;
    for (int i = 1; i < numParams; i++) {
        if (std::strcmp(arguments[i], "-testMode") == 0) {
            mode = TESTING_MODE;
            i = numParams;
        }
    }

    // mcpp::MinecraftConnection mc; 
    // mc.doCommand("time set day"); 

    //Error messages
    std::string main_menu_Error = "Input Error: Enter a number between 1 and 5 ...."; //MAIN 
    std::string sub_menu_Error = "Input Error: Enter a number between 1 and 3 ....";

    //Get player location
    mcpp::Coordinate playerLoc = mc.getPlayerPosition();

    //Agent Object
    Agent player(playerLoc, mode);

    // //Maze object
    Maze *maze = nullptr;

    // bool mazeBuilt = false;
    bool mazeGenerated = false;

    std::vector<std::vector<char>> charMaze;
    
    //Base point
    mcpp::Coordinate basePoint;

    //Maze dimensions 
    std::pair<int, int> mazeDimensions;

    States curState = ST_Main;
    
    readMaze rm;

    // Opening Menu
    printStartText();

    int stateIndex = 0;
    printStartText();
    printMainMenu();

    std::cin >> stateIndex;
    
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
                mazeGenerated = true;
            }
            else if (option == 2) {
                // Do Generate Random Maze
                // std::cout << std::endl;
                // std::cout << "OPTION 2 [Generate Random Maze] WAS SUCCESSFULLY EXECUTED";
                // std::cout << std::endl;
            }
            else if (option == 3) {
                // Do Back (Return to Main Menu)
                curState = ST_Main;
                // std::cout << std::endl;
                // std::cout << "OPTION 3 [Back] WAS SUCCESSFUL EXECUTED";
                // std::cout << std::endl;
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
            if (mazeGenerated && !mazeBuilt) {
                saveOrigBlocks(rm.getX(), rm.getY(), rm.getZ(), rm.getLength(), rm.getWidth());
                executeBuildMaze(rm.getX(), rm.getY(), rm.getZ(), rm.getLength(), rm.getWidth(), rm.getEnvStructure());
                mazeBuilt = true;
            }
            else if (mazeGenerated && mazeBuilt) {
                reverseBuildMaze(rm.getX(), rm.getY(), rm.getZ(), rm.getLength(), rm.getWidth());
                executeBuildMaze(rm.getX(), rm.getY(), rm.getZ(), rm.getLength(), rm.getWidth(), rm.getEnvStructure());
                mazeBuilt = true;
            }
            else {
                std::cout << "Maze not defined! Generate maze before Building." << std::endl;
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
                    // Do Solve Manually
                    executeSolveManually(rm.getX(), rm.getY(), rm.getZ(), rm.getLength(), rm.getWidth(), rm.getEnvStructure());
                    solveMan = true;
                }
                else {
                    std::cout << "Build Maze before solving..." << std::endl;
                }
            }
            else if (option == 2) {
                // Do Show Escape Route
                if (solveMan) {
                    std::cout << std::endl;
                    std::cout << "OPTION 2 [Show Escape Route] WAS SUCCESSFULLY EXECUTED";
                    std::cout << std::endl;
                }
                else {
                    std::cout << "Initialize player using Solve manually." << std::endl;
                }
            }
            else if (option == 3) {
                // Do Back (Return to Main Menu)
                // std::cout << std::endl;
                // std::cout << "OPTION 3 [Back] WAS SUCCESSFUL EXECUTED";
                // std::cout << std::endl;
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
        reverseBuildMaze(rm.getX(), rm.getY(), rm.getZ(), rm.getLength(), rm.getWidth());
    }
    // Print Exit Message
    printExitMassage();


    return EXIT_SUCCESS;

}
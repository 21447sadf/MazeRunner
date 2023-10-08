#include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"
#include "readMaze.h"
#include "buildMaze.h"

#include <limits>

#define NORMAL_MODE 0
#define TESTING_MODE 1

enum States{
    ST_Main,
    ST_GetMaze,
    ST_SolveMaze,
    ST_Creators,
    ST_Exit
};

int main(void){

    // bool mode = NORMAL_MODE;
    //read Mode

    int option;

    // mcpp::MinecraftConnection mc; 
    // mc.doCommand("time set day"); 

    States curState = ST_Main;
    
    readMaze rm;

    // Opening Menu
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
                // std::cout << std::endl;
                // std::cout << "OPTION 1 [Read Maze from terminal] WAS SUCCESSFULLY EXECUTED";
                // std::cout << std::endl;
            }
            else if (option == 2) {
                // Do Generate Random Maze
                std::cout << std::endl;
                std::cout << "OPTION 2 [Generate Random Maze] WAS SUCCESSFULLY EXECUTED";
                std::cout << std::endl;
            }
            else if (option == 3) {
                // Do Back (Return to Main Menu)
                curState = ST_Main;
                std::cout << std::endl;
                std::cout << "OPTION 3 [Back] WAS SUCCESSFUL EXECUTED";
                std::cout << std::endl;
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
            executeBuildMaze(rm.getX(), rm.getY(), rm.getZ(), rm.getLength(), rm.getWidth(), rm.getEnvStructure());
            // std::cout << std::endl;
            // std::cout << "OPTION 2 [BUILD MAZE] WAS SUCCESSFUL EXECUTED";
            // std::cout << std::endl;
        }

        // Solve Maze Menu
        else if (option == 3) {
            curState = ST_SolveMaze;
            while (curState == ST_SolveMaze) {
            printSolveMazeMenu();
            std::cin >> option;
            if (option == 1) {
                // Do Solve Manually
                std::cout << std::endl;
                std::cout << "OPTION 1 [Solve Manually] WAS SUCCESSFULLY EXECUTED";
                std::cout << std::endl;
            }
            else if (option == 2) {
                // Do Show Escape Route
                std::cout << std::endl;
                std::cout << "OPTION 2 [Show Escape Route] WAS SUCCESSFULLY EXECUTED";
                std::cout << std::endl;
            }
            else if (option == 3) {
                // Do Back (Return to Main Menu)
                std::cout << std::endl;
                std::cout << "OPTION 3 [Back] WAS SUCCESSFUL EXECUTED";
                std::cout << std::endl;
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

    // Print Exit Message
    printExitMassage();


    return EXIT_SUCCESS;

}
#include <iostream>

// #include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"


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

int main(void){

    bool mode = NORMAL_MODE;
    mode += 0;
    //read Mode

    

    mcpp::MinecraftConnection mc; 
    mc.doCommand("time set day"); 

    //Error messages
    std::string main_menu_Error = "Invalid input. Please enter a number between 1 and 5"; //MAIN 
    std::string sub_menu_Error = "Invalid input. Please enter number between 1 and 3";

    //Get player location
    mcpp::Coordinate playerLoc = mc.getPlayerPosition();

    //Agent Object
    Agent player(playerLoc);

    States curState = ST_Main;

    int stateIndex = 0;
    printMainMenu();

    std::cin >> stateIndex;
    
    //State machine for menu        
    while (curState != ST_Exit)
    {
        //Do something
        if (std::cin.fail()) {   // If input was not an int
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::string error_out;
            if (curState == ST_Main) {
                if ((stateIndex < 1) ||(stateIndex > 5)) {  // INVALID INPUT ON MAIN MENU
                std::cout << main_menu_Error << std::endl;
                }
            }
            else if ((curState == ST_GenMaze) || (curState == ST_SolveMaze)) {
                if ((stateIndex < 1) || (stateIndex > 3)) {
                std::cout << sub_menu_Error << std::endl;
                }
            }
            else {
            curState = ST_Main;
            printMainMenu();
            }
        } 
        if (curState != ST_Main) {
            if (curState == ST_GenMaze) {
                if (stateIndex == 1) {
                    std::cout << "You selected Read Maze from Terminal" << std::endl;
                }
                else if (stateIndex == 2) {
                    std::cout << "You selected Generate Random Maze" << std::endl;
                    std::vector<std::vector<char>> maze = genMaze();
                }
                curState = ST_Main;
                printMainMenu();
            }
            else if (curState == ST_SolveMaze) {
                if (stateIndex == 1) {
                    std::cout << "You selected Solve Manually" << std::endl;
                }
                else if (stateIndex == 2) {
                    std::cout << "You selected Show Escape Route" << std::endl;
                    player.orientPlayer();
                    std::vector<mcpp::Coordinate> route = player.findPath();
                }
                curState = ST_Main;
                printMainMenu();
            }
        }
        else if (curState == ST_Main) {
            if (stateIndex == ST_GenMaze) {
                printGenerateMazeMenu();
                curState = ST_GenMaze;
            }
            else if (stateIndex == ST_GetMaze) {
                std::cout << "Dummy message (Build Maze in MC)" << std::endl;
                curState = ST_Main;
                printMainMenu();
            }
            else if (stateIndex == ST_SolveMaze) {
                printSolveMazeMenu();
                curState = ST_SolveMaze;
            }
            else if (stateIndex == ST_Creators) {
                printTeamInfo();
                curState = ST_Main;
                printMainMenu();
            }
            else if (stateIndex == ST_Exit) {
                curState = ST_Exit;
            }
        }
        if (curState != ST_Exit) {
            std::cin >> stateIndex;
        }
        }

    printExitMassage();


    return EXIT_SUCCESS;

}
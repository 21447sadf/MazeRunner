#include <iostream>

// #include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"


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

    

    // mcpp::MinecraftConnection mc; 
    // mc.doCommand("time set day"); 

    States curState = ST_Main;

    // bool inMainMenu = true;

    int stateIndex = 0;
    printMainMenu();

    
    
    //State machine for menu        
    while (curState != ST_Exit)
    {
        //Do something
        std::cin >> stateIndex;
        while ((stateIndex > 5) || (stateIndex < 1)) {
            std::cout << "Please enter a number between 1 and 5" << std::endl;
        
        if (curState == ST_Main) {
            if ((stateIndex > 5) || (stateIndex < 1)) {
            std::cout << "Please enter a number between 1 and 5" << std::endl;
            }
        }
        else if ((curState == ST_GenMaze) || (curState == ST_SolveMaze)) {
            while ((stateIndex > 3) || (stateIndex < 1)) {
                std::cout << "Please enter a number between 1 and 3" << std::endl;
            }
        }
        else if (std::cin.fail()) {   // Add error condition for number options > 5 or < 0
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Please enter a numeric option" << std::endl;
            curState = ST_Main;
            printMainMenu();
        } 
        if (curState != ST_Main) {
            if (stateIndex == 1) {
                std::cout << "You selected Option 1" << std::endl;
            }
            else if (stateIndex == 2) {
                std::cout << "You selected Option 2" << std::endl;
            }
            curState = ST_Main;
            printMainMenu();
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
        }

    }

    printExitMassage();


    return EXIT_SUCCESS;

}
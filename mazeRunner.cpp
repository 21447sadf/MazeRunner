#include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"

#define NORMAL_MODE 0
#define TESTING_MODE 1

enum States{
    ST_Main,
    ST_GetMaze,
    ST_SolveMaze,
    ST_Creators,
    ST_Exit,
    ST_RandomMaze  //Random Maze enumerator
};

int main(void){

   // bool mode = NORMAL_MODE;
    //read Mode

    

    mcpp::MinecraftConnection mc; 
    mc.doCommand("time set day"); 

    States curState = ST_Main;

    //State machine for menu        
    while (curState != ST_Exit)
    {
        //Do something
    }

   // Random_maze+






















































































































































































    

    printExitMassage();


    return EXIT_SUCCESS;

    //State machine for RandomMaze

}
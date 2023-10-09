 #include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"
#include "mazeRunner.cpp"

#define NORMAL_MODE 0
#define TESTING_MODE 1


int main(void){

    bool mode = NORMAL_MODE;
    //read Mode
 
 
 mcpp::MinecraftConnection mc; 

    mc.doCommand("time set day"); 

    States curState = ST_RandomMaze;
}

 #include <iostream>

#include <mcpp/mcpp.h>

#include "menuUtils.h"
#include "Maze.h"
#include "Agent.h"
#include "mazeRunner.cpp"
#include <random>


#define NORMAL_MODE 0
#define TESTING_MODE 1

// declare inputs

int xPoint;
int yPoint;
int zPoint;
int width;
int length;


  std::vector<std::vector<char>> randomMaze(void){
    States curState = ST_RandomMaze;

    std::vector<std::vector<char>> maze;
   // a vector of vectors to store the maze

   std::cout<< "Please enter base point." << std::endl;
   std::cin << xPoint;
   std::cin << yPoint;
   std::cin << zPoint;
   
   std::cout<< "Please enter width."
   std::cin>>width;
   
   std::cout<<"Please enter length."
   std::cin>>length;
   
   // recursive backtracking

  //instantiate the 2D array with x

    for(int i = 0 ; i < width; < i++){
        maze.push_back(std::vector<char>row(length))
        //adding the characters in the vectors (x)
        std::vector<char>curRow = maze.at(i);
    
        for(int j = 0 ; j < length; j++){
           maze.at(i).at(j)='x';
           // looking at the column of that row and filling it up with x
           std::cout<< maze.at(i).at(j) <<" ";
             
        }

        std::cout<< endl;
    }



   return maze;

}
// engine
// uniform distribution
// seed
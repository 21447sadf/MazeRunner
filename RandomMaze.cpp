#include <iostream>
#include <vector>
#include <mcpp/mcpp.h>
#include "Maze.h"
#include "Agent.h"
#include <random>
#include <algorithm>
#define NORMAL_MODE 0
#define TESTING_MODE 1


// Check if its at the edge or carved or top using boolean statement
// enumerator for adjacent value
// function to check if the co ordinate is at the top or if the cell has already been carved.
// store the path in a stack to keep track of where u are, then 
bool isOnEdgeOrCarved(const std::vector<std::vector<char>> &maze, unsigned int x, unsigned int z)
{
    // Check if on edge
    if (x == 0 || x == maze.size() - 1 || z == 0 || z == maze[0].size() - 1)
    {
        return true;
    }
    // Check if path is already carved
    if (maze[x][z] == '.')
    {
        return true;
    }
    return false;
}

enum Direction
{
    Up,
    Down,
    Left,
    Right
};

// recursive backtrack algorithm

std::vector<std::vector<char>> randomMaze()
{
    int xPoint, yPoint, zPoint, width, length;
    std::vector<std::vector<char>> maze;

    std::cout << "Please enter the co-ordinates for the base point:" << std::endl;
    std::cout << "xPoint:";
    std::cin >> xPoint;
    std::cout << "yPoint:";
    std::cin >> yPoint;
    std::cout << "zPoint:";
    std::cin >> zPoint;

    std::cout << "Please enter width:";
    std::cin >> width;

    std::cout << "Please enter length:";
    std::cin >> length;

    for (int i = 0; i < width; i++)
    {
        maze.push_back(std::vector<char>(length));
        for (int j = 0; j < length; j++)
        {
            maze[i][j] = 'x';
            std::cout << maze[i][j] << " ";
        }
        std::cout << std::endl; // To move to the next line after printing each row
    }

    // the recursive algorithm
    // to choose a random starting point

    int max_x = width - 1; // MIGHT NEED TO REVIEW X AND Z DIRECTIONS WHEN IMPLEMENTING IN MC
    int random_x = 0;
    int max_z = length - 1;
    int random_z = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib_x(1, max_x - 1); // for width, the max_x -1 is to determine that the width is not at the edge
    random_x = distrib_x(gen);
    std::uniform_int_distribution<> distrib_z(1, max_z - 1); // for length, the max_z -1 is to determine that the width is not at the edge as well
    random_z = distrib_z(gen);
    std::cout << random_z << " " << random_x << std::endl;

    // While current co ordinates are not your starting co ordinates
    //  Recursive backtracking algorithm
    //  Implementation of the first starting point
    //  create a boolean function to check if the dot is at the edge
 
    // bool startAtEdge = random_z == 1 || random_z == maze[0].size() - 2 || random_x == 1 || random_x == maze.size() - 2;
    // recursiveBacktrack(maze, random_x, random_z, gen, startAtEdge);

    // Implementation of the second starting point
    // Recursive backtracking algorithm to start carving
    // generate a random direction

    return maze;
}

    
 void recursiveBacktrack(std::vector<std::vector<char>> &maze, int x, int z, std::mt19937 &gen) 
{
    std::vector<Direction> directions = {Up, Down, Left, Right};
    std::shuffle(directions.begin(), directions.end(), gen); // Shuffle the directions for randomness

    for (auto dir : directions) 
    {
        int newX = x, newZ = z;
        switch (dir) 
        {
            case Up:    newX -= 2; break;
            case Down:  newX += 2; break;
            case Left:  newZ -= 2; break;
            case Right: newZ += 2; break;
        }

        // Check if the newX, newZ position is valid for moving to
       if (newX > 0 && newX < static_cast<int>(maze.size()) && newZ > 0 && newZ < static_cast<int>(maze[0].size()) && maze[newX][newZ] == 'x')

        {
            // Carve a path to the new cell
            maze[newX][newZ] = '.';
            if (dir == Up) maze[x-1][z] = '.';
            if (dir == Down) maze[x+1][z] = '.';
            if (dir == Left) maze[x][z-1] = '.';
            if (dir == Right) maze[x][z+1] = '.';

            // Recursively call the function with the new position
            recursiveBacktrack(maze, newX, newZ, gen);
        }
    }
}
    
// validate user input



int main() 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    int random_x = 0;
    int random_z = 0;

    std::vector<std::vector<char>> maze = randomMaze();
    recursiveBacktrack(maze, random_x, random_z, gen);
    return 0;
}

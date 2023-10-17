#ifndef RANDOM_MAZE_H
#define RANDOM_MAZE_H


#include <vector>
#include <iostream>
#include <mcpp/mcpp.h>
#include <random>
#include <stack>

#define NORMAL_MODE 0
#define TESTING_MODE 1

class Maze
{
public:
    Maze(mcpp::Coordinate basePoint, unsigned int xlen, unsigned int zlen);
    ~Maze();

    void generate(); // Generate a random maze
    void display() const; // Display the maze
    std::vector<std::vector<char>> getMaze() const; // Get the maze matrix

private:
    mcpp::Coordinate basePoint;
    unsigned int xlen;
    unsigned int zlen;
    std::vector<std::vector<char>> maze;
    std::mt19937 gen; // Random number generator

    enum Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    struct Cell
    {
        int x;
        int z;
    };

    // Private helper functions
    bool isOnEdgeOrCarved(const std::vector<std::vector<char>> &maze, unsigned int x, unsigned int z);
    bool hasUnvisitedNeighbors(const std::vector<std::vector<char>> &maze, int x, int z);
    void generateMaze(std::vector<std::vector<char>> &maze, int startX, int startZ, std::mt19937 &gen);
    void randomMaze();
};

#endif 

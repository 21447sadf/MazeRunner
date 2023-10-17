#include <iostream>
#include <vector>
#include <mcpp/mcpp.h>
#include "Maze.h"
#include "Agent.h"
#include <random>
#include <algorithm>
#include <stack> 
#define NORMAL_MODE 0
#define TESTING_MODE 1


enum CellStatus {
    Unvisited,   // Not visited yet ('x')
    Visited,     // Already visited ('.')
    Path         // Part of the solution path ('O')
};

bool solveMaze(std::vector<std::vector<char>>& maze, int x, int z, std::vector<Cell>& solutionPath) {
    // If it's out of bounds or it's already been visited, return false.
    if (x < 0 || x >= maze.size() || z < 0 || z >= maze[0].size() || maze[x][z] != '.') {
        return false;
    }

    // Convert to Visited status to avoid re-visiting.
    maze[x][z] = 'V';

    // Base case: If you've reached the same entry (exit), you've found a path.
    if (x == solutionPath[0].x && z == solutionPath[0].z && solutionPath.size() > 1) {
        solutionPath.push_back({x, z});
        return true;
    }

    // Try all four directions
    Cell newCoords[4] = {
        {x + 1, z},  // down
        {x - 1, z},  // up
        {x, z + 1},  // right
        {x, z - 1}   // left
    };

    for (int i = 0; i < 4; i++) {
        if (solveMaze(maze, newCoords[i].x, newCoords[i].z, solutionPath)) {
            solutionPath.push_back({x, z});  // Add the current cell to the path.
            return true;
        }
    }

    return false;  // No path was found from this cell.
}

void findSolution(std::vector<std::vector<char>> maze) {
    int startX = 0, startZ = 0;  // Assuming entry point is at the top-left corner
    std::vector<Cell> solutionPath = {{startX, startZ}};
    
    solveMaze(maze, startX, startZ, solutionPath);

    // Display the solution path
    std::reverse(solutionPath.begin(), solutionPath.end());  // Reverse the path for correct order
    for (size_t i = 0; i < solutionPath.size(); i++) {
        std::cout << "(" << solutionPath[i].x << "," << solutionPath[i].z << ")";
        if (i != solutionPath.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

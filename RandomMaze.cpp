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
struct Cell
{
    int x;
    int z;
};

bool hasUnvisitedNeighbors(const std::vector<std::vector<char>> &maze, int x, int z)
{
    // Check above
    if (x > 1 && maze[x - 2][z] == 'x')
        return true;
    // Check below
    if (x < static_cast<int>(maze.size()) - 2 && maze[x + 2][z] == 'x')
        return true;
    // Check left
    if (z > 1 && maze[x][z - 2] == 'x')
        return true;
    // Check right
    if (z < static_cast<int>(maze[0].size()) - 2 && maze[x][z + 2] == 'x')
        return true;

    return false;
}

void generateMaze(std::vector<std::vector<char>> &maze, int startX, int startZ, std::mt19937 &gen)
{
    std::stack<Cell> cellStack;
    Cell current = {startX, startZ};
    cellStack.push(current);
    // check if cell has any neighbours, if it doesn't you pop back and backtrack
    while (!cellStack.empty())
    {
        current = cellStack.top();
        cellStack.pop();

        maze[current.x][current.z] = '.';

        std::vector<Direction> directions = {Up, Down, Left, Right};
        std::shuffle(directions.begin(), directions.end(), gen); // Shuffle the directions for randomness
        
        for (Direction dir : directions)
        {
            int newX = current.x, newZ = current.z;
            int midX = current.x, midZ = current.z;

            if (dir == Up)
            {
                newX -= 2;
                midX -= 1;
            }
            else if (dir == Down)
            {
                newX += 2;
                midX += 1;
            }
            else if (dir == Left)
            {
                newZ -= 2;
                midZ -= 1;
            }
            else if (dir == Right)
            {
                newZ += 2;
                midZ += 1;
            }

            if (newX > 0 && newX < static_cast<int>(maze.size()) - 1 &&
                newZ > 0 && newZ < static_cast<int>(maze[0].size()) - 1 &&
                maze[newX][newZ] == 'x' && !isOnEdgeOrCarved(maze, newX, newZ))
            {
                maze[midX][midZ] = '.';
                cellStack.push({newX, newZ});
               
            }

        }
    }
    // generateMaze(maze, adj_x, adj_z, gen);
    
}
std::vector<std::vector<char>> randomMaze()
{
    int width, length;
    std::vector<std::vector<char>> maze;

    // Coordinate input:
    double baseX, baseY, baseZ;
    std::cout << "Please enter the base x-coordinate:";
    std::cin >> baseX;
    while (std::cin.fail())
    {
        std::cin.clear();                                                   // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        std::cerr << "Error: Invalid x-coordinate!" << std::endl;
        std::cout << "Please enter the base x-coordinate:";
        std::cin >> baseX;
    }

    std::cout << "Please enter the base y-coordinate:";
    std::cin >> baseY;
    while (std::cin.fail())
    {
        std::cin.clear();                                                   // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        std::cerr << "Error: Invalid y-coordinate!" << std::endl;
        std::cout << "Please enter the base y-coordinate:";
        std::cin >> baseY;
    }

    std::cout << "Please enter the base z-coordinate:";
    std::cin >> baseZ;
    while (std::cin.fail())
    {
        std::cin.clear();                                                   // clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        std::cerr << "Error: Invalid z-coordinate!" << std::endl;
        std::cout << "Please enter the base z-coordinate:";
        std::cin >> baseZ;
    }

    mcpp::Coordinate basePoint(baseX, baseY, baseZ);

    while (true)
    {
        std::cout << "Please enter width:";
        std::cin >> width;

        // Check if input was an integer and odd
        if (std::cin.fail() || width % 2 == 0)
        {
            std::cin.clear();                                                   // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cerr << "Error: Width must be an odd integer!" << std::endl;
        }
        else
        {
            break; // valid input; break out of the loop
        }
    }

    while (true)
    {
        std::cout << "Please enter length:";
        std::cin >> length;

        // Check if input was an integer and odd
        if (std::cin.fail() || length % 2 == 0)
        {
            std::cin.clear();                                                   // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cerr << "Error: Length must be an odd integer!" << std::endl;
        }
        else
        {
            break; // valid input; break out of the loop
        }
    }

    for (int i = 0; i < width; i++)
    {
        maze.push_back(std::vector<char>(length));
        for (int j = 0; j < length; j++)
        {
            maze[i][j] = 'x';
            // std::cout << maze[i][j] << " ";
        }
        std::cout << std::endl; // To move to the next line after printing each row
    }

    // This determines a random starting point
    // This determines a random starting point on an edge
    int max_x = width - 1;
    int max_z = length - 1;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(1, 4); // 1 for top, 2 for bottom, 3 for left, 4 for right
    int edge = distrib(gen);

    int random_x = 0; // Default initialization
    int random_z = 0; // Default initialization

    if (edge == 1)
    { // top
        random_x = 0;
        std::uniform_int_distribution<> distrib_z(1, max_z - 1);
        random_z = distrib_z(gen);
    }
    else if (edge == 2)
    { // bottom
        random_x = max_x;
        std::uniform_int_distribution<> distrib_z(1, max_z - 1);
        random_z = distrib_z(gen);
    }
    else if (edge == 3)
    { // left
        random_z = 0;
        std::uniform_int_distribution<> distrib_x(1, max_x - 1);
        random_x = distrib_x(gen);
    }
    else if (edge == 4)
    { // right
        random_z = max_z;
        std::uniform_int_distribution<> distrib_x(1, max_x - 1);
        random_x = distrib_x(gen);
    }
    else
    {
        std::cerr << "Unexpected edge value" << std::endl;
        exit(EXIT_FAILURE); // Or handle this error in another way
    }
    maze[random_x][random_z] = '.'; // Starting point of our maze

    // Start the recursive backtracking from the randomly chosen starting point
    // recursiveBacktrack(maze, random_x, random_z, gen);
    // Choose adjacent cell to the starting point for recursive backtracking
    int adj_x = random_x;
    int adj_z = random_z;

    // Calculate the adjacent cell based on the chosen edge cell
    if (random_x == 0)
    {                         // top edge
        adj_x = random_x + 1; // adjacent cell is below
    }
    else if (random_x == width - 1)
    {                         // bottom edge
        adj_x = random_x - 1; // adjacent cell is above
    }
    else if (random_z == 0)
    {                         // left edge
        adj_z = random_z + 1; // adjacent cell is to the right
    }
    else if (random_z == length - 1)
    {                         // right edge
        adj_z = random_z - 1; // adjacent cell is to the left
    }

    maze[adj_x][adj_z] = '.'; // Carve the adjacent cell
    // Start the recursive backtracking from the adjacent cell
    // In the recursiveBacktrack function, before carving, check if the path is already carved

     generateMaze(maze, adj_x, adj_z, gen);

    // Display the maze
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < length; j++)
        {
            std::cout << maze[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return maze;
}

int main()
{
    randomMaze();
    return 0;
}
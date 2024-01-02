// Include any necessary headers here
#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>
#include <vector>
#include <limits>

// Declare the class
class readMaze {
public:
    readMaze();  // Constructor
    // ~readMaze();
    void executeReadMaze();
    int getX() const;
    int getY() const;
    int getZ() const;
    int getLength() const;
    int getWidth() const;
    const std::vector<std::vector<char>>& getEnvStructure() const;

    struct cell;
    bool isMazeValid();
    bool pathExists(cell currCell, cell entrance);


private:
    int build_x;
    int build_y;
    int build_z;
    int envLength;
    int envWidth;
    std::vector<std::vector<char>> envStructure;
};

// Include any necessary headers here
#include <iostream>
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

private:
    int build_x;
    int build_y;
    int build_z;
    int envLength;
    int envWidth;
    std::vector<std::vector<char>> envStructure;
};

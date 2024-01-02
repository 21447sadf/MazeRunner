#include "readMaze.h"

// Constructor to initialize member variables
readMaze::readMaze() {
    build_x = 0;
    build_y = 0;
    build_z = 0;
    envLength = 0;
    envWidth = 0;
    // envStructure = nullptr;
}

void readMaze::executeReadMaze() {
    // basePoint of Maze

    bool validInput = false;
        std::cout << "Enter the basePoint of maze:" << std::endl;
        while (!validInput) {
        try {
            if (!(std::cin >> build_x) || !(std::cin >> build_y) || !(std::cin >> build_z)) {
                throw std::invalid_argument("Invalid input. Please enter integers:");
            }
            else {
                validInput = true;
            }
        }
         catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear();  // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
        }
    }

    // Length & Width of Maze
    validInput = false;

    std::cout << "Enter the length and width of maze:" << std::endl;
    while (!validInput) {
        try {
            if (!(std::cin >> envLength) || !(std::cin >> envWidth)) {
                throw std::invalid_argument("Invalid input. Please enter integers:");
            }
            else if ((envLength % 2 == 0) || (envWidth % 2 == 0)) { //If inputs are even
                throw std::invalid_argument("Dimensions must be odd and positive. Please re-enter:");
            }
            else if ((envLength < 5) || (envLength > 99) || (envWidth < 5) || (envWidth > 99)) { //Inputs not between 3-99
                throw std::invalid_argument("Dimensions exceed allowable limits (5-99). Please re-enter:");
            }
            else {
                validInput = true;
            }
        }
         catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            std::cin.clear();  // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the input buffer
        } 
    }

    // Maze Structure
    // char envStructure[envLength][envWidth];
    envStructure.resize(envLength, std::vector<char>(envWidth));
    char readChar;

    std::cout << "Enter the maze structure:" << std::endl;


    //ADD: CHARACTER CHECKS FOR '.' AND 'x' ONLY
    for (int row = 0; row < envLength; row++) {
        for (int col = 0; col < envWidth; col++) {
            std::cin >> readChar;
            envStructure[row][col] = readChar;
        }
    }

    //ADD: CHECK IF MAZE IS VALID/PERFECT
    isMazeValid();

    // Print Information
    std::cout << "Maze read successfully" << std::endl;
    std::cout << "**Printing Maze**" << std::endl;
    std::cout << "BasePoint: (" << build_x << ", " << build_y << ", " << build_z << ")" << std::endl;
    std::cout << "Structure:" << std::endl;
    for (int row = 0; row < envLength; row++) {
        for (int col = 0; col < envWidth; col++) {
            std::cout << envStructure[row][col];
        }
        std::cout << std::endl;
    }
    std::cout << "**End Printing Maze**" << std::endl;
}

int readMaze::getX() const {
    return build_x;
}

int readMaze::getY() const {
    return build_y;
}

int readMaze::getZ() const {
    return build_z;
}

int readMaze::getLength() const {
    return envLength;
}

int readMaze::getWidth() const {
    return envWidth;
}

const std::vector<std::vector<char>>& readMaze::getEnvStructure() const {
    return envStructure;
}

struct readMaze::cell {
    int X;
    int Z;

    cell getNeighbor(int direction) {
        cell nextCell;
        
        if (direction == 0) { //UP
            nextCell = {X - 2, Z};
        }
        else if (direction == 1) { //DOWN
            nextCell = {X + 2, Z};
        }
        else if (direction == 2) { //LEFT
            nextCell = {X, Z - 2};
        }
        else if (direction == 3) { //RIGHT
            nextCell = {X, Z + 2};
        }
        
        return nextCell;
    }

    bool operator==(cell otherCell) {
        return ((X == otherCell.X) && (Z == otherCell.Z));
    }
};

//DFS Search to determine if maze is valid
bool readMaze::pathExists(cell currCell, cell entrance) {

    //Vector to track visited cells
    std::vector<cell> visited;

    //Create queue for DFS
    std::list<cell> queue;

    //Mark entrance as visited and push onto queue
    visited.push_back(currCell);
    queue.push_back(currCell);


    while (!queue.empty()) {
        //Dequeue front cell 
        currCell = queue.front();
        queue.pop_front();

        //Get adjacent neighbors on current cell

        for (int direction = 0; direction < 4; ++direction) {
            cell neighbor = currCell.getNeighbor(direction);

            //Check neighbor is within maze boundaries
            if ((neighbor.X >= 0) && (neighbor.X <= envLength) && (neighbor.Z >= 0) && (neighbor.Z <= envLength)) {
                //If neighbor is entrance, return true
                if (neighbor == entrance) {
                    return true;
                }
                //Mark neighbor as visited and push onto queue
                if ((envStructure[neighbor.X - 2][neighbor.Z] == '.') && (envStructure[neighbor.X - 1][neighbor.Z] == '.')) {
                    visited.push_back(neighbor);
                    queue.push_back(neighbor);
                    direction = 4;
                }
            }
        }
    }
    
    return false;
}


bool readMaze::isMazeValid() {

    int envLength = envStructure.size();
    int envWidth = envStructure[0].size();

    bool isValid = true;
    int mazeEntranceX = -1;
    int mazeEntranceZ = -1;

    //STEP 1: FIND ENTRY POINT

    //CHECK TOP & BOTTOM WALLS
    for (int col = 1; col < envWidth - 1; ++col) {
        //Top 
        if (envStructure[0][col] == '.') {
            mazeEntranceX = 0;
            mazeEntranceZ = col;
        }
        //Bottom
        else if (envStructure[envLength - 1][col] == '.') {
            mazeEntranceX = envLength - 1;
            mazeEntranceZ = col;
        }
    }

    //CHECK LEFT & RIGHT WALLS
    for (int row = 1; row < envLength - 1; ++row) {
        if (envStructure[row][0] == '.') {
            mazeEntranceX = row;
            mazeEntranceZ = 0;
        }
        else if (envStructure[row][envWidth - 1] == '.') {
            mazeEntranceX = row;
            mazeEntranceZ = envWidth - 1;
        } 
    }

    //If entrance not found, return false
    if ((mazeEntranceX == -1) && (mazeEntranceZ == -1)) {
        return false;
    }

    //STEP 2: CHECK MAZE PATHS - BFS

    //If maze is valid, each carved cell has one unique path to the entrance

    cell entrance = {mazeEntranceX, mazeEntranceZ};

    for (int row = 1; row < envLength - 1; ++row) {
        for (int col = 1; col < envWidth - 1; ++col) {
            //Perform BFS on each cell, '.', to determine it has a valid path to entrance
            if (envStructure[row][col] == '.') {
                cell currCell= {row, col};
                if (!pathExists(currCell, entrance)) {
                    return false;
                }
            }
        }
    }
    

    return isValid;
}
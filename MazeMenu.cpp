#include <iostream>
#include "menuUtils.h"
#include <limits>
#include "RandomMaze.h"
#include "SolveMaze.h"

void mazeMenu() {
    int choice;

    printStartText(); 

    while (true) {
        printMainMenu();
        
        if (!(std::cin >> choice) || (choice < 1) || (choice > 5)) {
            std::cout << "Please enter a number between 1 and 5." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
            while (true) {
                printGenerateMazeMenu();

                if (!(std::cin >> choice) || (choice < 1) || (choice > 3)) {
                    std::cout << "Please enter a number between 1 and 3." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                  printGenerateMazeMenu();
                if (choice == 2) {
                 
                } else if (choice == 3) {
                    
                    break;
                }
            }
        } else if (choice == 2) {
            std::cout << "Generating maze in Minecraft!" << std::endl;
        } else if (choice == 3) {
            while (true) {
              printGenerateMazeMenu();

                if (!(std::cin >> choice) || (choice < 1) || (choice > 3)) {
                    std::cout << "Please enter a number between 1 and 3." << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }

                if (choice == 3) {
                  
                }
            }
        } else if (choice == 4) {
            printTeamInfo();
        } else if (choice == 5) {
            printExitMassage();
            break;
        }
    }
}

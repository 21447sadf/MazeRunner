#include <iostream>
#include "menuUtils.h"
#include <limits>

int main() {
    int choice;

    printStartText(); 

    while (true) {
        printMainMenu();
        
        while (!(std::cin >> choice) || (choice < 1) || (choice > 5)) {
            std::cout << "Please enter a number between 1 and 5." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printMainMenu();
        }

        switch (choice) {
            case 1:
                while (true) {
                    printGenerateMazeMenu();

                    while (!(std::cin >> choice) || (choice < 1) || (choice > 3)) {
                        std::cout << "Please enter a number between 1 and 3." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        printGenerateMazeMenu();
                    }

                    if (choice == 3) break;  
                    
                    switch (choice) {
                        // Logic for options 1 and 2
                    }
                }
                break;

            case 2:
                // Logic for building maze in Minecraft.
                //Build Maze code 
                break;

            case 3:
                while (true) {
                    printSolveMazeMenu();

                    while (!(std::cin >> choice) || (choice < 1) || (choice > 3)) {
                        std::cout << "Please enter a number between 1 and 3." << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        printSolveMazeMenu();
                    }

                    if (choice == 3) break;

                    switch (choice) {
                        // Logic for options 1 and 2
                    }
                }
                break;

            case 4:
                printTeamInfo();
                break;

            case 5:
                printExitMassage();
                return 0;
        }
    }

    return 0;
}

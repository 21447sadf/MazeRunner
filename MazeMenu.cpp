#include <iostream>
#include "menuUtils.h"
// We can have extra function declarations here when we have them
// This file implements the function declared in the menuU
int main() {

    int choice;

    printStartText(); // This is the function in the menuUtils.h
  // try catch block to catch exceptions
    while (true) {
        printMainMenu();  // This is another function in menuUtils.h
        std::cin >> choice;

        switch (choice) {
            case 1:
                while(true) {
                    printGenerateMazeMenu();
                    std::cin >> choice;
                    
                    if(choice == 3) break;  // Exit to main menu
                    
                    // Additional logic for Generate Maze submenu options can be placed here
                    switch (choice) {
                        // case 1, case 2 etc. 
                    }
                }
                break;
                
            case 2:
                // Call function or logic to build maze in Minecraft.
                break;

            case 3:
                while(true) {
                    printSolveMazeMenu();
                    std::cin >> choice;
                    
                    if(choice == 3) break;  // Exit to main menu
                    
                    // Additional logic for Solve Maze submenu options can be placed here
                    switch (choice) {
                        // case 1, case 2 etc. 
                    }
                }
                break;

            case 4:
                printTeamInfo();
                break;

            case 5:
                printExitMassage();
                return 0;

            default:
                std::cout << "Invalid choice. Please select a valid menu item." << std::endl;
        }
    }

    return 0;

}
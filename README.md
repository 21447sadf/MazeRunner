## Team Information
Team Number: 58

### GitHub User Mapping
- `DameerP`: s4006119
- `21447sadf`: s3946776
- `LabibaShaikh`: s3954789
- `DevlynJB`: s3844511

For most tasks each team member were working individually on their tasks using their own branches on github.
- `DameerP` worked with the `dameer_menu` branch.
- `21447sadf` worked with the `Sadf---Main-Menu` branch.
- `LabibaShaikh` worked with the `Labiba_menu` branch.
- `DevlynJB` worked with the `Devlyn_menu`, `E1_branch` and `E1_final` branch.
- Everyone worked with the `main` branch.

When everyone completed their tasks on their seperate branches, the branches are then merged to the main central repository 
to form the complete program.

## Program Information
This program is an expansion pack to the game Minecraft. 
It allows players to generate, build and solve mazes in the game.

HOW TO RUN THE PROGRAM:
- Ensure that you have a Minecraft Spigot Server running already and already have the game running and on that server (version 1.19.4).
- Open up a terminal and make sure you navigate to the program folder.
- Run the mazeRunner file using the terminal to start the program as such "./mazeRunner".
   - if you wish to run the program in test mode use the "-testMode" flag as such "./mazeRunner -testMode".
- You should now be greeted with the program interface and be able to interact with it.

PROGRAM OVERVIEW:
The Main Menu displays 5 options.
1. Generate Maze
   Generate maze gives the player three options.
   1. Read Maze From Terminal
   - Allows the player to input their own maze structure using the terminal.
   2. Generate Random Maze
   - Allow the player to generate a random maze structure.
   3. Back
   - Returns to main menu
2. Build Maze in MineCraft
   - Will build the maze generated from "Generate Maze" (Option 1) in Minecraft
3. Solve Maze
   Solve Maze gives the player three options.
   1. Solve Manually
   - Teleports the player randomly within the built maze.
   2. Show Escape Route
   - Shows the player a route to escape the maze.
   3. Back
   - Returns to main menu
4. Show Team Information
   - Displays the team members responsible for creating the program.
5. Exit
   - Reverts any changes made in the game and stops the program.

## Task Allocation
1. Menu Navigation
   - `DameerP` (Merged in main)
   - `21447sadf` (Merged in main)
   - `LabibaShaikh` (Done in "Labiba_menu" branch)
   - `DevlynJB` (Done in "Devlyn_menu" branch)
NOTE: Each member contributed to the creation of the main menu, which is displayed in their respective branches.
Dameer's and Sadf's main menus are the main menus that were combined into main because they handle errors correctly and integrate effectively with the rest of the program.
2. Reading maze information from Terminal and data structurer for holding maze
   - `DameerP` (Merged in main)
   - `DevlynJB` (Done in "Devlyn_menu" branch)
NOTE: Dameer's code is merged to main because it offers great code strucutre and compliments well with the rest of the program.
3. Flattening the terrain
   - `DameerP` (Done in "dameer_menu" branch)
   - `21447sadf` (Merged in main)
NOTE: Sadf's code is merged to main because it offers greater improvements and effectiveness.
4. Building maze in MineCraft
   - `DameerP` (Merged in main)
   - `21447sadf` (Merged in main)
NOTE: While both is merged to main, the primary code used for building the maze is Sadf's as it offers greater efficiency and improvements.
5. Player placement (manual solve)
   - `DameerP` (Merged in main)
NOTE: Dameer is responsible for this task and therefore it is merged to main.
6. Random Maze generation algorithm (Recursive back tracking)
   - `21447sadf` (Merged in main)
   - `LabibaShaikh` (Done in "Labiba_menu" branch)
NOTE: ...
7. Show path to exit (Wall-follower)
   - `21447sadf` (Merged in main)
   - `DevlynJB` (Merged in main)
NOTE: ...
8. Undo Modifications to the world (clean-up)
   - `DameerP` (Done in "dameer_menu" branch)
   - `21447sadf` (Merged in main)
NOTE: Sadf's code is merged to main because it fixed the issues that was present in Dameer's code. 
An example issue that is fixed with Sadf's code is when another maze is generated it will clean the first maze and then generate the new one successfully.
9. Enhancement 1
   - `DevlynJB` (EDIT BRACKET)
NOTE: ...
10. Enhancement 2
   - `21447sadf` (EDIT BRACKET)
   - `LabibaShaikh` (EDIT BRACKET)
NOTE: ...

## Other Tasks
11. Test Cases
   - `DameerP` (Merged in main)
   - `21447sadf` (Merged in main)
   - `LabibaShaikh` (Merged in main)
   - `DevlynJB` (Merged in main)
NOTE: Each member contributed to writing test cases for the program.
12. [Any other relevent task]
   - ...
# **AdaShip Project**

**1. Challenge Outline**

**Summary and review of the problem** 

*AdaShip Program* is a computer program adaptation of the well known Battleship game. 
Each of the two players will have a given board and a collection of boats of different lengths that they can place on their board. 
They will then take turns to try and hit their opponent's boats. If the targeted point on the board is part of a boat, they record a 'hit', otherwise they record a 'miss'.
Once all points of a boat are hit, the boat is recorded to be sunk. The game ends when one player sinks all of he's opponent's boats.

#### Tasks:
- [X] First version of a game working
    - [x] I can read the configuration from the adaship_config.ini file
    - [x] User can see the menu and select “One player vs Computer” or “Quit”
    - [x] When selecting “One player vs Computer” from the menu the user can see a board
    - [x] Print an opponent board
    - [x] Move struct boat from config header to a boat header so all classes can import it
    - [x] Replace the boat struct with a map<string,int> to hold the data about boats
    - [x] Board class gets all info from GameController and prints 2 boards
    - [x] GameController creates players - > players take a board objects with two grids -> grids have a list of ships
    - [x] Can setup ships on boards
    - [x] Can play with two human players
- [] Add required functionalities from assignment
    - [] Add AI player
    - [] Add autoplacing for ships 
    
    
    
    
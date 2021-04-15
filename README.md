# **AdaShip Project/ Mirela Mariana Stoiovici**

github: https://github.com/marianastoiovici/AdaShip01
replit: https://replit.com/@mstoiovici/AdaShip01-1

**1. Challenge Outline**


*AdaShip Program* is a computer programme adaptation of the well known Battleship game. 
Each of the two players will have a given board and a collection of boats of different lengths that they can place on 
their board. They will then take turns to try and hit their opponent's boats. If the targeted point on the board is part
of a boat, they record a 'hit', otherwise they record a 'miss'.
Once all points of a boat are hit, the boat is recorded to be sunk. The game ends when one player sinks all of he's 
opponent's boats.

**Work plan**

In order to achieve this challenge, my original approach was to explore different data structure types to hold both the 
configuration  data and the main models of the programme. 
I made sure I read the configuration file correctly and stored the boards sizes in integer data types and a vector of 
struct data type for the boats. The same vector of boats would have been further passed to GameController and onto the 
Board. 
The initial focus was on getting the configuration data, having a GameController class that would control the 
entire game programme and a Board class that would receive the data and display a proper grid on the console.

Below is a breakdown of the general tasks that were planned and implemented, and a class diagram that was used to clarify 
the structure of the overall project.

**Breakdown of tasks to complete:**
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
- [x] Add required functionalities from assignment
    - [x] Clearly indicate the current non-placed and placed ships
    - [x] Add AI player
    - [x] Add autoplacing for ships 
   
- [] Bugs
    - [x] Fix board to display ships differently
    - [x] Fix board to display columns up to 25 (entire alphabet)
    - [] Fix board to display columns up to 80
    - [x] Fix boat placement for coordinate 6H instead of H6
    - [x] Press Enter to let other player take its turn -> Press Enter to let "player 1/2" take its turn
    - [x] Fix Player menu to let second player use it (switch from using the player's turn)


**Class diagram:**
https://screenshot.googleplex.com/3EVHvUanFr5uJCq

**2. Development approach**
Since my approach was more of a try and fail one, the choice of some of the data structure types proved to not be 
the best. The vector of structs to hold the boat data was soon replaced with a
map of string and int (where the string would be the boat name and the int the boat's length). This new map was 
populated with data from the configuration file and passed onto all other objects. One of the downsizes of using this 
type of data structure was that it was storing the ordered version of the configuration data.

I used an agile approach for this challenge and changed the implementation of the programme often, in order to fit my 
new requirements or to fix the validation bugs.
Since the focus was initially on mostly the board, this model was designed to store all the relevant information. Each 
Player object would have it's own board object, and the board object would mostly store all the needed functionalities 
(a view of his own grid, a view of his opponent's grid, a list with his ships, functionalities to place ships manually 
or automatically, functionalities for validating the placing of ships on the grid etc.). 

Outside the board, a separate class to store the ship entity was designed. 
The Ship class would store all data defining a ship (name, length, damage counter, identifier character to 
differentiate it on the board from the other ship objects, a boolean to store if the ship object is placed on the board
or not and a string pointer to store the list of coordinates which basically defines the ship).
**2.1. Implemented features** 
- [x] User menu to control the game
- [x] Human player menu to control his turn
- [x] One player vs computer game
- [x] Player vs player game
- [x] Place ship manually
- [x] Place ship automatically
- [x] Reset the board
- [x] Option to give turn to next player
- [x] Board with sizes up to 26
- [x] Add more boats to the configuration file
- [x] Game over feature

    
**3. Quality assurance** 
In terms of quality assurance, I used an approach of continued manual testing throughout the development stage.
Each new added feature was tested manually by running the programme and observing the flow and checking if any already 
implemented feature would break.
This testing step involved a good part of the time allocated for the overall implementation since I needed to use 
debugging tools to find the breakages.
   
**4. Object oriented Programming** 
I used an object-oriented approach and designed the whole project as a collection of separate classes. All models have 
their own class with field members to store the data and function members to provide different functionality. 
Additional class to store static functionality to be used by all models was added later in the 
development stage. This helped maintain a cleaner code throughout the models.
Being new to C++, the OOP approach for this assignment helped me learn more about overloaded constructors and how to 
control the access to the members of a class. Also, an OOP approach implemented from the design stage contributes hugely
to easier implementation of new added features to a programme.

    
**4. Reflective review**  
At the end of my project, there was a cleanup phase of the overall implementation. This step helped getting a better
picture of what went well and what still needs to be improved.
Although the programme compiles and runs correctly, there are several things that still need to be improved.

1. Currently, the algorithm used to get a random coordinate to place a ship on the board, or to shoot a target is not 
efficient. It is basically getting a random coordinate and then checking if that specific location is available on board
, the same as how a manual coordinate would be validated for collision. And this process takes would take too much time 
if there will be extra ships added to the configuration file.
Efficiency could be achieved if the algorithm would already know which tiles are still available on the board
and choose a random target only from those ones.

2. Board with sizes over the length of the alphabet
Even though currently, my board can display tiles of up to 80 x80, the naming of the columns is not correct above the 
length of the alphabet. So, for more than 26 columns, displaying the column names and, of course, getting the validation 
for the targets above the 26th column should be fixed.


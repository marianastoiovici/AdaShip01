#include <string>
#include <vector>
#include <map>
using namespace std;


#include "Config.h"
#include "Board.h"


//Creates and sets up the game, controlling the program.
class GameController {
  private:
    int rows;
    int columns;
//    vector<Ship::boat> boats;
    map<string,int> boats;

    void startGame();
    void quit();

  public:
    // Constructor method for GameController.
    GameController(Config config);

    // Menu method to give access to private action methods
    void menu();
};
#include <string>
#include <vector>
using namespace std;

#include "Config.h"

//Creates and sets up the game, controlling the overall program.
class GameController {
  private:
    int rows;
    int columns;
    vector<boat> boats;

    void startGame();
    void quit();

  public:
    // Constructor method for GameController.
    GameController(Config config);

    // Menu method to give access to private action methods
    void menu();
};
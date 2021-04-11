#include <string>
#include <vector>
#include <map>
using namespace std;


#include "Config.h"
#include "Player.h"


//Creates and sets up the game, controlling the program.
class GameController {
  private:
    int rows;
    int columns;
    map<string,int> configBoats;

    Player* player_1;		//player object for player1
	Player* player_2;		//player object for player2
	int player_1Turn; //true if player1 turn, false if player2 turn
	bool gameOver;	//game over to stop the while loop once the game ends

    void setUpGame();
    void quit();

  public:
    // Constructor method for GameController.
    GameController(Config config);

    ~GameController();

    void menu();
	void shoot(string coordinate);
	void play();
	bool checkGameOver(Player* player);
	void pause();
};
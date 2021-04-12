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

    Player* player_1{};		//player object for player1
	Player* player_2{};		//player object for player2
	int player_1Turn{}; //true if player1 turn, false if player2 turn
	bool gameOver = false;	//game over to stop the while loop once the game ends

    void startGame(bool ai);
    static void quit();

  public:
    // Constructor method for GameController.
    explicit GameController(Config config);

    ~GameController();

  [[noreturn]] void menu();
	void shoot(const string& coordinate);
	void play(bool ai);
	void checkGameOver(Player* player);
	static void pause();
};
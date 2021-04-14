#include <string>
#include <vector>
#include <map>
using namespace std;

#include "Config.h"
#include "Player.h"

enum GameOptions {
    Menu_Invalid,
    Menu_Option1,
    Menu_Option2,
    Menu_Quit
};

enum PlayerOptions {
    Player_OptionInvalid,
    Player_Option1,
    Player_Option2,
    Player_Option3,
    Player_Reset,
    Player_Quit,
};


//Creates and sets up the game, controlling the program.
class GameController {
 private:
  int rows;
  int columns;
  map<string, int> configBoats;
  GameOptions resolveOption(string input);
  PlayerOptions resolvePlayerOption(string input);

  Player* player_1{};        //player object for player1
  Player* player_2{};        //player object for player2
//  static int player_1Turn; //true if player1 turn, false if player2 turn
  bool
      gameOver = false;    //game over to stop the while loop once the game ends

  void startGame(bool isGameWithAI);
  static void quit();
  void getPlayerMenu(Player* player, int turn);
  void setupPlayer(Player* player, int turn);

 public:
   int player_1Turn; //true if player1 turn, false if player2 turn
  map<string, int> alphaLookup_;
  // Constructor method for GameController.
  explicit GameController(Config config);

  ~GameController();

  [[noreturn]] void menu();
  void shoot(const string& coordinate);
  void play(bool ai, map<string, int> map1);
  void checkGameOver(Player* player);
  int pause(int turn);
//  void setPlayer1_Turn(int value);


  string columnToString(int column);
  void initialiseLookup();
};
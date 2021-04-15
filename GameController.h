#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <iostream>
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


static const char *const INVALID_MENU_OPTION = "Please enter a valid option.\n\n";

//GameController creates and sets up the game, controlling the program.
class GameController {
private:
    int rows;
    int columns;
    map<string, int> configBoats;
    Player *player_1{};        //player object for player1
    Player *player_2{};        //player object for player2
    bool gameOver = false;    //game over to stop the while loop once the game ends

    void startGame(bool isGameWithAI);

    static void quit();

    void getPlayerMenu(Player *player, int turn);

    void setupPlayer(Player *player, int turn);

    map<string, int> charactersLookup;

    GameOptions resolveOption(string input);

    PlayerOptions resolvePlayerOption(string input);

public:

    // Constructor for GameController.
    explicit GameController(Config config);

    ~GameController();

    [[noreturn]] void menu();

    int player_1Turn; //true if player1 turn, false if player2 turn

    void shoot(const string &coordinate);

    void play(bool ai, map<string, int> map1);

    void checkGameOver();

    void pause(int turn);

    string columnToString(int column);

    map<string, int> initialiseLookup();

    bool isHumanPlayerTurn() const;
};

#endif
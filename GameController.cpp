#include <iostream>
//#include "algorithm" //for transform
using namespace std;

#include "GameController.h"


// Constructor for GameController.
GameController::GameController(Config config) {
    rows = config.getRows();
    columns = config.getColumns();
    configBoats = config.getShipsToPlace();
    charactersLookup = initialiseLookup();
}

GameController::~GameController() {
    delete player_1;
    delete player_2;
}

// Display the menu
[[noreturn]] void GameController::menu() {
    cout << "\nWelcome to AdaShip Game!\n";
    while (true) {
        // display the options and get user's input
        string userInput;
        cout << "\nPlease select one of the following options: \n";
        cout << "\t1 - One player v computer game\n";
        cout << "\t2 - Two player game\n";
        cout << "\tq - Quit\n";
        getline(cin, userInput);
        switch (resolveOption(userInput)) {
            case Menu_Option1:
                startGame(true);
                break;
            case Menu_Option2:
                startGame(false);
                break;
            case Menu_Quit:
                quit();
                break;
            case Menu_Invalid:
                cout << INVALID_MENU_OPTION;
            default:;
        }
    }
}

void GameController::getPlayerMenu(Player *player, int playerTurn) {
    while (player_1Turn) {
        string userInput;
        cout << "\nWhat would you like to do: \n";
        if (!player->allShipsPlaced()) {
            cout << "\t1 - Place available ships automatically\n";
            cout << "\t2 - Place ships manually\n";
        }
        if (player->allShipsPlaced()) {
            cout << "\t3 - Give turn to other player\n";
        }
        cout << "\t4 - Reset your board\n";
        cout << "\tq - Quit\n";
        getline(cin, userInput);
        switch (resolvePlayerOption(userInput)) {
            case Player_Option1:
                if (player->allShipsPlaced()) {
                    cout << INVALID_MENU_OPTION;
                    break;
                }
                player->getBoard()->placeAllShipsAutomatically();
                break;
            case Player_Option2:
                if (player->allShipsPlaced()) {
                    cout << INVALID_MENU_OPTION;
                    break;
                }
                player->getBoard()->placeAllShipsManually();
                break;
            case Player_Option3:
                if (!player->allShipsPlaced()) {
                    cout << INVALID_MENU_OPTION;
                    break;
                }
                pause(playerTurn);
                break;
            case Player_Reset:
                player->getBoard()->initializeBoard();
                player->getBoard()->printShips();
                break;
            case Player_Quit:
                quit();
                break;
            case Player_OptionInvalid:
                cout << INVALID_MENU_OPTION;
            default:;
        }
    }
}

void GameController::setupPlayer(Player *player, int turn) {
    if (turn == 1) {
        cout << "\n\033[1;32m Player 1 place your ships\033[0m\n";
    } else {
        cout << "\n\033[1;32m Player 2 place your ships\033[0m\n";
    }
    player->getBoard()->initializeBoard();
    player->getBoard()->printShips();
    getPlayerMenu(player, turn);
}


// Start a game
void GameController::startGame(bool isGameWithAI) {
    //set first turn to player 1
    player_1Turn = 1;
    cout << "\n\t Setting up the game! " << "\n";

    // Setup phase
    player_1 = new Player(rows, columns, configBoats, charactersLookup);
    setupPlayer(player_1, player_1Turn);

    player_2 = new Player(rows, columns, configBoats, charactersLookup);
    if (isGameWithAI) {
        cout << "\n" << "AI places ships " << "\n";
        player_2->getBoard()->initializeBoard();
        player_2->getBoard()->placeAllShipsAutomatically();
        if (isHumanPlayerTurn()) {
            cout << "Press Enter to let AI take its turn: ";
        } else {
            cout << "Press Enter to let other player take its turn: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        pause(0);
    } else {
        setupPlayer(player_2, player_1Turn);
    }
    cout << "\n\033[1;31mPlayers are set. It's time to shoot your targets. Good luck!\033[0m"
         << "\n";
    //Play phase
    play(isGameWithAI, charactersLookup);
}

// Quit the game
void GameController::quit() {
    cout << "\nYou chose to quit the game. See you later !\n";
    exit(EXIT_SUCCESS);

}

void GameController::play(bool ai, map<string, int> alphaLookup_) {
    while (!gameOver) {
        try {
            string target;
            if (isHumanPlayerTurn()) {
                cout << "\n\n \033[1;31mPlayer 1's turn to shoot!\033[0m" << "\n";
                player_1->getBoard()->printMyGrid();
                player_1->getBoard()->printOpponentGrid();
                string coordinate = Helpers::getInput("Where would you like to shoot: ");
                target = Helpers::getCoordinate(coordinate, alphaLookup_, rows);
                if (target == INVALID_COORDINATE) {
                    cout << "\n\033[1;31mInvalid coordinate! Please try again.\033[0m\n";
                }

            } else {
                if (ai) {
                    cout << "\n\n \033[1;31mAi's turn to shoot!\033[0m" << "\n";
                    player_2->getBoard()->printMyGrid();
                    player_2->getBoard()->printOpponentGrid();

                    target = Helpers::getRandomCoordinate(rows, columns);
                } else {
                    cout << "\n\n \033[1;31mPlayer 2's turn to shoot!\033[0m" << "\n";
                    player_2->getBoard()->printMyGrid();
                    player_2->getBoard()->printOpponentGrid();
                    string coordinate = Helpers::getInput("Where would you like to shoot: ");
                    target = Helpers::getCoordinate(coordinate, alphaLookup_, rows);
                }
                if (target.length() != 2) {
                    cout << "\n\033[1;31mInvalid coordinate! Please try again.\033[0m\n";
                }
            }

            shoot(target);
            if (!gameOver) {
                if (isHumanPlayerTurn()) {
                    cout << "Press Enter to let AI take its turn: ";
                } else {
                    cout << "Press Enter to let other player take its turn: ";
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                pause(player_1Turn);
            }
            cout << "After shoot, the player should be changed" << "\n";
        }
        catch (runtime_error &rte) {
            cout << rte.what();
        }
    }

}

bool GameController::isHumanPlayerTurn() const { return player_1Turn == 1; }

void GameController::shoot(const string &coordinate) {
    bool hit = false;

    if (player_1Turn) {
        hit = player_2->getShot(coordinate); //check player_2 has a ship at the location or not
        player_1->shootCoordinate(coordinate, hit); //update hit marker for player_1

        cout << "Boards updated for Player 1\n";
        player_1->getBoard()->printMyGrid();
        player_1->getBoard()->printOpponentGrid();
        checkGameOver();
    } else {
        hit = player_1->getShot(coordinate);
        player_2->shootCoordinate(coordinate, hit);

        cout << "Boards updated for Player 2\n";
        player_2->getBoard()->printMyGrid();
        player_2->getBoard()->printOpponentGrid();
        checkGameOver();
    }
}

void GameController::checkGameOver() {
    if (player_1Turn) {
        int numberOfShips = player_2->getBoard()->getNumberOfShips();
        int sunkedShips = player_2->getBoard()->sunkedShips;

        if (sunkedShips == numberOfShips) {
            gameOver = true;
            cout << "PLAYER 1 WINS!\n";
        }
    } else {
        int numberOfShips = player_1->getBoard()->getNumberOfShips();
        int sunkedShips = player_1->getBoard()->sunkedShips;
        if (sunkedShips == numberOfShips) {
            gameOver = true;
            cout << "PLAYER 2 WINS!\n";
        }
    }
}

//Method to switch turns between players
void GameController::pause(int turn) {
    cout << "\n\nSwitched turns\n\n";
    if (turn == 1) {
        player_1Turn = 0;
    } else {
        player_1Turn = 1;
    }
}

string GameController::columnToString(int column) {
    const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string alpha = "";

    if (column > 26) {
        alpha += alphabet[(column - 1) / 26 - 1];
    }
    alpha += alphabet[(column - 1) % 26];
    return alpha;
}

map<string, int> GameController::initialiseLookup() {
    map<string, int> charactersLookup;
    for (int i = 1; i <= columns; i++) {
        charactersLookup[columnToString(i)] = i;
    }
    return charactersLookup;
}

GameOptions GameController::resolveOption(std::string input) {
    if (input == "1") return Menu_Option1;
    if (input == "2") return Menu_Option2;
    if (input == "q" || input == "Q") return Menu_Quit;
    return Menu_Invalid;
}

PlayerOptions GameController::resolvePlayerOption(std::string input) {
    if (input == "1") return Player_Option1;
    if (input == "2") return Player_Option2;
    if (input == "3") return Player_Option3;
    if (input == "4") return Player_Reset;
    if (input == "q" || input == "Q") return Player_Quit;
    return Player_OptionInvalid;
}
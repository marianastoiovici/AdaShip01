#include <iostream>
#include "algorithm" //for transform
#include <iomanip>
//#include <utility>
using namespace std;

#include "GameController.h"

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



// Constructor for GameController.
GameController::GameController(Config config) { // TODO review instance variables
  rows = config.getRows();
  columns = config.getColumns();
  configBoats = config.getShipsToPlace();
}

GameController::~GameController() {
  delete player_1;
  delete player_2;
}
// Display the menu
[[noreturn]] void GameController::menu() {
  cout << "\nWelcome to AdaShip Game!\n";
  //TODO: fix loop
  while (true) {
    // display the options and get user's input
    string userInput;
    cout << "\nPlease select one of the following options: \n";
    cout << "\t1 - One player v computer game\n";
    cout << "\t2 - Two player game\n";
    cout << "\tq - Quit\n";
    getline(cin, userInput);
    switch (resolveOption(userInput)) {
      case Menu_Option1:startGame(true);
        break;
      case Menu_Option2:startGame(false);
        break;
      case Menu_Quit:quit();
        break;
      case Menu_Invalid: cout << "Please enter a valid option.\n\n";
      default:;
    }
  }
}


void GameController::getPlayerMenu(Player* player) {
  while (true) {
    // display the options and get user's input
    string userInput;
    cout << "\nWhat would you like to do: \n";
    cout << "\t1 - Place available ships automatically\n";
    cout << "\t2 - Place ships manually\n";
    cout << "\t3 - Reset your board\n";
    cout << "\t4 - Give turn to other player\n";
    cout << "\tq - Quit\n";
    getline(cin, userInput);
    switch (resolvePlayerOption(userInput)) {
      case Player_Option1:player->getBoard()->placeAllShipsAutomatically();
        break;
      case Player_Option2:player->getBoard()->placeShipManually();
        break;
//      case Player_Reset:player->getBoard().resetBoard();
//        break;
      case Player_Option3:pause(); // TODO:: this should switcgh turns too
        break;
      case Player_Quit:quit();
        break;
      case Menu_Invalid: cout << "Please enter a valid option.\n\n";
      default:;
    }
  }
}


  /** Converts the given column number to its Excel-style representation. */
string GameController::columnToString(int column) {
  const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  string alpha = "";
  // if the number is above 26, then an additional character (representing the
  // integer quotient when divided by 26) is prepended
  if (column > 26) {
    alpha += alphabet[(column - 1) / 26 - 1];
  }
  // the final character represents the remainder when divided by 26
  alpha += alphabet[(column - 1) % 26];
  return alpha;
}

/** Populates the mapping from Excel-style column names to column numbers. */
  void GameController::initialiseLookup() {
    // populate an 'alpha to column number' lookup map
    for (int i = 1; i <= columns; i++) {
      alphaLookup_[columnToString(i)] = i;
    }
  }

  void GameController::setupPlayer(Player* player, int turn){
    if(turn == 1){
      cout << "\n\033[1;32m Player 1 place your ships\033[0m\n";
    } else {
       cout << "\n\033[1;32m Player 2 place your ships\033[0m\n";
    }
    player->getBoard()->initializeBoard();

    cout <<"ID"<< setw(2) <<"- " << "STATUS"<< setw(2) <<"- "  "SHIP"<< "\n";
    for (int shipIndex = 0; shipIndex < player->getBoard()->getNumberOfShips();
       shipIndex++) {
    Ship ship = player->getBoard()->getShips()[shipIndex];
    cout<< shipIndex << setw(4) << "-  " << ship.isPlaced() <<setw(4) << "-  "<<  ship.getName() << ", " << ship.getLength()<<"\n";// ship.toString
  }
    getPlayerMenu(player);
  }



// Start a game
void GameController::startGame(bool isGameWithAI) {
    initialiseLookup();
  player_1Turn = 1;
  cout << "\n\t Setting up the game! " << "\n";

  player_1 = new Player(rows, columns, configBoats);
  setupPlayer(player_1, player_1Turn);
//  cout << "\n\033[1;32m Player 1 place your ships\033[0m\n";
//  player_1->getBoard()->initializeBoard();
//  for (int shipIndex = 0; shipIndex < player_1->getBoard()->getNumberOfShips();
//       shipIndex++) {
//    player_1->getBoard()->placeShipManually(shipIndex);
//  }
  pause();

  player_2 = new Player(rows, columns, configBoats);
  cout << "\n\033[1;32m Player 2 place your ships \033[0m\n";
  player_2->getBoard()->initializeBoard();
  if (isGameWithAI) {
    for (int shipIndex = 0;
         shipIndex < player_1->getBoard()->getNumberOfShips(); shipIndex++) {
      player_2->getBoard()->placeShipAutomatically(shipIndex);
    }
    pause();
    play(isGameWithAI, alphaLookup_);
  } else {
    for (int shipIndex = 0;
         shipIndex < player_1->getBoard()->getNumberOfShips(); shipIndex++) {
//      player_2->getBoard()->placeShipManually(shipIndex);
    }
    pause();
    play(isGameWithAI, alphaLookup_);
  }
}

// Quit the game
void GameController::quit() {
  cout << "\nYou chose to quit the game. See you later !\n";
  exit(EXIT_SUCCESS);

}

// TODO: give turn as input to refactor function
void GameController::play(bool ai, map<string, int> alphaLookup_) {
  cout
      << "\033[1;31mPlayers are set. It's time to shoot your targets. Good luck!\033[0m"
      << "\n";

  while (!gameOver) {
    try {
      string target = "";
      while (target.length() != 2) {
        if (player_1Turn % 2 == 1) {
          cout << "\n\n \033[1;31mPlayer 1's turn!\033[0m" << "\n";
          player_1->getBoard()->printMyGrid();
          player_1->getBoard()->printOpponentGrid();
          cout << "\n\033[1;31mPlayer 1: \033[0m";
          target = Helpers::getTargetInput(alphaLookup_, rows);

          if (target == INVALID_COORDINATE) {
            cout
                << "Invalid coordinate! Please try again.\n"; //error if user inputs a string which length is not 2
          }

        } else {
          if (ai) {
            cout << "\n\n \033[1;31mAi's turn!\033[0m" << "\n";
            player_2->getBoard()->printMyGrid();
            player_2->getBoard()->printOpponentGrid();
            cout << "\n\033[1;31mAi: \033[0m";
            target = Helpers::getRandomCoordinate(rows, columns);
          } else {
            cout << "\n\n \033[1;31mPlayer 2's turn!\033[0m" << "\n";
            player_2->getBoard()->printMyGrid();
            player_2->getBoard()->printOpponentGrid();
            cout << "\n\033[1;31mPlayer 2: \033[0m";
            //target = Helpers::getTargetInput(nullptr, 0);
          }



// TODO: need to check if target is valid based oon how many columns I have , might be H14, so length is 3
          if (target.length() != 2) {
            cout
                << "Invalid coordinate! Try again.\n";//error if user inputs a string which length is not 2
          }
        }
      }
      shoot(target);
      if (player_1Turn % 2 == 1 && !gameOver) {
        cout << "PLAYER 1 TURN\n";
        player_1->getBoard()->printMyGrid();
        player_1->getBoard()->printOpponentGrid();
        pause();
      } else if (player_1Turn % 2 == 0
          && !gameOver)    //if it is player 2's turn
      {
        cout << "PLAYER 2 TURN\n";

        player_2->getBoard()->printMyGrid();
        player_2->getBoard()->printOpponentGrid();
        pause();
      }

      player_1Turn++; //switch turns
    }
    catch (runtime_error& rte) {
      cout << rte.what();
    }
  }

}

void GameController::shoot(const string& coordinate) // TODO: can add playerTurn param from play()
{
  bool hit = false;

  if (player_1Turn % 2 == 1) //daca este player1 turn
  {
    hit =
        player_2->getShot(coordinate); //check player_2 has a ship at the location or not
    player_1->shootCoordinate(coordinate, hit); //update hit marker for player_1
    checkGameOver(player_2);
  } else {
    hit = player_1->getShot(coordinate);
    player_2->shootCoordinate(coordinate, hit);
    checkGameOver(player_1);
  }
}

void GameController::checkGameOver(Player* player) {
  int numberOfShips = player->getBoard()->getNumberOfShips();
  int sunkedShips = 0;
  while (sunkedShips != numberOfShips) {
    for (int i = 0; i < numberOfShips; i++) {
      if (player->getBoard()->getShips()[i].isSunk()) {
        sunkedShips++;
      }
    }
    {
      gameOver = sunkedShips == numberOfShips;
      if (gameOver) {
        if (player_1Turn % 2 == 1) {
          cout << "PLAYER 1 WINS!\n";
        } else {
          cout << "PLAYER 2 WINS!\n";
        }
      }
      break;
    }
  }
}

void GameController::pause() {
  cout << "Press Enter to let other player take its turn: ";
  cin.ignore(numeric_limits<streamsize>::max(),
             '\n');
}
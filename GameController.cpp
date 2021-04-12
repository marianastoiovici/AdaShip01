#include <iostream>
#include "algorithm" //for transform
using namespace std;

#include "GameController.h"

// Constructor for GameController.
GameController::GameController(Config config) { // TODO review instance variables
  // set number of rows, columns and configBoats
  rows = config.getRows();
  columns = config.getColumns();
  configBoats = config.getBoatsToPlace();
}

GameController::~GameController() {
  delete player_1;        //delete player1
  delete player_2;        //delete player2
}
// Display the menu
[[noreturn]] void GameController::menu() {
  cout << "\nWelcome to AdaShip Game!\n";

  // Show the menu and stop the program when user wants to quit
  //TODO: fix loop
  while (true) {
    // display the options and get user's input
    string userInput;
    cout << "\nPlease select one of the following options: ";
    cout << "\nMenu:\n";
    cout << "\t1 - One player v computer game\n";
    cout << "\tq - Quit\n";
    getline(cin, userInput);
    if (userInput.length() == 1) {
      char choice = userInput[0];
      switch (choice) {
        case '1':setUpGame();
          break;
        case 'q':quit();
          break;
        default: cout << "Please enter a valid option.\n\n";
      }
    } else {
      cout << "Please enter a valid option.\n\n";
    }
  }
}

// Start a game
void GameController::setUpGame() {
  cout << "\n\t Setting up the game! " << "\n";
  Board board(rows, columns, configBoats);

  player_1 = new Player(rows, columns,configBoats);
  player_2 = new Player(rows, columns,configBoats);
  player_1Turn = 1;

  cout << "\nPlayer 1 place your ships\n";        //prompt player1 to place their ships
  player_1->getBoard()->initializeBoard();
//  player_1->getBoard()->setupBoard();//call getBoard and setupBoard from board.cpp to create the two boards for player1
  for ( int shipIndex = 0; shipIndex < player_1->getBoard()->getNumberOfShips(); shipIndex++){
    player_1->getBoard()->placeShipManually(shipIndex);
  }
  pause();
  cout << "\nPlayer 2 place your ships\n";        //promt player2 to place their ships
  player_2->getBoard()->initializeBoard();                    //call getBoard and setupBoard from board.cpp to create the two boards for player2
  pause();
  play();
}

// Quit the game
void GameController::quit() {
  cout << "\nYou chose to quit the game. See you later !\n";
  exit(EXIT_SUCCESS);

}

// TODO: give turn as input to refactor function
void GameController::play() {
  cout<< "Players are set. It's time to sgoot your targets. Good luck!"<< "\n";
  string target;

  while (!gameOver) {
    try {
      target = "";
      while (target.length() != 2) {
        if (player_1Turn % 2 == 1) {
          player_1->getBoard()->printMyGrid();
          player_1->getBoard()->printOpponentGrid();
          cout
              << "Player 1: Where would you like to shoot: "; //print player's board and opponent's board and ask for user a location to shoot

          getline(cin, target);

          transform(target.begin(), target.end(), target.begin(), ::toupper);

          cout << "target: " << target << "\n";

          if (target.length() != 2) {
            cout
                << "Invalid coordinate! Try again.\n"; //error if user inputs a string which length is not 2
          }

        } else {
          player_2->getBoard()->printMyGrid();
          player_2->getBoard()->printOpponentGrid();
          cout
              << "Player 2: Where would you like to shoot: "; //print player's board and opponent's board and ask for user a location to shoot
          getline(cin, target);
          transform(target.begin(),
                    target.end(),
                    target.begin(),
                    ::toupper);    //converts guess to uppercase
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

/*  if (player_1Turn % 2 == 1) {
    player_2->getBoard()->printOpponentBoard();
    player_2->getBoard()->printMyGrid();

    cout << "PLAYER 2 WINS!\n";
  } else {
    player_1->getBoard()->printOpponentBoard();
    player_1->getBoard()->printMyGrid();

    cout << "PLAYER 1 WINS!\n";
  }*/

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

void GameController::pause()
{
  cout << "Press Enter to let other player take its turn: ";
  cin.ignore(numeric_limits<streamsize>::max(),
             '\n');
}
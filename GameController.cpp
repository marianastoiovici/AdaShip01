#include <iostream>
#include <string>
#include "algorithm" //for transform

using namespace std;

#include "GameController.h"


// Constructor for GameController.
GameController::GameController(Config config) {
  // set number of rows, columns and boats
  rows = config.getRows();
  columns = config.getColumns();
  boats = config.getBoatsToPlace();
}

// Display the menu
void GameController::menu() {
  cout << "\nWelcome to AdaShip Game!\n";

  // Show the menu and stop the program when user wants to quit
  //TODO: fix loop
  while (true) {
    // display the options and get user's input
    string userInput = "";
    cout << "\nMenu:\n";
    cout << "\t1 - One player v computer game\n";
    cout << "\tq - Quit\n";
    cout << "\nPlease select one of the following options: ";
    getline(cin, userInput);
    if (userInput.length() == 1) {
      char choice = userInput[0];
      switch (choice) {
        case '1':
          startGame();
          break;
        case 'q':
          quit();
          break;
        default: cout << "Please enter a valid option.\n\n";
      }
    } else {
      cout << "Please enter a valid option.\n\n";
    }
  }
}

// Start a game
void GameController::startGame() {
  cout<< "\n\t Starting the game! " << "\n";
  Board board(rows, columns, boats);
  board.printMyBoard();
  board.printOpponentBoard();

  cout<< "Board: " << rows << " x " << columns<< "\n";
  for (const auto&[name, length] : boats){
    cout<< "Boat: "<<  name <<", " << length << "\n";
  }
}

// Quit the game
void GameController::quit() {
    cout << "\nYou chose to quit the game. See you later !\n";
    exit(EXIT_SUCCESS);

}
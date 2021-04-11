#include "Board.h"
#include <iomanip>
#include <sstream>
#include <limits>
#include "algorithm" //for transform
using namespace std;

Board::Board(int rows, int columns, map<string, int> ships) {
  this->rows = rows;
  this->columns = columns;
  this->ships = ships;
  this->numberOfShips = ships.size();

  blueTilde = "\033[1;36m~\033[0m";    //sets the color of ~ to blue
  redHit = "\033[1;31mX\033[0m";    //sets the color of X to red
  whiteMiss = "\033[1;37mO\033[0m";        //sets the color of O to white
//  TODO: differentiate ships on board?
  ship = "\033[1;32m∆\033[0m";    //sets the color of ship (∆) to green

//  initialize board with all tiles empty
  for (int i = 0; i < rows;
       i++) {
    for (int j = 0; j < columns; j++) {
      myBoard[i][j] = blueTilde;
      opponentBoard[i][j] = blueTilde;
    }
  }
}

void Board::printMyBoard() {    //prints the current player's board
  cout << "\t\t\tYour board\n";
  cout << setw(5);
  for (int i = 0; i < columns; i++) {
    cout << columnNames[i] << "\t";    //prints the column names (A-J)
  }
  cout << endl;

  for (int x = 0; x < rows; x++) { //number coordinates
    if (x == rows - 1) {
      cout << x + 1;
    } else {
      cout << setw(2) << x + 1;
    }
    for (int y = 0; y < columns; y++) {
      cout << "\t" << myBoard[x][y];
    }
    cout << "\n";
  }

}

//prints the current player's view of their opponents side
void Board::printOpponentBoard() {
  std::cout << "\n\t\t\tOpponent's board\n";
  cout << setw(5);
  for (int i = 0; i < columns; i++) {
    cout << columnNames[i] << "\t";    //prints the column names (A-J)
  }
  cout << endl;

  for (int x = 0; x < rows; x++) { //row coordinates
    if (x == rows - 1) {
      cout << x + 1;
    } else {
      cout << setw(2) << x + 1;
    }
    for (int y = 0; y < columns; y++) {
      cout << "\t" << opponentBoard[x][y];
    }
    cout << "\n";
  }

}


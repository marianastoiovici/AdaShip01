#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <map>
using namespace std;

#include "Ship.h"

#define MAX_ROWS 80
#define MAX_COLUMNS 80

// The Board class represents a general game board
class Board {
 private:
  int rows;
  int columns;
//    vector<boat> boats;
  map<string, int> ships;
  int numberOfShips;

  string myGrid[MAX_ROWS][MAX_COLUMNS]; // check https://stackoverflow.com/questions/3749660/how-to-resize-array-in-c
  string opponentGrid[MAX_ROWS][MAX_COLUMNS];
  //TODO: improve printing chars for columns when >10
//  string columnNames = "ABCDEFGHIJ";
  vector<string> columnNames = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
  int rowIndex{};
  int columnIndex{};

  // types of tiles	TODO: improve with an enum to store these types
  string blueTilde = "\033[1;36m~\033[0m";    //sets the color of ~ to blue
  string redHit = "\033[1;31mX\033[0m";    //sets the color of X to red
 string whiteMiss = "\033[1;37mO\033[0m";        //sets the color of O to white
//  TODO: differentiate ships on board?
  string ship = "\033[1;32m∆\033[0m";    //sets the color of ship (∆) to green

  Ship* myShips = nullptr;

 public:
  Board();
  // Board Constructor
  Board(int rows, int columns, const map<string, int>& ships);

  ~Board();

  void printOpponentGrid();
  void printMyGrid();

  int getNumberOfShips() const;
  void setupBoard();
  void convertCoordinateToIndexes(string coordinate);
  void updateOpponentGrid(string coordinate, bool wasHit);
  bool updateMyGrid(const string& userGuess);
  bool withinBoundary(const string& userGuess);
  bool noHorizontalCollision(string userGuess, int shipLength);
  bool noVerticalCollision(string userGuess, int shipLength);
  Ship* getShips() const;
  void printShips();
  string getCoordinateInput(int index);
  string getDirectionInput(int index);
  void createListOfShips();
  bool isValidHorizontalDirection(const string& direction) const;
  bool isValidVerticalDirection(const string& direction) const;
};
#endif


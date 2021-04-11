#ifndef BOARD_H
#define BOARD_H

#include <iostream>
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

  string myBoard[MAX_ROWS][MAX_COLUMNS]; // check https://stackoverflow.com/questions/3749660/how-to-resize-array-in-c
  string opponentBoard[MAX_ROWS][MAX_COLUMNS];
  //TODO: improve printing chars for columns when >10
  string columnNames = "ABCDEFGHIJ";
  int rowIndex{};
  int columnIndex{};

  // types of tiles	TODO: improve with an enum to store these types
  string blueTilde; // Empty tile
  string redHit; // Hit tile
  string whiteMiss; // Missed tile
  string ship; // Ship tile

  Ship* myShips = nullptr;

 public:
  Board();
  // Board Constructor
  Board(int rows, int columns, const map<string, int>& ships);

  ~Board();

  void printOpponentBoard();
  void printMyBoard();

  int getNumberOfShips() const;
  void setupBoard();
  void convertCoordinateToIndexes(string coordinate);
  void updateOpponentBoard(string coordinate, bool wasHit);
  bool updateMyBoard(const string& userGuess);
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


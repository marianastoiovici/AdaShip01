#include <iostream>
#include <map>

#include "Board.h"

class Player {
 private:
  Board* board = nullptr;

 public:
  Player(int rows, int columns, map<string, int> boats);
  ~Player();
  void shootCoordinate(string coordinate, bool hit);
  bool getShot(string coordinate);
  Board* getBoard() const;
};
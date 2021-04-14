#include <iostream>
#include <map>

#include "Board.h"

class Player {
private:
    Board *board = nullptr;

public:
    Player(int rows, int columns, const map<string, int> &boats, map<string, int> alphaLookup_);

    ~Player();

    void shootCoordinate(string coordinate, bool hit);

    bool getShot(const string &coordinate);

    Board *getBoard() const;

//  Board* resetBoard() const;
    bool allShipsPlaced();
};
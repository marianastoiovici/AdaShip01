#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

#include "Ship.h"
#include "Helpers.h"

#define MAX_ROWS 80
#define MAX_COLUMNS 80

// The Board class represents a general game board
class Board {
private:
    int rows;
    int columns;
    map<string, int> ships;
    int numberOfShips;


    string myGrid[MAX_ROWS][MAX_COLUMNS]; // check https://stackoverflow.com/questions/3749660/how-to-resize-array-in-c
    string opponentGrid[MAX_ROWS][MAX_COLUMNS];

    int rowIndex{};
    int columnIndex{};

    // types of tiles	TODO: improve with an enum to store these types
    string blueTilde = "\033[1;36m~\033[0m";    //sets the color of ~ to blue
    string redHit = "\033[1;31mX\033[0m";    //sets the color of X to red
    string whiteMiss = "\033[1;37mO\033[0m";        //sets the color of O to white

    Ship *myShips = nullptr;

    map<string, int> alphaLookup_;


public:
    Board();

    // Board Constructor
    Board(int rows, int columns, const map<string, int> &ships, map<string, int> alphaLookup_);

    ~Board();

    void printOpponentGrid();

    void printMyGrid();

    void initializeBoard();

    void placeShipManually(int shipIndex);

    void placeAllShipsManually();

    void placeShipAutomatically(int shipIndex);

    void placeAllShipsAutomatically();

    int getNumberOfShips() const;

    void convertCoordinateToIndexes(string coordinate);

    void updateOpponentGrid(string coordinate, bool wasHit);

    bool updateMyGrid(const string &userGuess);

    bool withinBoundary(const string &userGuess);

    bool noHorizontalCollision(string userGuess, int shipLength);

    bool noVerticalCollision(string userGuess, int shipLength);

    Ship *getShips() const;

    void printShips();


    void createListOfShips();

    bool isValidHorizontalDirection(const string &direction) const;

    bool isValidVerticalDirection(const string &direction) const;

    int sunkedShips;


};

#endif


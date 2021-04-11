#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include <vector>


using namespace std;

#define MAX_ROWS 80
#define MAX_COLUMNS 80


 // The Board class represents a general game board
class Board {
  private:
     int rows;
     int columns;
//    vector<boat> boats;
map<string,int> ships;
int numberOfShips;


	string myBoard[MAX_ROWS][MAX_COLUMNS];
	string opponentBoard[MAX_ROWS][MAX_COLUMNS];
    //TODO: improve printing chars for columns when >10
	string columnNames = "ABCDEFGHIJ";
	int m_rowIndex;
	int m_columnIndex;

    // types of tiles	TODO: improve with an enum to store these types
	string blueTilde; // Empty tile
	string redHit; // Hit tile
	string whiteMiss; // Missed tile
	string ship; // Ship tile




  public:

    // Board Constructor
	Board(int rows, int columns, map<string,int> ships);



    void printMyBoard();
    void printOpponentBoard();

};
#endif


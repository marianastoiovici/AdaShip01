#include <iostream>
#include <string>

 using namespace std;

#define MAX_ROWS 80
#define MAX_COLUMNS 80

 // The Board class represents a general game board
class Board {
  private:
    int rows;
    int columns;

	string myBoard[MAX_ROWS][MAX_COLUMNS];
    //TODO: improve printing chars for columns when >10
	string columnNames = "ABCDEFGHIJ";
	int rowIndex;
	int columnIndex;

    // types of tiles	TODO: improve with an enum to store these types
	string blueTilde; // Empty tile
	string redHit; // Hit tile
	string whiteMiss; // Missed tile
	string ship; // Ship tile


  public:
    // Board Constructor
	Board(int rows, int columns);

	void printMyBoard();
};


#include <iostream>
#include <sstream>

#include <iomanip>
#include <utility>
#include "algorithm" //for transform
using namespace std;

#include "Board.h"

Board::Board(int rows, int columns, const map<string, int>& ships) {
  this->rows = rows;
  this->columns = columns;
  this->ships = ships;
  this->numberOfShips = ships.size();
}

Board::~Board() {
  delete[] myShips;
}

void Board::initializeBoard(){
  //  initialize board with all tiles empty
  for (int indexRows = 0; indexRows < rows; indexRows++) {
    for (int indexColumns = 0; indexColumns < columns; indexColumns++) {
      myGrid[indexRows][indexColumns] = blueTilde;
      opponentGrid[indexRows][indexColumns] = blueTilde;
    }
  }
  printMyGrid();
  createListOfShips();
  printShips();

}

void Board::printMyGrid() {    //prints the current player's board
  cout << "\t\t\t\033[1;32mYour board\033[0m\n";
  cout << setw(5);
  for (int i = 0; i < columns; i++) {
    cout << Helpers::columnNames[i] << "\t";    //prints the column names (A-J)
  }
  cout << endl;

  for (int x = 0; x < rows; x++) { //number coordinates
    if (x == rows - 1) {
      cout << x + 1;
    } else {
      cout << setw(2) << x + 1;
    }
    for (int y = 0; y < columns; y++) {
      cout << "\t" << myGrid[x][y];
    }
    cout << "\n";
  }

}

//prints the current player's view of their opponents side
void Board::printOpponentGrid() {

  std::cout << "\n\t\t\t\033[1;32mOpponent's board\033[0m\n";
  cout << setw(5);
  for (int i = 0; i < columns; i++) {
    cout << Helpers::columnNames[i] << "\t";    //prints the column names (A-J)
  }
  cout << endl;

  for (int x = 0; x < rows; x++) { //row coordinates
    if (x == rows - 1) {
      cout << x + 1;
    } else {
      cout << setw(2) << x + 1;
    }
    for (int y = 0; y < columns; y++) {
      cout << "\t" << opponentGrid[x][y];
    }
    cout << "\n";
  }

}

void Board::convertCoordinateToIndexes(string coordinate) {
  string s;
  if( coordinate.length() > 3 ){
    return;
  }
  else if(coordinate.length() >=2  ) {
    for (int i = 0; i <= Helpers::columnNames.size(); i++) {
      s = coordinate.at(0);
      if (s == Helpers::columnNames[i]) {
        columnIndex = i;
        coordinate.erase(0,1);
        break;
      }
    }

  } else {
    return;
  }
  stringstream ss;
  int number;
  ss<< coordinate;
  ss>> number;
  rowIndex = number - 1; //sets it to the intended column by subtracting 1 to get the proper index
}

bool Board::updateMyGrid(const string& coordinate) {
  convertCoordinateToIndexes(coordinate);    //updates rowIndex and columnIndex based on a given string coordinate
  string tile = myGrid[rowIndex][columnIndex];
  if (tile == blueTilde) {
    myGrid[rowIndex][columnIndex] = whiteMiss;
  } else if (tile != whiteMiss || tile != redHit) {
    myGrid[rowIndex][columnIndex] = redHit;
    // loops through all ships to find the ship with the hit coordinate in order to increase its damage
    for (int i = 0; i < numberOfShips; i++) {
      for (int j = 0; j < myShips[i].getLength(); j++) {
//        cout << myShips[i].getCoordinate(j) << "\n";
        if (myShips[i].getCoordinate(j) == coordinate) {
          myShips[i].increaseDamage();    //add damage counter to that ship
          if (myShips[i].isSunk()) {
            std::cout << "\033[1;32mSHIP SUNK!!!\033[0m\n";
          }
          break;
        }
      }
    }
    return true;    //return true because a ship was hit
  } else if (tile == redHit || tile
      == whiteMiss)    //if tile was already targeted before, user can try again
  {
    throw (std::runtime_error("You already targeted this location! Try again."));
  }
  return false;    //if there were no hits, then this runs and we return false because it was a miss
}

void Board::updateOpponentGrid(string coordinate, bool wasHit) {
  convertCoordinateToIndexes(std::move(coordinate)); // sets row and column indexes to point to given coordinate
  if (wasHit) {
    opponentGrid[rowIndex][columnIndex] = redHit;
  } else {
    opponentGrid[rowIndex][columnIndex] = whiteMiss;
  }
}

bool Board::withinBoundary(const string& coordinate) //checks if given coordinate is within the boundary of the board
{
if( coordinate.length() > 3 ){
  return false;
}
else if(coordinate.length() >=2  ) {
  convertCoordinateToIndexes(coordinate);    // sets row and column indexes to point to given coordinate
  bool isit = (0 <= rowIndex && rowIndex < rows)
        && (0 <= columnIndex && columnIndex < columns);
    return isit;

} else {
  return false;
}
}

void Board::placeShipAutomatically(int index) {

  string coordinate;
  if (!myShips[index].getPlaced()) {
    string direction = Helpers::getRandomDirection();
      bool isValidDirection = false;
      bool isValidCoordinate = false;
      do {
        if (isValidHorizontalDirection(direction)) {
          coordinate = Helpers::getRandomCoordinate(rows, columns);
          while (!isValidCoordinate) {  //runs until the location is valid
            if (noHorizontalCollision(coordinate,myShips[index].getLength())) {
              string temp = coordinate;
              for (int j = 0; j < myShips[index].getLength(); j++) {
                myGrid[rowIndex][columnIndex + j] = myShips[index].getSign();   //set tile to ship
                myShips[index].addCoordinate(temp,
                                             j); // add tempCoordinate to the ships coordinates
                temp[0] = temp.at(0) + 1; // moves to next one
              }
              myShips[index].setPlaced(true);
              printMyGrid();    //prints the updated board
              printShips();
              isValidCoordinate = true;
              isValidDirection = true;
            } else {
              coordinate = Helpers::getRandomCoordinate(rows, columns);
            }
          }

        } else if (isValidVerticalDirection(direction)) {
          coordinate = Helpers::getRandomCoordinate(rows, columns);

          while (!isValidCoordinate) {
            if (noVerticalCollision(coordinate,
                                    myShips[index].getLength())) {
              string temp =
                  coordinate;    //used to store and manipulate tempCoordinate without changing it
              for (int j = 0; j < myShips[index].getLength(); j++) {
                myGrid[rowIndex + j][columnIndex] = myShips[index].getSign();
                myShips[index].addCoordinate(temp, j);
                temp[1] = temp.at(1) + 1;
              }
              myShips[index].setPlaced(true);
              printMyGrid();
              printShips();
              isValidCoordinate = true;
              isValidDirection = true;    //true to exit the while loop
            } else {
              coordinate = Helpers::getRandomCoordinate(rows, columns);
            }
          }
        }

      } while (!isValidDirection);    //runs until the user has inputed "H" or "h" or "V" or "v".

  }
}

void Board::placeShipManually(int index) {
string coordinate;
//TODO: do not ask for direction when ship length is 1
      //("H" or "h" or "V" or "v") horizontal or vertical ship placement
      string direction = Helpers::getDirectionInput(myShips[index].getName());
      bool isValidDirection = false;
      bool isValidCoordinate = false;
      do {
        if (isValidHorizontalDirection(direction)) {
          coordinate = Helpers::getCoordinateInput(myShips[index].getName());
          while (!isValidCoordinate) {  //runs until the location is valid
            if (noHorizontalCollision(coordinate,
                                      myShips[index].getLength())) {
              string temp =
                  coordinate;    //used to store and manipulate userGuess without changing userGuess
              for (int j = 0; j < myShips[index].getLength(); j++) {
                myGrid[rowIndex][columnIndex + j] = myShips[index].getSign();   //set tile to ship
                myShips[index].addCoordinate(temp,
                                             j); // add tempCoordinate to the ships coordinates
                temp[0] = temp.at(0) + 1; // moves to next one
              }
              myShips[index].setPlaced(true);
              printMyGrid();    //prints the updated board
              printShips();
              isValidCoordinate =
                  true;    //sets valid location to true to help break out of loop
              isValidDirection = true;    //true to kick out of while loop
            } else {
              cout << "\n\033[1;31mInvalid location. Try again!\033[0m\n";
              coordinate = Helpers::getCoordinateInput(myShips[index].getName());
            }
          }

        } else if (isValidVerticalDirection(direction)) {
          coordinate = Helpers::getCoordinateInput(myShips[index].getName());

          while (!isValidCoordinate) {
            if (noVerticalCollision(coordinate,
                                    myShips[index].getLength())) {
              string temp =
                  coordinate;    //used to store and manipulate tempCoordinate without changing it
              for (int j = 0; j < myShips[index].getLength(); j++) {
                myGrid[rowIndex + j][columnIndex] = myShips[index].getSign();
                myShips[index].addCoordinate(temp, j);
                temp[1] = temp.at(1) + 1;
              }
              myShips[index].setPlaced(true);
              printMyGrid();
              printShips();
              isValidCoordinate = true;
              isValidDirection = true;    //true to exit the while loop
            } else {
              cout << "\n\033[1;31mInvalid location. Try again!\033[0m\n";
              coordinate = Helpers::getCoordinateInput(myShips[index].getName());
            }
          }
        } else {  //if the input was not "V" or "v"
          cout << "\n\033[1;31mInvalid Direction. Try again!\033[0m\n";
          direction = Helpers::getDirectionInput(myShips[index].getName());
        }
      } while (!isValidDirection);    //runs until the user has inputed "H" or "h" or "V" or "v".
}

bool Board::isValidVerticalDirection(const string& direction) const { return direction == "V" || direction == "v"; }

bool Board::isValidHorizontalDirection(const string& direction) const { return direction == "H" || direction == "h"; }

void Board::createListOfShips() {
  myShips = new Ship[numberOfShips]; // create list of null ship objects

  int shipIndex = 0;
  for (const auto&[name, length] : ships) { // create ship objects and add them to the list of ships
    Ship* shippy = new Ship(name, length);
    myShips[shipIndex] = *shippy; // does this actually points to shippy????
    shipIndex++;
  }
}

void Board::printShips() {
  for (int i = 0; i < numberOfShips; i++) {
    if (myShips[i].getPlaced()) {
      cout << myShips[i].getName() << " of length " << myShips[i].getLength()
           << " is PLACED.\n";
    } else {
      cout << myShips[i].getName() << " of length " << myShips[i].getLength()
           << " is NOT PLACED.\n";
    }
  }
  cout << "\n\n";
}

bool Board::noHorizontalCollision(std::string userGuess, int shipLength) {
  convertCoordinateToIndexes(std::move(userGuess));    //updates rowIndex and columnIndex based on userGuess
  for (int i = 0; i < shipLength; i++) {
    if ((0 <= rowIndex && rowIndex <= rows) && (0 <= columnIndex + i
        && columnIndex + i
            <= columns)) { //checks that all the next right indices are within the bounds
      if (myGrid[rowIndex][columnIndex + i]
          != blueTilde) {   //returns false if at any time the next right indices are not blueTildes
        return false;
      }
    } else {
      return false;    //returns false if any of the right indices are out of bounds
    }
  }
  return true;    //returns true since all the false checks were not hit, so there is no collision that would happen
}

bool Board::noVerticalCollision(std::string userGuess, int shipLength) {
  convertCoordinateToIndexes(std::move(userGuess));    //updates rowIndex and columnIndex based on userGuess
  for (int i = 0; i < shipLength; i++) {
    if ((0 <= rowIndex + i && rowIndex + i <= rows) && (0 <= columnIndex
        && columnIndex
            <= columns)) {   //checks that all the next below indices are within bounds
      if (myGrid[rowIndex + i][columnIndex]
          != blueTilde) {   //returns false if at any time the next below indices are not blueTildes
        return false;
      }
    } else {
      return false;    //returns false if any of the below indices are out of bounds
    }
  }
  return true;    //returns true since all the false checks were not hit, so there is no collision that would happen
}

int Board::getNumberOfShips() const {
  return numberOfShips;
}

Ship* Board::getShips() const {
  return myShips;
}
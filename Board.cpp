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

//  initialize board with all tiles empty
  for (int indexRows = 0; indexRows < rows; indexRows++) {
    for (int indexColumns = 0; indexColumns < columns; indexColumns++) {
      myGrid[indexRows][indexColumns] = blueTilde;
      opponentGrid[indexRows][indexColumns] = blueTilde;
    }
  }
}

Board::~Board() {
  delete[] myShips;
}

void Board::printMyGrid() {    //prints the current player's board
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
      cout << "\t" << myGrid[x][y];
    }
    cout << "\n";
  }

}

//prints the current player's view of their opponents side
void Board::printOpponentGrid() {

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
    for (int i = 0; i <= columnNames.size(); i++) {
      s = coordinate.at(0);
      if (s == columnNames[i]) {
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
  } else if (tile == ship) {
    myGrid[rowIndex][columnIndex] = redHit;
    // loops through all ships to find the ship with the hit coordinate in order to increase its damage
    for (int i = 0; i < numberOfShips; i++) {
      for (int j = 0; j < myShips[i].getLength(); j++) {
//        cout << myShips[i].getCoordinate(j) << "\n";
        if (myShips[i].getCoordinate(j) == coordinate) {
          myShips[i].increaseDamage();    //add damage counter to that ship
          if (myShips[i].isSunk()) {
            std::cout << "SHIP SUNK!!!\n";
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

string Board::getCoordinateInput(int index) {
  string coordinateInput;
  cout << "Enter coordinate of type \'A1\', \'E5\' to place your ship.\n";
  cout << "Enter your left/top most coordinate for " << myShips[index].getName()
       << ": ";
  getline(std::cin, coordinateInput);
  transform(coordinateInput.begin(),
            coordinateInput.end(),
            coordinateInput.begin(),
            ::toupper);    //converts coordinate to uppercase
  return coordinateInput;
}

string Board::getDirectionInput(int index) {
  string directionInput;
  cout << "HORIZONTAL(H/h) OR VERTICAL(V/v) orientation for "
       << myShips[index].getName() << " :";
  getline(std::cin,
          directionInput);    //takes in the user input of horizontal or vertical
  return directionInput;
}

void Board::setupBoard() {
  printMyGrid();
  createListOfShips();
  printShips();

  string coordinate;
  bool isValidCoordinate;

  for (int index = 0; index < numberOfShips; index++) {
    if (myShips[index].getLength() == 1) // you don't need to ask for direction
    {
      do {
        coordinate = getCoordinateInput(index);
//        TODO: fix bug: when length is 1 I don't check for any collisions??
        if (!withinBoundary(coordinate)) { //checks boundary and sets the indexes according to the given oordinate
          std::cout << "\n\033[1;31mInvalid coordinate! Try again.\033[0m\n";
        }
      } while (!withinBoundary(coordinate));    //runs until the user's coordinate is within the boundary

      myGrid[rowIndex][columnIndex] = ship;    //sets the user's guess location to a ship
      myShips[index].addCoordinate(coordinate, 0);

      myShips[index].setPlaced(true);
      printMyGrid();    //prints the newly updated board
      printShips();
    } else // you need to ask for direction before setting the coordinates to ship
    {
      //("H" or "h" or "V" or "v") horizontal or vertical ship placement
      string direction = getDirectionInput(index);
      bool isValidDirection = false;
      bool isValidCoordinate = false;
      do {
        if (isValidHorizontalDirection(direction)) {
          coordinate = getCoordinateInput(index);
          while (!isValidCoordinate) {  //runs until the location is valid
            if (noHorizontalCollision(coordinate,
                                      myShips[index].getLength())) {
              string temp =
                  coordinate;    //used to store and manipulate userGuess without changing userGuess
              for (int j = 0; j < myShips[index].getLength(); j++) {
                myGrid[rowIndex][columnIndex + j] = ship;   //set tile to ship
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
              coordinate = getCoordinateInput(index);
            }
          }

        } else if (isValidVerticalDirection(direction)) {
          coordinate = getCoordinateInput(index);

          while (!isValidCoordinate) {
            if (noVerticalCollision(coordinate,
                                    myShips[index].getLength())) {
              string temp =
                  coordinate;    //used to store and manipulate tempCoordinate without changing it
              for (int j = 0; j < myShips[index].getLength(); j++) {
                myGrid[rowIndex + j][columnIndex] = ship;
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
              coordinate = getCoordinateInput(index);
            }
          }
        } else {  //if the input was not "V" or "v"
          cout << "\n\033[1;31mInvalid Direction. Try again!\033[0m\n";
          direction = getDirectionInput(index);
        }
      } while (!isValidDirection);    //runs until the user has inputed "H" or "h" or "V" or "v".
    }

  }

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
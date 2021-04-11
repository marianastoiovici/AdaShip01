#include <iostream>
#include <iomanip>
#include "algorithm" //for transform
using namespace std;

#include "Board.h"

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

Board::~Board() {
  delete[] myShips;
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

void Board::convertCoordinateToIndexes(string coordinate)
{
  if (coordinate.length() != 2) {
    return; // TODO: resolve bug where userGuess == 1 and program doesn't ask for another coordinate
  } else {
    for (unsigned int i = 0; i < columnNames.length(); i++)   {  // TODO: rowNames.length() returns an unsigned int??
      if (coordinate.at(0) == columnNames.at(i) || coordinate.at(0) == (tolower(columnNames.at(i)))) {
        columnIndex = i;
        break;
      } else {
        columnIndex = 9;
      }
    }
  }

  // convert coordinate at second index to decimal
  int temp = coordinate.at(1) - '0';
  rowIndex = temp - 1; //sets it to the intended column by subtracting 1 to get the proper index
}

bool Board::updateMyBoard(string coordinate)
{
  convertCoordinateToIndexes(coordinate);    //updates rowIndex and columnIndex based on a given string coordinate
  string tile = myBoard[rowIndex][columnIndex];
  if (tile== blueTilde) {
    myBoard[rowIndex][columnIndex] = whiteMiss;
  }
  else if (tile == ship) {
    myBoard[rowIndex][columnIndex] = redHit;
    // loops through all ships to find the ship with the hit coordinate in order to increase its damage
    for (int i = 0; i < numberOfShips; i++) {
      for (int j = 0; j < myShips[i].getLength(); j++) {
        cout<<myShips[i].getCoordinate(j)<<"\n";
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
  }
  else if (tile == redHit || tile == whiteMiss)    //if tile was already targeted before, user can try again
  {
    throw (std::runtime_error("You already targeted this location! Try again."));
  }
  return false;    //if there were no hits, then this runs and we return false because it was a miss
}

void Board::updateOpponentBoard(string coordinate,bool wasHit) {
  convertCoordinateToIndexes(coordinate); // sets row and column indexes to point to given coordinate
  if (wasHit) {
    opponentBoard[rowIndex][columnIndex] = redHit;
  } else {
    opponentBoard[rowIndex][columnIndex] = whiteMiss;
  }
}

bool Board::withinBoundary(string coordinate) //checks if given coordinate is within the boundary of the board
{
  if (coordinate.length() != 2) {
    return false;
  }
  else {
    convertCoordinateToIndexes(coordinate);    // sets row and column indexes to point to given coordinate
    if ((0 <= rowIndex && rowIndex <= 9) && (0 <= columnIndex && columnIndex <= 9)) {
      return true;    //if the indices are within the bounds of our board, we return true
    } else {
      return false;    //otherwise, we return false
    }
  }
}

string Board::getCoordinateInput(int index) {
  string coordinateInput;
  cout<< "Enter coordinate of type \'A1\', \'E5\' to place your ship.\n";
  cout << "Enter your left/top most coordinate for "<<  myShips[index].getName() << ": ";
  getline(std::cin, coordinateInput);
  transform(coordinateInput.begin(), coordinateInput.end(), coordinateInput.begin(), ::toupper);    //converts guess to uppercase
  return coordinateInput;
}

string Board::getDirectionInput(int index) {
  string directionInput;
  cout << "HORIZONTAL(H/h) OR VERTICAL(V/v) orientation for " << myShips[index].getName() << " :";
      getline(std::cin,
              directionInput);    //takes in the user input of horizontal or vertical
  return directionInput;
}

void Board::setupBoard() {   //sets up the board
  printMyBoard();

  string temp;


  myShips = new Ship[numberOfShips]; // create list of null ship objects
  int i = 0;
  for (const auto&[name, length] : ships) { // create ship objects and add them to the list of ships
    Ship* shippy = new Ship(name, length);
    myShips[i] = *shippy; // does this actually points to shippy????
    i++;
  }
  printShips(); // print the ships to the player

  string coordinate;
  string userDirection;    //("H" or "h" or "V" or "v") horizontal or vertical ship placement
  bool validLocation;
  bool validDirection; // true if we'll get 'H' or 'h' for horizontal and 'V' or 'v' for vertical

  for (int i=0; i< numberOfShips; i++) {
    if (myShips[i].getLength() == 1) // you don't need to ask for direction
    {
      do {
        coordinate = getCoordinateInput(i);
        if (!withinBoundary(coordinate)) { //checks boundary and sets the indexes according to the given oordinate
          std::cout << "\033[1;31mInvalid coordinate! Try again.\033[0m\n";
        }
      } while (!withinBoundary(coordinate));    //runs until the user's coordinate is within the boundary

      myBoard[rowIndex][columnIndex] = ship;    //sets the user's guess location to a ship
      myShips[i].addCoordinate(coordinate, 0);

      myShips[i].setPlaced(true);
      printMyBoard();    //prints the newly updated board
      printShips();
    } else // you need to ask for direction before setting the coordinates to ship
    {
      userDirection = getDirectionInput(i);
      do {
     string coordinate;
        validDirection =false;    //need to reinitialize to false so that each run through, this loop correclty runs

        if (userDirection == "H" || userDirection == "h") {
          validLocation = false;
          coordinate = getCoordinateInput(i);
          while (!validLocation) {  //runs until the location is valid

            if (noHorizontalCollision(coordinate, myShips[i].getLength())) {
              convertCoordinateToIndexes(coordinate); // sets row and column indexes to point to given coordinate
              temp = coordinate;    //used to store and manipulate userGuess without changing userGuess
              for (int j = 0; j < myShips[i].getLength(); j++) {
                myBoard[rowIndex][columnIndex + j] = ship;   //set tile to ship
                myShips[i].addCoordinate(temp, j); // add coordinate to the ships coordinates
                temp[0] = temp.at(0) + 1; // moves to next one
              }
              myShips[i].setPlaced(true);
              printMyBoard();    //prints the updated board
              printShips();
              validLocation = true;    //sets valid location to true to help break out of loop
              validDirection = true;    //true to kick out of while loop
            } else
            {
              printMyBoard();
              printShips();
              cout << "\033[1;31mInvalid location. Try again!\033[0m\n";
              coordinate = getCoordinateInput(i);
            }
          }

        } else if (userDirection == "V" || userDirection == "v") {
         validLocation = false;
          coordinate = getCoordinateInput(i);

          while (!validLocation) {
            if (noVerticalCollision(coordinate,myShips[i].getLength())) {
              //i think this is already done in noverticall check
              convertCoordinateToIndexes(coordinate); //pushing two int indexes back to orignal spot of user guess
              temp = coordinate;    //used to store and manipulate coordinate without changing it
              for (int j = 0; j < myShips[i].getLength(); j++) {
                myBoard[rowIndex + j][columnIndex] = ship;
                myShips[i].addCoordinate(temp, j);
                temp[1] = temp.at(1) + 1;
              }
               myShips[i].setPlaced(true);
              printMyBoard();    //prints the updated board
              printShips();
              validLocation = true;
              validDirection = true;    //true to kick out of while loop
            } else {
              printMyBoard();    //prints the updated board again and asks the user to try again
              printShips();
              cout << "\033[1;31mInvalid location. Try again!\033[0m\n";
              coordinate = getCoordinateInput(i);
            }
          }
        } else {  //if the input was not "V" or "v"
          cout << "\033[1;31mInvalid Direction. Try again!\033[0m\n";
          printMyBoard();    //prints the board again so that the user can try again
          printShips();
          userDirection = getDirectionInput(i);
        }
      } while (!validDirection);    //runs until the user has inputed "H" or "h" or "V" or "v".
    }

  }

}

void Board::printShips() {
  for (int i=0; i< numberOfShips; i++) {
        if (myShips[i].getPlaced()){
           cout << myShips[i].getName() << " of length " << myShips[i].getLength() << " is PLACED.\n";
        } else {
            cout << myShips[i].getName() << " of length " << myShips[i].getLength() << " is NOT PLACED.\n";
      }
  }
  cout<< "\n\n";
}

bool Board::noHorizontalCollision(std::string userGuess, int shipLength) {
  convertCoordinateToIndexes(userGuess);    //updates rowIndex and columnIndex based on userGuess
  for (int i = 0; i < shipLength; i++) {
    if ((0 <= rowIndex && rowIndex <= 9) && (0 <= columnIndex + i && columnIndex + i <= 9)) { //checks that all the next right indices are within the bounds
      if (myBoard[rowIndex][columnIndex + i]!= blueTilde) {   //returns false if at any time the next right indices are not blueTildes
        return false;
      }
    } else {
      return false;    //returns false if any of the right indices are out of bounds
    }
  }
  return true;    //returns true since all the false checks were not hit, so there is no collision that would happen
}

bool Board::noVerticalCollision(std::string userGuess, int shipLength) {
  convertCoordinateToIndexes(userGuess);    //updates rowIndex and columnIndex based on userGuess
  for (int i = 0; i < shipLength; i++) {
    if ((0 <= rowIndex + i && rowIndex + i <= 9) && (0 <= columnIndex && columnIndex <= 9)) {   //checks that all the next below indices are within bounds
      if (myBoard[rowIndex + i][columnIndex] != blueTilde) {   //returns false if at any time the next below indices are not blueTildes
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
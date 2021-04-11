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
  //  cout<< "printMyBoard() called"<<"\n";
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
//assumes userGuess is within boundary since that is checked first
void Board::convertCoordinateToIndexes(string coordinate) //converts userGuess to two indices and updates member variables rowIndex and columnIndex with those indices
{
  if (coordinate.length()
      != 2)    //if userGuess is not a string of length 2, we instantly return because it cannot be a valid input
  {
    return; //resolve bug where userGuess == 1 and program doesn't ask for another coordinate
  } else {
    for (unsigned int i = 0; i < columnNames.length();
         i++)    //had to make i an unsigned int since m_rowNames.length() returns an unsigned in as well
    {
      if (coordinate.at(0) == columnNames.at(i) || coordinate.at(0)
          == (tolower(columnNames.at(i))))    //compares the first char in userGuess to every element in m_rowNames,
        //which is "ABCDEFGH" until it matches one, and returns that index.
        //it also compares it to the tolower version, so "abcdefgh"
      {
        columnIndex =
            i;    //sets columnIndex to the correct index, and then breaks out since we do not need to scan through m_rowNames anymore
        break;
      } else {
        columnIndex =
            9;
      }

    }
  }

  int temp = coordinate.at(1)
      - '0'; //sets temp to the index the user typed. We subtract '0' to convert it from the ASCII value to the proper decimal value. In works cited

  rowIndex = temp
      - 1; //sets it to the column the user wants, but subtracts 1 to get the proper index

}

//bool Board::updateMyBoard(string coordinate)
//{
//  convertCoordinateToIndexes(coordinate);    //updates rowIndex and columnIndex based on userGuess
//  string tile = myBoard[rowIndex][columnIndex];    //sets the location to the current element in the index that the player got shot at
//  if (tile== blueTilde)    //if the location is a blueTilde (aka water), then it becomes a miss
//  {
//    myBoard[rowIndex][columnIndex] = whiteMiss;
//  }
//  else if (tile == ship)    //if the location is a ship, then we set that element to a redHit
//  {
//    myBoard[rowIndex][columnIndex] = redHit;
//    for (int i = 0; i < numberOfShips;
//         i++)    //searches through each ship, at the length of each ship, until it finds the correct index holding the userGuess location
//    {
//      for (int j = 0; j < myShips[i].getLength(); j++) {
//        cout<<myShips[i].getCoordinate(j)<<"\n";
//        if (myShips[i].getCoordinate(j) == coordinate) {
//          myShips[i].increaseDamage();    //add damage counter to that ship
//          if (myShips[i].isSunk())    //then, we check if it has an amount of damage counters equal to its length, meaning it has been sunk
//          {
//            std::cout
//                << "BATTLESHIP SUNK!!!\n";    //prints that the ship has been sunk
//          }
//          break;    //we can break since we found the indices of the userGuess location ship
//        }
//      }
//    }
//    return true;    //return true because a ship was hit
//  }
//  else if (tile == redHit || tile == whiteMiss)    //if the user guesses a location already shot at before, we prompt them to try again
//  {
//    throw (std::runtime_error("You already shot at this location! Try again."));
//  }
//  return false;    //if there were no hits, then this runs and we return false because it was a miss
//}
//
//void Board::updateOpponentBoard(std::string userGuess,bool wasHit)    //takes in the userGuess and a bool wasHit
//{
//  convertCoordinateToIndexes(userGuess);    //calls guess conversion to get back the correct indices based on userGuess
//  if (wasHit)    //if that location was hit, then we changed it to a redHit
//  {
//    opponentBoard[rowIndex][columnIndex] = redHit;
//  } else    //if that location was a miss, we change it to whiteMiss
//  {
//    opponentBoard[rowIndex][columnIndex] = whiteMiss;
//  }
//}

bool Board::withinBoundary(std::string coordinate) //returns true if userGuess is within bounds of the board, false if not
{
  if (coordinate.length() != 2)    //checks that the userGuess was length 2. If not, returns false immediately
  {
    return false;
  }
  else {
    convertCoordinateToIndexes(coordinate);    //takes in userGuess and sets the indices based on that guess
    if ((0 <= rowIndex && rowIndex <= 9) && (0 <= columnIndex && columnIndex <= 9)) {
      return true;    //if the indices are within the bounds of our board, we return true
    } else {
      return false;    //otherwise, we return false
    }
  }
}

void Board::setupBoard() {   //sets up the board
  printMyBoard();
  std::string coordinate;    //used to take in the user's location
  std::string
      userDirection;    //("H" or "h" or "V" or "v") horizontal or vertical ship placement
  bool validLocation = false;
  std::string temp;        //used for ascii conversion
  bool HorV =
      false; //gets set to true if the user types "H" or "h" or "V" or "v"

  myShips =
      new Ship[numberOfShips];    //creates an array of Ship objects, the amount is the number of ships

  int num = 0;
  for (const auto&[name, length] : ships) {
    Ship* shippy = new Ship(name, length);
    myShips[num] = *shippy; // does this actually points to shippy????
    cout << "I'm in board setup and myShips[i], createdShip has length : "
         << myShips[num].getLength() << " and name: " << myShips[num].getName()
         << "\n";

    if (myShips[num].getLength() == 1) // you don't need to ask for direction
    {
      coordinate = "";    //reinitialize userGuess
      do {
        cout
            << "Where would you like to place this ship of size 1? Enter your coordinate: ";
        getline(std::cin, coordinate);    //takes in the user's input

        transform(coordinate.begin(),
                  coordinate.end(),
                  coordinate.begin(),
                  ::toupper); //converts guess to uppercase so that it is always passed in consistently
        if (!withinBoundary(coordinate))    //if that location is not within the boundary, we tell them to try again
        {
          std::cout << "Invalid coordinate! Try again.\n";
        }
      } while (!withinBoundary(coordinate));    //runs until the user's coordinate is within the boundary

      myBoard[rowIndex][columnIndex] =
          ship;    //sets the user's guess location to a ship
      myShips[num].setCoordinate(coordinate, 0);
      printMyBoard();    //prints the newly updated board
    } else // you need to ask for direction before setting the coordinates to ship
    {
      cout
          << "HORIZONTAL(H/h) OR VERTICAL(V/v) orientation for this ship of size "
          << myShips[num].getLength() << ": ";
      getline(std::cin,
              userDirection);    //takes in the user input of horizontal or vertical

      do {
        HorV =
            false;    //need to reinitialize to false so that each run through, this loop correclty runs

        if (userDirection == "H" || userDirection == "h") {
          validLocation =
              false; //reinitializes to false since if they do H twice in a row, it could have been set to true from before
          cout
              << "Where would you like the left most coordinate of this ship to be? ";
          getline(std::cin, coordinate);
          transform(coordinate.begin(),
                    coordinate.end(),
                    coordinate.begin(),
                    ::toupper);    //converts guess to uppercase

          while (validLocation == false) {  //runs until the location is valid

            if (noHorizontalCollision(coordinate, myShips[num].getLength())) {
              convertCoordinateToIndexes(coordinate); //pushing two int indexes back to orignal spot of user guess
              temp =
                  coordinate;    //used to store and manipulate userGuess without changing userGuess

              for (int j = 0; j < myShips[num].getLength(); j++) {
                myBoard[rowIndex][columnIndex + j] =
                    ship;    //sets the horizontal locations to a ship
                myShips[num].setCoordinate(temp, j);

                temp[0] = temp.at(0)
                    + 1;    //sets the first value of temp (which is a copy of userGuess) to the next consecutive alphabetical value, using ASCII math
                //for example, if temp is "A1" then temp[0] = 'A', and temp.at(0) = 'A'. temp.at(0) + 1 is 'A' + 1, which returns 'B'
                //so, when then override temp[0] to B, hence traversing the columns

              }
              printMyBoard();    //prints the updated board
              validLocation =
                  true;    //sets valid location to true to help break out of loop
              HorV = true;    //true to kick out of while loop
            } else    //if the input was not "H" or "h"
            {
              cout << "SetupBoard calls printMyBoard() " << "\n";
              printMyBoard();    //prints the board again and asks the user to try again
              cout << "Invalid location. Try again!\n";
              cout
                  << "Where would you like the left most coordinate of this ship to be? ";

              getline(std::cin, coordinate);

              transform(coordinate.begin(),
                        coordinate.end(),
                        coordinate.begin(),
                        ::toupper);    //converts guess to uppercase

            }
          }

        } else if (userDirection == "V" || userDirection == "v") {
          validLocation =
              false; //reinitializes to false since if they do H twice in a row, it could have been set to true from before

          cout
              << "Where would you like the top most coordinate of this ship to be? ";

          getline(std::cin, coordinate);

          transform(coordinate.begin(),
                    coordinate.end(),
                    coordinate.begin(),
                    ::toupper);    //converts guess to uppercase


          while (validLocation == false) {
            if (noVerticalCollision(coordinate,
                                    myShips[num].getLength())) { // here I had num+1 again, like I was giving the length of the ship to be = a cata ship din map este + 1
              convertCoordinateToIndexes(coordinate); //pushing two int indexes back to orignal spot of user guess
              temp =
                  coordinate;    //used to store and manipulate userGuess without changing userGuess
              for (int j = 0; j < myShips[num].getLength(); j++) {
                myBoard[rowIndex + j][columnIndex] = ship;
                myShips[num].setCoordinate(temp, j);
                temp[1] = temp.at(1)
                    + 1;    //sets the second value of temp (which is a copy of userGuess) to the next consecutive numberical value
                //for example, if temp is "A1" then temp[1] = '1', and temp.at(1) = '1'. temp.at(1) + 1 is '1' + 1, which returns '2'
                //so, when then override temp[1] to 2, hence traversing the rows

              }
              cout << "SetupBoard calls printMyBoard() " << "\n";
              printMyBoard();    //prints the updated board

              validLocation =
                  true;    //sets valid location to true to help break out of loop
              HorV = true;    //true to kick out of while loop
            } else {
              cout << "SetupBoard calls printMyBoard() " << "\n";
              printMyBoard();    //prints the updated board again and asks the user to try again
              cout << "Invalid location. Try again!\n";
              cout
                  << "Where would you like the top most coordinate of this ship to be? ";

              getline(std::cin, coordinate);

              transform(coordinate.begin(),
                        coordinate.end(),
                        coordinate.begin(),
                        ::toupper);    //converts guess to uppercase

            }
          }
        } else {  //if the input was not "V" or "v"
          cout << "Invalid Direction. Try again!\n";
          printMyBoard();    //prints the board again so that the user can try again
          cout
              << "HORIZONTAL(H/h) OR VERTICAL(V/v) orientation for this ship of size "
              << myShips[num].getLength() << ": ";
          getline(std::cin, userDirection);
        }
      } while (!HorV);    //runs until the user has inputed "H" or "h" or "V" or "v". Also, there are checks to insure that the location was valid first as well, before getting to this point
    }
    num++;
  }
  cout << "I'm in board setup and myShips is: " << myShips
       << " with a length of " << sizeof(myShips) / sizeof(myShips[0]) << "\n";
  for (int i = 0; i < numberOfShips; i++) {
    cout << "a ship here but the myShips.getLength is " << myShips->getLength()
         << " and numberofShips is:" << numberOfShips << "\n";
    cout << myShips[i].getName() << ", " << myShips[i].getLength() << "\n";
    for (int j = 0; j < myShips[i].getLength(); j++) {
//      cout << myShips[i].getCoordinate(j) << "\n";

      cout << myShips[i].getCoordinate(j) << "\n";
    }
  }
}

bool Board::noHorizontalCollision(std::string userGuess,
                                  int shipLength)    //returns true if the userGuess location will not cause any horizontal ship collision or out of bounds errors
{
  convertCoordinateToIndexes(userGuess);    //updates rowIndex and columnIndex based on userGuess
  for (int i = 0; i < shipLength; i++) {
    if ((0 <= rowIndex && rowIndex <= 9) && (0 <= columnIndex + i
        && columnIndex + i
            <= 9))    //checks that all the next right indices are within the bounds
    {
      if (myBoard[rowIndex][columnIndex + i]
          != blueTilde)    //returns false if at any time the next right indices are not blueTildes
      {
        return false;
      }
    } else {
      return false;    //returns false if any of the right indices are out of bounds
    }
  }
  return true;    //returns true since all the false checks were not hit, so there is no collision that would happen
}

bool Board::noVerticalCollision(std::string userGuess,
                                int shipLength)    //returns true if the userGuess location will not cause any vertical ship collison or out of bounds errors
{
  convertCoordinateToIndexes(userGuess);    //updates rowIndex and columnIndex based on userGuess
  for (int i = 0; i < shipLength; i++) {
    if ((0 <= rowIndex + i && rowIndex + i <= 9) && (0 <= columnIndex
        && columnIndex
            <= 9))    //checks that all the next below indices are within bounds
    {
      if (myBoard[rowIndex + i][columnIndex]
          != blueTilde)    //returns false if at any time the next below indices are not blueTildes
      {
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
#include <iostream>
#include <iomanip> // for setw(int)

using namespace std;

#include "Board.h"
#include "GameController.h"

Board::Board(int rows, int columns, const map<string, int> &ships, map<string, int> charactersLookup) {
    this->rows = rows;
    this->columns = columns;
    this->ships = ships;
    this->numberOfShips = ships.size();
    sunkedShips = 0;
    this->charactersLookup = charactersLookup;
}

Board::~Board() {
    delete[] myShips;
}

void Board::initializeBoard() {
    //  initialize board with all tiles empty
    for (int indexRows = 0; indexRows < rows; indexRows++) {
        for (int indexColumns = 0; indexColumns < columns; indexColumns++) {
            myGrid[indexRows][indexColumns] = blueTilde;
            opponentGrid[indexRows][indexColumns] = blueTilde;
        }
    }
    printMyGrid();
    createListOfShips();
}

//Prints the current player's board
void Board::printMyGrid() {
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

//Prints the current player's view of their opponents board
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
    if (coordinate.length() > 3) {
        return;
    } else if (coordinate.length() >= 2) {
        for (int i = 0; i <= Helpers::columnNames.size(); i++) {
            s = coordinate.at(0);
            if (s == Helpers::columnNames[i]) {
                columnIndex = i;
                coordinate.erase(0, 1);
                break;
            }
        }
    } else {
        return;
    }
    stringstream ss;
    int number;
    ss << coordinate;
    ss >> number;
    //sets it to the intended column by subtracting 1 to get the proper index
    rowIndex = number - 1;
}

bool Board::updateMyGrid(const string &coordinate) {
    //updates rowIndex and columnIndex based on a given string coordinate
    convertCoordinateToIndexes(coordinate);
    string tile = myGrid[rowIndex][columnIndex];
    if (tile == blueTilde) {
        myGrid[rowIndex][columnIndex] = whiteMiss;
    } else if (tile != whiteMiss || tile != redHit) {
        myGrid[rowIndex][columnIndex] = redHit;
        // loops through all ships to find the ship with the hit coordinate in order to increase its damage
        for (int i = 0; i < numberOfShips; i++) {
            for (int j = 0; j < myShips[i].getLength(); j++) {
                if (myShips[i].getCoordinate(j) == coordinate) {
                    //add damage counter to that ship
                    myShips[i].increaseDamage();
                    if (myShips[i].isSunk()) {
                        std::cout << "\033[1;32mSHIP SUNK!!!\033[0m\n";
                        sunkedShips++;
                    }
                    break;
                }
            }
        }
        return true;    //return true because a ship was hit
        //if tile was already targeted before, user can try again
    } else if (tile == redHit || tile == whiteMiss) {
        throw (std::runtime_error("You already targeted this location! Try again."));
    }
    return false;    //if there were no hits, then this runs and we return false because it was a miss
}

void Board::updateOpponentGrid(string coordinate, bool wasHit) {
    // sets row and column indexes to point to given coordinate
    convertCoordinateToIndexes(std::move(coordinate));
    if (wasHit) {
        opponentGrid[rowIndex][columnIndex] = redHit;
    } else {
        opponentGrid[rowIndex][columnIndex] = whiteMiss;
    }
}

//Checks if given coordinate is within the boundary of the board
bool Board::withinBoundary(const string &coordinate) {
    if (coordinate.length() > 3) {
        return false;
    } else if (coordinate.length() >= 2) {
        // sets row and column indexes to point to given coordinate
        convertCoordinateToIndexes(coordinate);
        bool isit = (0 <= rowIndex && rowIndex < rows) && (0 <= columnIndex && columnIndex < columns);
        return isit;
    } else {
        return false;
    }
}

void Board::placeAllShipsAutomatically() {
    for (int shipIndex = 0; shipIndex < numberOfShips; shipIndex++) {
        placeShipAutomatically(shipIndex);
    }
    printMyGrid();
    printShips();
}

void Board::placeAllShipsManually() {
    for (int shipIndex = 0; shipIndex < numberOfShips; shipIndex++) {
        placeShipManually(shipIndex);
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
                    if (noHorizontalCollision(coordinate, myShips[index].getLength())) {
                        string temp = coordinate;
                        for (int j = 0; j < myShips[index].getLength(); j++) {
                            myGrid[rowIndex][columnIndex + j] =
                                    myShips[index].getShipIdentifier();   //set tile to ship
                            myShips[index].addCoordinate(temp,
                                                         j); // add tempCoordinate to the ships coordinates
                            temp[0] = temp.at(0) + 1; // moves to next one
                        }
                        myShips[index].setPlaced(true);
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
                        //used to store and manipulate tempCoordinate without changing it
                        string temp = coordinate;
                        for (int j = 0; j < myShips[index].getLength(); j++) {
                            myGrid[rowIndex + j][columnIndex] = myShips[index].getShipIdentifier();
                            myShips[index].addCoordinate(temp, j);
                            temp[1] = temp.at(1) + 1;
                        }
                        myShips[index].setPlaced(true);
                        isValidCoordinate = true;
                        isValidDirection = true;    //true to exit the while loop
                    } else {
                        coordinate = Helpers::getRandomCoordinate(rows, columns);
                    }
                }
            }
            //runs until the user has inputed "H" or "h" or "V" or "v".
        } while (!isValidDirection);

    } else {
        cout << "Ship is already placed!" << "\n";
    }
}

void Board::placeShipManually(int shipIndex) {
    if (!myShips[shipIndex].getPlaced()) {
        cout << "\nPlace your " << myShips[shipIndex].getName() << ", " << myShips[shipIndex].getLength();
        string coordinate;
//TODO: do not ask for direction when ship length is 1
        string direction = Helpers::getDirectionInput();
        bool isValidDirection = false;
        bool isValidCoordinate = false;
        do {
            if (isValidHorizontalDirection(direction)) {
                string input = Helpers::getInput("Enter your left/top most coordinate: ");
                coordinate = Helpers::getCoordinate(input, charactersLookup, rows);
                if (coordinate == INVALID_COORDINATE) {
                    cout << "\n\033[1;31mInvalid coordinate! Please try again.\033[0m\n";
                    isValidCoordinate = false;
                    break;
                }
                while (!isValidCoordinate) {  //runs until the coordinate is valid
                    if (noHorizontalCollision(coordinate,
                                              myShips[shipIndex].getLength())) {
                        string temp = coordinate;
                        for (int j = 0; j < myShips[shipIndex].getLength(); j++) {
                            myGrid[rowIndex][columnIndex + j] =
                                    myShips[shipIndex].getShipIdentifier();   //set tile to ship's identifier
                            myShips[shipIndex].addCoordinate(temp, j); // add tempCoordinate to the ships coordinates
                            temp[0] = temp.at(0) + 1; // moves to next one
                        }
                        myShips[shipIndex].setPlaced(true);
                        printMyGrid();    //prints the updated board
                        printShips();
                        isValidCoordinate = true;
                        isValidDirection = true;    //true to kick out of while loop
                    } else {
                        cout << "\n\033[1;31mInvalid location. Try again!\033[0m\n";
                        string input = Helpers::getInput("Enter your left/top most coordinate: ");
                        coordinate = Helpers::getCoordinate(input, charactersLookup, rows);
                        if (coordinate == INVALID_COORDINATE) {
                            cout << "\n\033[1;31mInvalid coordinate! Please try again.\033[0m\n";
                            isValidCoordinate = false;
                            break;
                        }
                    }
                }

            } else if (isValidVerticalDirection(direction)) {
                string input = Helpers::getInput("Enter your left/top most coordinate: ");
                coordinate = Helpers::getCoordinate(input, charactersLookup, rows);
                if (coordinate == INVALID_COORDINATE) {
                    cout << "\n\033[1;31mInvalid coordinate! Please try again.\033[0m\n";
                    isValidCoordinate = false;
                    break;
                }

                while (!isValidCoordinate) {
                    if (noVerticalCollision(coordinate,
                                            myShips[shipIndex].getLength())) {
                        string temp = coordinate;
                        for (int j = 0; j < myShips[shipIndex].getLength(); j++) {
                            myGrid[rowIndex + j][columnIndex] = myShips[shipIndex].getShipIdentifier();
                            myShips[shipIndex].addCoordinate(temp, j);
                            temp[1] = temp.at(1) + 1;
                        }
                        myShips[shipIndex].setPlaced(true);
                        printMyGrid();
                        printShips();
                        isValidCoordinate = true;
                        isValidDirection = true;    //true to exit the while loop
                    } else {
                        cout << "\n\033[1;31mInvalid location. Try again!\033[0m\n";
                        string input = Helpers::getInput("Enter your left/top most coordinate: ");
                        coordinate = Helpers::getCoordinate(input, charactersLookup, rows);
                        if (coordinate == INVALID_COORDINATE) {
                            cout << "\n\033[1;31mInvalid coordinate! Please try again.\033[0m\n";
                            isValidCoordinate = false;
                            break;
                        }
                    }
                }
            } else {  //if the input was not "V" or "v"
                cout << "\n\033[1;31mInvalid Direction. Try again!\033[0m\n";
                direction = Helpers::getDirectionInput();

            }
        } while (!isValidDirection);    //runs until the user has inputed "H" or "h" or "V" or "v".
    } else {
        cout << "Ship is already placed!" << "\n";
    }
}

bool Board::isValidVerticalDirection(const string &direction) const {
    return direction == "V" || direction == "v";
}

bool Board::isValidHorizontalDirection(const string &direction) const {
    return direction == "H" || direction == "h";
}

void Board::createListOfShips() {
    myShips = new Ship[numberOfShips]; // create list of null ship objects
    int shipIndex = 0;
    for (const auto&[name, length] : ships) { // create ship objects and add them to the list of ships
        Ship *newShip = new Ship(name, length);
        myShips[shipIndex] = *newShip;
        shipIndex++;
    }
}

void Board::printShips() {
    cout << "\nID " << setw(2) << "-  " << "STATUS   " << setw(8) << "-  "  "SHIP" << "\n";
    for (int i = 0; i < numberOfShips; i++) {
        cout << i << setw(5) << "-  " << myShips[i].isPlaced() << setw(6) << "-  " << myShips[i].getName() << ","
             << myShips[i].getLength()
             << "\n";
    }
    cout << "\n\n";
}

bool Board::noHorizontalCollision(std::string coordinate, int shipLength) {
    convertCoordinateToIndexes(std::move(coordinate));    //updates rowIndex and columnIndex based on coordinate
    for (int i = 0; i < shipLength; i++) {
        //checks that all the next right indices are within the bounds
        if ((0 <= rowIndex && rowIndex <= rows) &&
            (0 <= columnIndex + i && columnIndex + i <= columns)) {
            //returns false if at any time the next right indices are not blueTildes
            if (myGrid[rowIndex][columnIndex + i] != blueTilde) {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

bool Board::noVerticalCollision(std::string coordinate, int shipLength) {
    //updates rowIndex and columnIndex based on coordinate
    convertCoordinateToIndexes(std::move(coordinate));
    for (int i = 0; i < shipLength; i++) {
        //checks that all the next below indices are within bounds
        if ((0 <= rowIndex + i && rowIndex + i <= rows) &&
            (0 <= columnIndex && columnIndex <= columns)) {
            //returns false if at any time the next below indices are not blueTildes
            if (myGrid[rowIndex + i][columnIndex]
                != blueTilde) {
                return false;
            }
        } else {
            return false;    //returns false if any of the below indices are out of bounds
        }
    }
    return true;
}

int Board::getNumberOfShips() const {
    return numberOfShips;
}

Ship *Board::getShips() const {
    return myShips;
}


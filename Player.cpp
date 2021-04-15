#include "Player.h"

//#include <utility>
//Player overloaded constructor that initialises member variables with default values
Player::Player(int rows, int columns, const map<string, int> &boats, map<string, int> alphaLookup_) {
    board = new Board(rows, columns, boats, alphaLookup_);
}

//Player destructor
Player::~Player() {
    delete board;
}

void Player::shootCoordinate(string coordinate, bool hit) {
    board->updateOpponentGrid(std::move(coordinate), hit);
}

bool Player::getShot(const string &coordinate) {
    if (board->withinBoundary(coordinate)) {
        return (board->updateMyGrid(coordinate));
    } else {
        throw (runtime_error("Out of Board boundary! Please try again.\n"));
    }

}

Board *Player::getBoard() const {
    return board;
}

bool Player::allShipsPlaced() {
    int numberOfShips = board->getNumberOfShips();
    int placedShips = 0;
    for (int i = 0; i < numberOfShips; i++) {
        if (board->getShips()[i].getPlaced())
            placedShips++;
    }
    return placedShips == numberOfShips;
}

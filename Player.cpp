#include "Player.h"

#include <utility>

Player::Player(int rows, int columns, const map<string, int>& boats) {
  board = new Board(rows, columns, boats);
}

Player::~Player() {
  delete board;
}

void Player::shootCoordinate(string coordinate, bool hit) {
  board->updateOpponentGrid(std::move(coordinate), hit);
}

bool Player::getShot(const string& coordinate) {
  if (board->withinBoundary(coordinate)) {
    return (board->updateMyGrid(coordinate));
  } else {
    throw (runtime_error("Out of Board boundary! Please try again.\n"));
  }

}

Board* Player::getBoard() const {
  return board;
}

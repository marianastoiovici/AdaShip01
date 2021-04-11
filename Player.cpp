#include "Player.h"

Player::Player(int rows, int columns, map<string, int> boats) {
  board = new Board(rows, columns, boats);
}

Player::~Player() {
  delete board;
}

void Player::shootCoordinate(string coordinate, bool hit) {
  board->updateOpponentBoard(coordinate, hit);
}

bool Player::getShot(string coordinate) {
  if (board->withinBoundary(coordinate)) {
    return (board->updateMyBoard(coordinate));
  } else {
    throw (runtime_error("Out of Board boundary! Please try again.\n"));
  }

}

Board* Player::getBoard() const {
  return board;
}

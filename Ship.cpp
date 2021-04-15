#include "Ship.h"
#include "Helpers.h"


//Ship default constructor that initialises member variables with default values
Ship::Ship() {
  coordinates = nullptr;
  name = "";
  length = 0;
  damage = 0;
  placed = false;
  shipIdentifier="";
}

//Ship overloaded constructor
Ship::Ship(string name, int length)
{
  this->name = name; //initialises name variable to given name value
  this->length = length; //initialises length variable to given length value
  coordinates =
      new string[this->length]; //initialises coordinates to an array of strings of the ship's length
  damage = 0; //initialises damage variable to default value of 0
  placed = false;
  shipIdentifier = Helpers::charToString(name.at(0));
}

//ship destructor
Ship::~Ship() {
  delete[] coordinates;
}

//function that returns the length of a ship
int Ship::getLength() const {
  return length;
}

//function that returns the ship's Identifier on the board
string Ship::getShipIdentifier() const {
  return shipIdentifier;
}

//function that returns the name of a ship
string Ship::getName() const {
  return name;
}

//function that sets the ship's coordinates at a given index, to a given coordinate
void Ship::addCoordinate(std::string coordinate, int index) {
  coordinates[index] = std::move(coordinate);
}

//function that gets the coordinate stored in coordinates at a given index
std::string Ship::getCoordinate(int index) const {
  return coordinates[index];
}

//function that increases damage to a ship
void Ship::increaseDamage() {
  damage++;   //increment the damage by one when a ship is hit
}

//function that returns true or false depending on if the ship is sunk or not
bool Ship::isSunk() const {
  //if the damage equals the length of the ship
  return damage == length;
}

//function that whether a ship is placed on board or not
bool Ship::getPlaced() const {
  return placed;
}

//function that sets the value of placed for a ship
void Ship::setPlaced(bool newPlaced) {
  placed = newPlaced;
}


string Ship::isPlaced(){
  if(getPlaced()){
    return "PLACED";
  } else {
    return "NOT PLACED";
  }
}
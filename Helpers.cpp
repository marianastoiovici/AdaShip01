#include <map>
#include "Helpers.h"
using namespace std;

vector<string>Helpers::columnNames =
    {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
     "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
int Helpers::getRandomInt(int min, int max) {
  random_device rd;
  mt19937 mt(rd());
  uniform_int_distribution<int> dist(min, max);
  return dist(mt);
}
string Helpers::getRandomDirection() {
  string randomDirection;
  int randomInt = Helpers::getRandomInt(1, 2);
  if (randomInt == 1) {
    return randomDirection = "H";
  } else {
    return randomDirection = "V";
  }
}

string Helpers::getDirectionInput() {
  string directionInput;
  cout << "\nHORIZONTAL(H/h) OR VERTICAL(V/v) orientation: ";
  getline(std::cin,
          directionInput);
  return directionInput;
}
string Helpers::getCoordinateInput() {
  string coordinateInput;
//  cout << "Enter coordinate of type \'A1\', \'E5\' to place your ship.\n";
  cout << "Enter your left/top most coordinate: ";
  getline(std::cin, coordinateInput);
  transform(coordinateInput.begin(),
            coordinateInput.end(),
            coordinateInput.begin(),
            ::toupper);    //converts coordinate to uppercase
  return coordinateInput;
}

string Helpers::getRandomCoordinate(int rows, int columns) {
  string randomCoordinate;
  int randomRow = Helpers::getRandomInt(0, rows - 1);
  int randomColumn = Helpers::getRandomInt(0, columns - 1);
  randomCoordinate = columnNames[randomColumn] + to_string(randomRow);
  return randomCoordinate;
}

string Helpers::getInput(string question){
  string input;
  cout << question;
  getline(cin, input);
  return input;
}

//string Helpers::printText(string text){
//  cout<<
//}

string Helpers::getTargetInput( map<string, int> map, int rows) {
  string target = getInput("Where would you like to shoot: ");

  int index = 0;
  // get the alphabetic part of the string
  string alphabetic = "";
  while (index < target.length() && isalpha(target[index])) {
    alphabetic += toupper(target[index]);
    index++;
  }

    // if the alphabetic part is not in the map, return invalid
  if (map.find(alphabetic) == map.end()) {
    return INVALID_COORDINATE;
  }

  // otherwise, look up the column number it represents
  int column = map[alphabetic];

  // get the number part
  string numeric = "";
  while (index < target.length() && isdigit(target[index])) {
    numeric += target[index];
    index++;
  }

  // if we're not at the end of the string, or the numeric part is
  // empty, return (0, 0)
  if (index < target.length() || numeric.length() == 0) {
    return INVALID_COORDINATE;
  }
  // get the row
  int row = stoi(numeric);

  // if the row > the total number of my board's rows, return (0, 0)
  if (row > rows) {
    return INVALID_COORDINATE;
  }

  return alphabetic+numeric;
}
string Helpers::charToString(char character) {
  stringstream ss;
  string myString;
  ss << character;
  ss >> myString;
  return myString;
}

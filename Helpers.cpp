#include "Helpers.h"
using namespace std;

vector<string> Helpers::columnNames = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
int Helpers::getRandomInt(int min, int max) {
  random_device rd;
  mt19937 mt(rd());
  uniform_int_distribution<int> dist(min, max);
  return dist(mt);
}
string Helpers::getRandomDirection() {
  string randomDirection;
  int randomInt= Helpers::getRandomInt(1, 2);
  if (randomInt == 1){
    return randomDirection= "H";
  } else {
    return randomDirection= "V";
  }
}

string Helpers::getDirectionInput( string shipName) {
  string directionInput;
  cout << "HORIZONTAL(H/h) OR VERTICAL(V/v) orientation for "
       << shipName << " :";
  getline(std::cin,
          directionInput);    //takes in the user input of horizontal or vertical
  return directionInput;
}
string Helpers::getCoordinateInput(string shipName) {
  string coordinateInput;
  cout << "Enter coordinate of type \'A1\', \'E5\' to place your ship.\n";
  cout << "Enter your left/top most coordinate for " << shipName
       << ": ";
  getline(std::cin, coordinateInput);
  transform(coordinateInput.begin(),
            coordinateInput.end(),
            coordinateInput.begin(),
            ::toupper);    //converts coordinate to uppercase
  return coordinateInput;
}

string Helpers:: getRandomCoordinate(int rows, int columns) {
  string randomCoordinate;
  int randomRow= Helpers::getRandomInt(0, rows - 1);
  int randomColumn = Helpers::getRandomInt(0, columns - 1);
  randomCoordinate = columnNames[randomColumn] + to_string(randomRow);
  cout << "Yuhuuu, my random coordinate is: " << randomCoordinate<<"\n";
  return randomCoordinate;
}

string Helpers::getTargetInput(){
  string target;
  cout << "Where would you like to shoot: ";
  getline(cin, target);
  transform(target.begin(), target.end(), target.begin(), ::toupper);
  return target;
}

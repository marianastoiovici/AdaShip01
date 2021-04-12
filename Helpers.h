#include <iostream>
#include <random>
#include "algorithm" //for transform
#include <sstream>
using namespace std;

class Helpers {
 public:
  //TODO: improve columnNames to contain generated names based on the nr of columns.
//  TODO: if improved, check coordinates that reads the first char as the columns. for AA12 - AA needs to be the column name
  static vector<string> columnNames ;
  static int getRandomInt(int min, int max);
  static string getRandomDirection();
  static string getDirectionInput(string shipName);
  static string getCoordinateInput(string shipName);
  static string getRandomCoordinate(int rows, int columns);
  static string getTargetInput();
  static string charToString(char character);
};
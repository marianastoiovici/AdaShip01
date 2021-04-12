#include <iostream>
#include <random>
#include "algorithm" //for transform
using namespace std;

class Helpers {
 public:
  static vector<string> columnNames ;
  static int getRandomInt(int min, int max);
  static string getRandomDirection();
  static string getDirectionInput(string shipName);
  static string getCoordinateInput(string shipName);
  static string getRandomCoordinate(int rows, int columns);
  static string getTargetInput();
};
#include <iostream>
#include <random>
#include "algorithm" //for transform
#include <sstream>
#include "map"

using namespace std;

static const char *const INVALID_COORDINATE = "target invalid";

class Helpers {
public:
    //TODO: improve columnNames to contain generated names based on the nr of columns.
//  TODO: if improved, check coordinates that reads the first char as the columns. for AA12 - AA needs to be the column name

    static int getRandomInt(int min, int max);

    static string getRandomDirection();

    static string getDirectionInput();

    static string getCoordinate(string coordinate, map<string, int> map, int rows);

    static string charToString(char character);

    static string getInput(string question);

    static string getRandomCoordinate(int rows, int columns);

    static vector<string> columnNames;
};
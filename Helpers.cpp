#include <map>
#include "Helpers.h"

using namespace std;

vector<string>Helpers::columnNames =
        {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
         "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "AA", "AB", "AC"};

int Helpers::getRandomInt(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(min, max);
    return dist(gen);
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
    getline(std::cin, directionInput);
    return directionInput;
}

string Helpers::getRandomCoordinate(int rows, int columns) {
    string randomCoordinate;
    int randomRow = Helpers::getRandomInt(0, rows - 1);
    int randomColumn = Helpers::getRandomInt(0, columns - 1);
    randomCoordinate = columnNames[randomColumn] + to_string(randomRow);
    return randomCoordinate;
}

string Helpers::getInput(string question) {
    string input;
    cout << question;
    getline(cin, input);
    return input;
}

string Helpers::getCoordinate(string coordinate, map<string, int> map, int rows) {
    int index = 0;
    // get the alphabetic part from the string
    string alphabetic;
    while (index < coordinate.length() && isalpha(coordinate[index])) {
        alphabetic += toupper(coordinate[index]);
        index++;
    }

    // if the alphabetic part is not in the map, return invalid
    if (map.find(alphabetic) == map.end()) {
        return INVALID_COORDINATE;
    }

    // get the number part from the string
    string numeric;
    while (index < coordinate.length() && isdigit(coordinate[index])) {
        numeric += coordinate[index];
        index++;
    }

    // if we're not at the end of the string, or the numeric part is
    // empty,return invalid coordinate
    if (index < coordinate.length() || numeric.length() == 0) {
        return INVALID_COORDINATE;
    }
    // get the row
    int row = stoi(numeric);

    // if the row > the total number of the board's rows, return invalid coordinate
    if (row > rows) {
        return INVALID_COORDINATE;
    }

    return alphabetic + numeric;
}

string Helpers::charToString(char character) {
    stringstream ss;
    string myString;
    ss << character;
    ss >> myString;
    return myString;
}

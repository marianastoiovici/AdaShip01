#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <random>
#include <sstream>
#include "map"

using namespace std;

static const char *const INVALID_COORDINATE = "target invalid";

class Helpers {
public:

    static int getRandomInt(int min, int max);

    static string getRandomDirection();

    static string getDirectionInput();

    static string getCoordinate(string coordinate, map<string, int> map, int rows);

    static string charToString(char character);

    static string getInput(string question);

    static string getRandomCoordinate(int rows, int columns);

    //TODO: columnNames to contain columns over the length of alphabet
    static vector<string> columnNames;
};

#endif
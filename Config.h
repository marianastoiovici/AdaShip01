#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <map>

static const char* const BOAT = "boat";
static const char* const BOARD = "board";
static const char* const FILE_NAME = "adaship_config.ini";

using namespace std;

class Config {
  private:
    int rows;
    int columns;
    map<string,int> ships;

    // Reads the board's rows and columns
    bool readBoard(string configLine, int index);

    // Reads the ship's name and length
    bool readShips(string configLine, int index);



  public:
    Config() {}

   // Reads the config file
    bool readConfigFile();

   // Gets the number of rows
    int getRows() {
      return rows;
    }

    // Gets the number of columns
    int getColumns() {
      return columns;
    }

    // Getter for list of ships to be placed on the board
    map<string,int> getShipsToPlace() {
      return ships;
    }

  void readDataFromFile(bool& boardRead, bool& shipsRead);
};

#endif
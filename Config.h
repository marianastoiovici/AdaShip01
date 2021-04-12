#include <string>
#include <vector>
#include <map>

static const char* const BOAT = "boat";
static const char* const BOARD = "board";
static const char* const FILE_NAME = "adaship_config.ini";

using namespace std;

class Config {
  private:
    int rows; //board rows
    int columns; // board columns
    map<string,int> ships;

    // Reads the board's rows and columns and returns whether the action was successful or not
    bool readBoard(string configLine, int index);

    // Reads the ship's name and length and returns whether the action was successful or not
    bool readShips(string configLine, int index);



  public:
    Config() {}

   // Reads the config file provided and returns whether the action was successful or not
    bool readConfigFile();

   // Getter for number of rows
    int getRows() {
      return rows;
    }

    // Getter for number of columns
    int getColumns() {
      return columns;
    }

    // Getter for list of ships to be placed on the board
    map<string,int> getShipsToPlace() {
      return ships;
    }

  void readDataFromFile(bool& boardRead, bool& shipsRead);
};
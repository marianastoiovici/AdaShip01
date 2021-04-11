#include <string>
#include <vector>
#include <map>


using namespace std;


class Config {
  private:
    int rows; //board rows
    int columns; // board columns
    map<string,int> boatsToPlace;

    // Reads the board's rows and columns and returns whether the action was successful or not
    bool readBoard(string configLine, int index);

    // Reads the boat's name and length and returns whether the action was successful or not
    bool readBoats(string configLine, int index);



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

    // Getter for list of boats to be placed on the board
    map<string,int> getBoatsToPlace() {
      return boatsToPlace;
    }
};
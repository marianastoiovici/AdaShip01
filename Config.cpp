#include <iostream>
#include <fstream>

using namespace std;

#include "Config.h"

//Read the config file (adaship_config.ini)
bool Config::readConfigFile() {
    bool boardRead = false;
    bool shipsRead = false;
    readDataFromFile(boardRead, shipsRead);
    return (shipsRead && boardRead);
}

void Config::readDataFromFile(bool &boardRead, bool &shipsRead) {
    ifstream configFile;
    string configLine;

    configFile.open(FILE_NAME);

    // read the file line by line
    while (!configFile.eof()) { // while not at the end of the file
        // read line from file and store it in configLine variable
        getline(configFile, configLine);
        // variable to store the type of asset that's being read
        string type;
        int index = 0;
        //read the configLine until the ':' to get whether is config for the board or ship
        while (index < configLine.length() && configLine[index] != ':') {
            type += tolower(configLine[index]);
            index++; // update index
        }
        // skip the ':'
        index += 1;

        // if is a board update it
        if (type == BOARD) {
            if (readBoard(configLine, index)) {
                boardRead = true;
            }
            // if is a ship update it
        } else if (type == BOAT) {
            if (readShips(configLine, index)) {
                shipsRead = true;
            }
        }

    }
    // close the file
    configFile.close();
}

// Sets the board configuration according to the config file
bool Config::readBoard(string configLine, int index) {
    string tempRows;
    string tempColumns;

    //skip over the non digit characters after ':'
    while (index < configLine.length() && !isdigit(configLine[index])) {
        index++;
        if (index == configLine.length()) {
            return false;
        }
    }
    // get numeric characters and store them in the 'tempRows' string
    while (index < configLine.length() && isdigit(configLine[index])) {
        tempRows += configLine[index];
        index++;
        if (index == configLine.length()) {
            return false;
        }
    }
    // skip over the 'x' char or any other extra white spaces
    while (index < configLine.length() && !isdigit(configLine[index])) {
        index++;
        if (index == configLine.length()) {
            return false;
        }
    }
    // get numeric characters and store them in the 'tempColumns' string
    while (index < configLine.length() && isdigit(configLine[index])) {
        tempColumns += configLine[index];
        index++;
    }

    this->rows = stoi(tempRows);// convert string to int for tempRows
    this->columns = stoi(tempColumns); // convert string to int for tempColumns

    bool isBoardSizeValid = true;
    if ((this->rows < 5 || this->rows > 80)
        || (this->columns < 5 || this->columns > 80)) {
        isBoardSizeValid = false;
    }
    return isBoardSizeValid;
}

// reads the length of the ship from the config file
bool Config::readShips(string configLine, int index) {
    //skip the white spaces after ':'
    if (configLine[index] == ' ') {
        index++;
    }
    // get the shipName of the boat by reading up until ','
    string shipName;
    while (index < configLine.length() && configLine[index] != ',') {
        shipName += configLine[index];
        index++;
        if (index == configLine.length()) {
            return false;
        }
    }

    // skip over  ',' or white spaces
    while (index < configLine.length() && !isdigit(configLine[index])) {
        index++;
        if (index == configLine.length()) {
            return false;
        }
    }
    // get the length of the ship from here
    string shipLength;
    while (index < configLine.length() && isdigit(configLine[index])) {
        shipLength += configLine[index];
        index++;
    }

    ships[shipName] = stoi(shipLength);

    return true;
}
#include <iostream>
#include <fstream>

using namespace std;

#include "Config.h"


//read the config file (adaship_config.ini) and returns whether this was completed successfully or not
bool Config::readConfigFile() {
  ifstream configFile;
  string configLine;

  // variables to check if board and boats information have been read and saved
  bool boardRead = false;
  bool boatsRead = false;

  configFile.open("adaship_config.ini");

  // read the file line by line
  while(!configFile.eof()) { // while not at the end of the file
    getline(configFile, configLine); //read line from file and store it in configLine variable
    // variable to store the type of asset that's being read
    string type;
    int index = 0;
    //read the configLine until the ':' to get whether is config for the board or boat
    while (index < configLine.length() && configLine[index] != ':') {
      //update type variable
      type += tolower(configLine[index]);
      index++; // update index
    }
    // skip the ':'
    index += 1;
    // if is a board asset update it with the rest of the configLine

    if (type == "board") {
      if (readBoard(configLine, index)) {
        boardRead = true;
      }
      // if is a boat update boats
    } else if (type == "boat") {
      if (readBoats(configLine, index)) {
        boatsRead = true;
      }
    }

  }

  // close the file
  configFile.close();
	return (boatsRead && boardRead);
}

 // Sets the board configuration according to the config file and returns whether this completed successfully or not
bool Config::readBoard(string configLine, int index) {
  string tempRows;
  string tempColumns;

  //skip the non digit characters after ':'
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
    //cout << "tempRows: " << tempRows << "\n";
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
    // cout << "tempColumns: " << tempColumns << "\n";
    index++;
  }

  this->rows = stoi(tempRows);// convert string to int for tempRows
  this->columns = stoi(tempColumns); // convert string to int for tempColumns

  bool isBoardSizeValid = true;
  if ((this->rows<5 || this->rows>80) || (this->columns<5 || this->columns>80)) {
    isBoardSizeValid = false;
  }
//  cout << "Board : " << this->tempRows << " x " << this->tempColumns << "\n";
  // cout << "\n isBoardSizeValid: " << isBoardSizeValid <<"\n";
  return isBoardSizeValid;
}

// reads the length of the boat from the config file
bool Config::readBoats(string configLine, int index) {
  // variable to store a temporary instance of type boat
//  Ship::boat tempBoat;
  //skip the white spaces after ':'
  if (configLine[index] == ' ') {
    index++;
  }
  // get the name of the boat by reading up until ','

  string name;
  while (index < configLine.length() && configLine[index] != ',') {
    name += configLine[index];
    index++;
    if (index == configLine.length()) {
      return false;
    }

  }

  // cout << "name: " << name << "\n";

  // skip over  ',' or white spaces
  while (index < configLine.length() && !isdigit(configLine[index])) {
    index++;
    if (index == configLine.length()) {
      return false;
    }
  }
  // get the length of the boat from here
  string length;
  while (index < configLine.length() && isdigit(configLine[index])) {
    length += configLine[index];
    index++;
  }
  // cout << "Boat's length is:  " << length  << "\n";
//  cout << "Boat : " << name << ", " << length << "\n";

//  tempBoat.name = name;
//  tempBoat.length = stoi(length);
//  // add boat to our list of boats that needs to be placed on the board
//  this->boatsToPlace.push_back(tempBoat);

//   for (int i =0; i < this->boatsToPlace.size(); i++ ){
//     cout<< "we are here and name of boat is : " << this->boatsToPlace[i].name << " and length of boat is : " << this->boatsToPlace[i].length << "\n";
//   }

boatsToPlace[name] = stoi(length);
map<string,int>::iterator it;
//for(it=boatsToPlace.begin(); it!=boatsToPlace.end();++it){
//  cout<<it->first<< " => " <<it->second << '\n';
//}
  return true;
}
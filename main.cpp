#include <iostream>
using namespace std;

#include "GameController.h"

int main() {
  // Instantiate a Config object
  Config config;
  //  Read the file and store boolean result
  bool isConfigRead = config.readConfigFile();
  //   If configuration is not completed successfully inform user and stop program
  if (!isConfigRead) {
    cout << "Configuration did not complete successfully.\n";
    return 0;
  }

  GameController gameController(config);
  gameController.menu();

  return 0;
}

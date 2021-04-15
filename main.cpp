#include <iostream>

using namespace std;

#include "GameController.h"

int main() {
    // Instantiate a Config object to read configuration details
    Config config;
    bool isConfigRead = config.readConfigFile();
    //   If configuration is not completed successfully inform user and stop program
    if (!isConfigRead) {
        cout << "Configuration did not complete successfully.\n";
        return 0;
    }
    // Instantiate a GameController object to run the game
    GameController gameController(config);
    gameController.menu();

    return 0;
}

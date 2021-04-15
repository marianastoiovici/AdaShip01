#ifndef SHIP_H
#define SHIP_H

#include <iostream>

using namespace std;

class Ship {
private:
    string *coordinates;
    string name;
    int length;
    int damage;
    bool placed;
    string shipIdentifier;

public:
    Ship();

    Ship(string name, int length);

    ~Ship();

    string getName() const;

    int getLength() const;

    void addCoordinate(string coordinate, int index);

    string getCoordinate(int index) const;

    bool getPlaced() const;

    void setPlaced(bool newPlaced);

    string isPlaced();

    void increaseDamage();

    bool isSunk() const;

    string getShipIdentifier() const;
};

#endif
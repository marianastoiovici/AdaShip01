#include <iostream>

using namespace std;

class Ship {
 private:
  string* coordinates;
  string name;
  int length;
  int damage;
  bool placed;

 public:
  Ship();
  Ship(string name, int length);
  ~Ship();

  string getName() const;
  int getLength() const;
  void addCoordinate(string coordinate, int index);
  string getCoordinate(int index) const;
  void increaseDamage();
  bool isSunk();
  void setPlaced(bool newPlaced);
  bool getPlaced() const;

};
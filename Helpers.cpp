#include "Helpers.h"
using namespace std;

int Helpers::getRandomInt(int min, int max) {
  random_device rd;
  mt19937 mt(rd());
  uniform_int_distribution<int> dist(min, max);
  return dist(mt);
}
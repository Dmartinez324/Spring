
#include <iostream>
#include <raylib.h>
#include <vector>
#include <glm/glm.hpp>
#include "Circle.h"

using namespace std;


class Spring{
  public:
  Spring();
  Spring(Circle bCircle, int s, glm::vec2 d, double k, Circle eCircle);
  ~Spring();

  float getX();
  float getY();
  float getGrav();
  float getVelocity();


  glm::vec2 beginPos;
  Circle bCircle;
  Circle eCircle;
  int restedLength;
  glm::vec2 Direction;
  double k;
  glm::vec2 endPos;

};




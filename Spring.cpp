#include "Spring.h"
#include <iostream>



Spring::Spring() : beginPos(glm::vec2(0.0f, 0.0f)), restedLength(1.0f), Direction(glm::vec2(0.0f, 0.0f)), k(0.0f) {}

// Parameterized constructor
Spring::Spring(Circle b, int size, glm::vec2 dir, double velocity, Circle e)
    : bCircle(b), restedLength(size), Direction(dir), k(velocity), eCircle(e) {}


Spring::~Spring(){
    
}
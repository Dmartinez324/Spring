#include <iostream>
#include <raylib.h>
#include <vector>
#include <glm/glm.hpp>
#include "Circle.h"
#include <unistd.h>
#include <string>
#include "Spring.h"



class Simulation{
    public:
    std::vector<Circle> circles;
    float _gravity = 0.05f;
    float GravConstant = 1;
    bool firstClick;
    bool skip;
    std::vector<glm::vec2> direction;
    std::vector<bool> skips;
    std::vector<Spring> springs;
    Spring spring;
    bool done;


    Simulation();
    void BeginSim();
    void Gravity();
    void DrawMovement();
    void Movememnt();
    void StartPendulum();
    void GetSpringPos();
};
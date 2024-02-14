#include <iostream>
#include <raylib.h>
#include <vector>
#include <glm/glm.hpp>
//#include "Circle.h"
#include "Simulation.h"

int main() {
    // SetTraceLogLevel(LOG_NONE);
    // InitWindow(800, 600, "Gravity");
    // std::vector<Circle> circles;
    // std::vector<Vector2> direction;
    // bool firstClick = true;
    // glm::vec2 firstClickPos;
    // float size = 10.0f;

    // while (!WindowShouldClose()) {

    //     SetTargetFPS(60);
    //     float mousePosX = -100.0f;
    //     float mousePosY = -100.0f;

    //     if(IsKeyReleased(KEY_ONE)){
    //         size = 10.0f;
    //     }
    //     if(IsKeyReleased(KEY_TWO)){
    //         size = 20.0f;
    //     }
    //     else if(IsKeyReleased(KEY_THREE)){
    //         size = 30.0f;
    //     }
        

    //     if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    //         mousePosX = GetMouseX();
    //         mousePosY = GetMouseY();
    //         circles.push_back({{mousePosX,mousePosY}, size, {0.0f,0.0f}, 0.0f});
    //     }
        
    //     BeginDrawing();
    //     ClearBackground(RAYWHITE);     

    //     //moves the circles based on gravity
    //     for(auto& circle : circles){
    //         circle.velocity += 0.02f;
    //         circle.pos.y += circle.velocity;
    //     }
        
        
    //     //draws the circles in their current pos
    //    for(const auto& circle : circles){
    //     DrawCircle(circle.pos.x,circle.pos.y,circle.size,RED);
    //    }
    
    //     EndDrawing();
    // }

    // CloseWindow();
    Simulation sim;

    sim.BeginSim();
    return 0;
}





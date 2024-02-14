#include "Simulation.h"
#include <iostream>




Simulation::Simulation(){}



void Simulation:: BeginSim(){
    SetTraceLogLevel(LOG_NONE);
    InitWindow(GetScreenWidth(),GetScreenHeight(), "Pendulum");
    skip = firstClick = true;
    float size = 10.0f;
    bool first,second,third, fourth, fifth;
    first = second = third = fourth = fifth= false;
    bool firstClick, secondClick = false;
    firstClick = true;

    Circle c1,c2;

    bool filled = false;
    done = false;

    while (!WindowShouldClose()) {

        SetTargetFPS(60);
        
        if(circles.size() == 2){
            filled = true;
        }

        if(IsKeyReleased(KEY_ONE)){
            first = true;
            second = false;
            third = false;
            fourth = false;
        }
        if(IsKeyReleased(KEY_TWO)){
            first = false;
            second = true;
            third = false;
            fourth = false;
        }
        if(IsKeyReleased(KEY_THREE)){
            first = false;
            second = false;
            third = true;
            fourth = false;
        }
        if(IsKeyReleased(KEY_FOUR)){
            first = false;
            second = false;
            third = false;
            fourth = true;
        }



        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            float x = GetMouseX();
            float y = GetMouseY();
            //Circle(glm::vec2 p, float s, glm::vec2 d, float v, string t);
            if(first && !filled && !done){
                circles.push_back({{x,y},30.0f,{0.0f,0.0f}, 0.02f, 0});
                direction.push_back({0.0f,0.0f});
                skips.push_back(true);
            }
            if(second && !filled && !done){
                circles.push_back({{x,y},30.0f,{0.0f,0.0f}, 0.02f, 1});
                direction.push_back({0.0f,0.0f});
                skips.push_back(false);
            }
            if(third && filled && !done){
                this->spring.bCircle = circles[0];
                this->spring.eCircle = circles[1];
                float mag = glm::length(this->spring.bCircle.pos - this->spring.eCircle.pos);
                this->spring.restedLength = mag;
                this->spring.Direction = {0.0f,0.0f};
                this->spring.k = .8;
                // this->spring.endPos = circles[1].pos;
                done = true;
            }
            if(fourth && !done){
                if(firstClick && !secondClick){
                    secondClick = true;
                    firstClick = false;
                    for(const auto& circle:circles){
                        glm::vec2 circlePos = circle.pos;
                        glm::vec2 clickPos = {x,y};
                        float length = glm::length(clickPos - circlePos);
                        if(length <= circle.size){
                            c1.pos = {x,y};
                            springs.push_back({c1,10,{0,0},.8,c2});
                            first = false;
                            DrawText("FirstClickWorks", circlePos.x,circlePos.y,200, BLACK);
                            break;
                        }
                    }
                }
                else if(secondClick && !firstClick){
                    firstClick = true;
                    secondClick = true;

                    for(const auto& circle:circles){
                        glm::vec2 circlePos = circle.pos;
                        glm::vec2 clickPos = {x,y};
                        float length = glm::length(clickPos - circlePos);
                        if(length <= circle.size){
                         springs.back().eCircle.pos = {x,y};
                         DrawText("SecondClickWorks", 500,500,200, GREEN);
                         break;
                        }
                    }
                }
                if(firstClick && secondClick){
                    DrawText("Done",x, 200, 150, BLACK);
                    secondClick = false;
                }
                // GetSpringPos();
            }
            if(fifth && !done){
                DrawCircle(springs.back().bCircle.pos.x,springs.back().bCircle.pos.y, 200,BLACK);
                DrawCircle(springs.back().eCircle.pos.x,springs.back().eCircle.pos.y,200,RED);
            }

        }


        BeginDrawing();

        ClearBackground(RAYWHITE);     

        DrawMovement();

        Gravity();

        Movememnt();

        if(done){
            StartPendulum();
        }

        EndDrawing();
    }

    CloseWindow();
}


void Simulation::Gravity(){
    for(auto& circle : circles){
        if(circle.type == 1 && done){
            circle.velocity += GravConstant;
            circle.pos.y += circle.velocity;
        }
        }
}



void Simulation::Movememnt(){
    int i = 0;
    for(auto& circle : circles){
        circle.pos.y += direction[i].y;
        circle.pos.x += direction[i].x;
        i++;
        }
}






void Simulation::DrawMovement(){
    for(const auto& circle: circles){
        if(circle.type == 0){
            DrawCircle(circle.pos.x,circle.pos.y,circle.size,RED);
        }
        if(circle.type == 1){
            DrawCircle(circle.pos.x,circle.pos.y,circle.size,GREEN);
        }
    }
}


// F = -k * x
void Simulation::StartPendulum(){
    int i = 0;
    int length = spring.restedLength;
    Circle fixed = circles[0];
    for(auto& circle:circles){
        if(!skips[i] && circle.type == 1 && done){
            glm::vec2 dirVector = circle.pos - fixed.pos;
            int x = glm::length(dirVector);
            dirVector = glm::normalize(dirVector);
            x = x - length;
            double k = spring.k;
            double force = -k * x;
            float acc = force / circle.size;
            dirVector = dirVector * acc;
            direction[i] += dirVector;
        }
        i++;
    }
}






void Simulation::GetSpringPos(){
    bool clicked = false;
    bool first = true;
    bool second = false;
    Circle c1;
    Circle c2;
    int clickCount = 0;
    bool wasMouseButtonReleased = false;

    while(!clicked){

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            wasMouseButtonReleased = true;
        }

        if(wasMouseButtonReleased){
            float xpos = GetMouseX();
            float ypos = GetMouseY();
            if(first){
                DrawText("First", xpos,ypos,150,BLUE);
                first = false;
            }
            else{
                DrawText("Second", xpos, ypos, 200, RED);
                clicked = true;
            }
            wasMouseButtonReleased = true;
        }
        wasMouseButtonReleased = false;
    }

    DrawText("DONE", 200,200,100, BLUE);
}







//  if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
//             float xpos = GetMouseX();
//             float ypos = GetMouseY();
//             if (!first && clickCount == 1){
//                 for(const auto& circle:circles){
//                     glm::vec2 circlePos = circle.pos;
//                     glm::vec2 clickPos = {xpos,ypos};
//                     float length = glm::length(clickPos - circlePos);
//                     if(length <= circle.size){
//                         springs.back().eCircle.pos = {xpos,ypos};
//                         clicked = true;
//                         DrawText("SecondClickWorks", 500,500,200, GREEN);
//                         break;
//                     }
//                     clickCount++;
//                 }
//             }
//             else if(first && clickCount == 0){
//                 //Spring(Circle bCircle, int s, glm::vec2 d, double k, Circle eCircle);
//                 for(const auto& circle:circles){
//                     glm::vec2 circlePos = circle.pos;
//                     glm::vec2 clickPos = {xpos,ypos};
//                     float length = glm::length(clickPos - circlePos);
//                     if(length <= circle.size){
//                         c1.pos = {xpos,ypos};
//                         springs.push_back({c1,10,{0,0},.8,c2});
//                         first = false;
//                         DrawText("FirstClickWorks", 300,200,200, BLACK);
//                         break;
//                     }
//                 }
//                 clickCount++;
//             }
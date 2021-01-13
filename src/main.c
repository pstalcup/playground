#include "raylib.h"
#include "inc/scene.h"
#include "inc/scene_battle_map.h"

const int screenWidth = 800; 
const int screenHeight = 600;

int main(void) {
    InitWindow(screenWidth, screenHeight, "pstalcup test"); 
    SetTargetFPS(60); 
    nextScene = &battleMap; 

    while(!WindowShouldClose()) {
        gameLoop(0.0); 
    } 
    CloseWindow();
    return 0; 
}
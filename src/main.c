#include "raylib.h"
#include "inc/game.h"
#include "inc/scene.h"
#include "inc/scene_battle_map.h"

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "pstalcup test"); 
    SetTargetFPS(60); 
    nextScene = &battleMap; 

    while(!WindowShouldClose()) {
        gameLoop(0.0); 
    } 
    CloseWindow();
    return 0; 
}
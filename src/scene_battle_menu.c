
#include "raylib.h"
#include "inc/scene.h"
#include "inc/game.h"

int battle_menu_load() {
    return 0;
}

int battle_menu_update(double delta) {
    int retCode = SCENE_UPDATE_PARENT_RENDER | SCENE_UPDATE_CAPTURE; 
    if (IsKeyDown(KEY_X)) { 
        retCode |= SCENE_UPDATE_POP; 
    }   
    return retCode; 
}

void battle_menu_render() {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){ 130, 130, 130, 150 });
}

int battle_menu_unload() {
    return 0; 
}

Scene battleMenu = SCENE(&battle_menu_load, &battle_menu_update, &battle_menu_render, &battle_menu_unload); 
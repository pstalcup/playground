#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "inc/scene.h"
#include "inc/grid.h"
#include "inc/scene_battle_menu.h"

Rectangle scaledScreen;

int cellSize = 50; 
int borderSize = 2; 
int lastClickedX = 0;
int lastClickedY = 0;
int lastClickedGridX = 0;
int lastClickedGridY = 0;
int mouseX = 0;
int mouseY = 0;
int boxStartX = 0;
int boxStartY = 0;
int boxWidth = 0;
int boxHeight = 0;
int boxStartGridX = -1;
int boxStartGridY = -1;
int boxGridWidth = 0;
int boxGridHeight = 0;
int boxSizeThreshold = 1;

int load(void) {
    scaledScreen = (Rectangle) {0, 0, gridWidth, gridHeight}; 
    SetMouseScale(0.02, 0.02);
    clearGrid(); 
    return 0;
}

void drawGrid(void) {
    SetMouseScale(0.02, 0.02);
    for(int x = 0; x < gridWidth; ++x) {
        for(int y = 0; y < gridHeight; ++y) {
            Color outline = (x == mouseGridX && y == mouseGridY) ? RED : BLACK;
            if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                if ((x >= boxStartGridX) && (x <= boxStartGridX+boxGridWidth) && (y >= boxStartGridY) && (y <= boxStartGridY+boxGridHeight)){
                    outline = RED;
                }
                
            }

            Color fill = WHITE; 
            switch(gridCell(x, y)) {
                case 1: fill = GREEN; break;
                case 2: fill = RED; break; 
            }

            DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, outline); 
            DrawRectangle(x * cellSize + borderSize, y * cellSize + borderSize, cellSize - borderSize * 2, cellSize - borderSize * 2, fill);
        }
    }
}

void drawSelectionBox(void) {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if ((boxWidth < boxSizeThreshold) || (boxHeight < boxSizeThreshold)) {
            return;
        } 
        Rectangle boxRec = (Rectangle) {boxStartX, boxStartY, boxWidth, boxHeight}; 
        DrawRectangleLinesEx(boxRec, 2, YELLOW);
    }
}

int update(double delta) {
    SetMouseScale(1.0, 1.0);
    mouseX = (int) GetMouseX();
    mouseY = (int) GetMouseY();
    SetMouseScale(0.02, 0.02);
    mouseGridX = (int) GetMouseX(); 
    mouseGridY = (int) GetMouseY();

    bool insideScreen = CheckCollisionPointRec(GetMousePosition(), scaledScreen);
    int retCode = 0; 
    
    if (insideScreen) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            lastClickedX = mouseX;
            lastClickedY = mouseY;
            lastClickedGridX = mouseGridX;
            lastClickedGridY = mouseGridY;
        } 
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {

            /* set the box starting location, using the min for x and y guarantees we end up with the top left corner */
            boxStartX = mouseX;
            boxStartY = mouseY;
            if (lastClickedX < boxStartX) boxStartX = lastClickedX;
            if (lastClickedY < boxStartY) boxStartY = lastClickedY;
            
            boxWidth = abs(mouseX - lastClickedX);
            boxHeight = abs(mouseY - lastClickedY);

            /* repeat this for the grid-scaled mouse x,y values so we can determine which cells fall into the selection */
            boxStartGridX = mouseGridX;
            boxStartGridY = mouseGridY;
            if (lastClickedGridX < boxStartGridX) boxStartGridX = lastClickedGridX;
            if (lastClickedGridY < boxStartGridY) boxStartGridY = lastClickedGridY;
            
            boxGridWidth = abs(mouseGridX - lastClickedGridX);
            boxGridHeight = abs(mouseGridY - lastClickedGridY);
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            if ((boxStartGridX) >= 0 && (boxStartGridY >= 0)){
                for(int x = 0; x <= boxGridWidth; x++){ //note boxGridWidth/Height can be 0, which really means 1 cell
                    for(int y = 0; y <= boxGridHeight; y++){
                        setGridCell(boxStartGridX + x, boxStartGridY + y, 0);
                    }
                }
            }
        }
    }
    if (IsKeyDown(KEY_Y)) {
        setGridCell(mouseGridX, mouseGridY, 0);
    }
    if (IsKeyDown(KEY_A)) {
        clearGrid();
    }
    if (IsKeyDown(KEY_S)) {
        if(insideScreen) {
            pathFind(0, 0, mouseGridX, mouseGridY); 
        }
    }
    if (IsKeyDown(KEY_M) && !battleMenu._loaded) {
        nextScene = &battleMenu; 
        retCode = SCENE_UPDATE_PUSH;
    }
    return retCode; // default behavior
}

void render() {
    drawGrid(); 
    drawSelectionBox();
}

int unload() {
    // NOOP
    return 0;
}

Scene battleMap = SCENE(&load, &update, &render, &unload);
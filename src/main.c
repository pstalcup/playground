#include "raylib.h"
#include <stdio.h>
#include "inc/grid.h"

const int screenWidth = 800; 
const int screenHeight = 600;

int pathFindX = -1;
int pathFindY = -1; 

int cellSize = 50; 
int borderSize = 2; 

Rectangle scaledScreen;

void drawGrid(void) {
    for(int x = 0; x < gridWidth; ++x) {
        for(int y = 0; y < gridHeight; ++y) {
            Color outline = (x == mouseGridX && y == mouseGridY) ? RED : BLACK;
            Color fill = WHITE; 
            switch(gridCell(x, y)) {
                case 1: fill = GREEN; break;
                case 2: fill = RED; break; 
            }

            DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, outline); 
            DrawRectangle(x * cellSize + borderSize, y * cellSize + borderSize, cellSize, cellSize, fill);
        }
    }
}

void init(void) {
    scaledScreen = (Rectangle) {0, 0, gridWidth, gridHeight}; 
    SetMouseScale(0.02, 0.02);
    clearGrid(); 
}

void handleInputs(void) {
    mouseGridX = (int) GetMouseX(); 
    mouseGridY = (int) GetMouseY(); 

    bool insideScreen = CheckCollisionPointRec(GetMousePosition(), scaledScreen);
    
    if (insideScreen) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            setGridCell(mouseGridX, mouseGridY, 0); 
        }
    }
    if (IsKeyDown(KEY_A)) {
        clearGrid();
    }
    if (IsKeyDown(KEY_S)) {
        if(insideScreen) {
            pathFind(0, 0, mouseGridX, mouseGridY); 
        }
    }
}

void update(void) {
    if(pathFindX != -1) {
    }
}

void drawFrame(void) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            drawGrid(); 
        EndDrawing();
}

int main(void) {
    InitWindow(screenWidth, screenHeight, "pstalcup test"); 
    SetTargetFPS(60); 
    init(); 

    while(!WindowShouldClose()) {
        handleInputs(); 
        update();
        drawFrame();
    } 
    CloseWindow();
    return 0; 
}
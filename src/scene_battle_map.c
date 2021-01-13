#include "raylib.h"
#include "inc/scene.h"
#include "inc/grid.h"

Rectangle scaledScreen;

int cellSize = 50; 
int borderSize = 2; 

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
            DrawRectangle(x * cellSize + borderSize, y * cellSize + borderSize, cellSize - borderSize * 2, cellSize - borderSize * 2, fill);
        }
    }
}

int load(void) {
    scaledScreen = (Rectangle) {0, 0, gridWidth, gridHeight}; 
    SetMouseScale(0.02, 0.02);
    clearGrid(); 
    return 0;
}

int update(double delta) {
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
    return 0; // default behavior
}

void render(double delta) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            drawGrid(); 
        EndDrawing();
}

int unload() {
    // NOOP
    return 0;
}

Scene battleMap = SCENE(&load, &update, &render, &unload);
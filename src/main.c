#include "raylib.h"
#include <stdio.h>
#include "inc/grid.h"

#define _GRID_WIDTH 16
#define _GRID_HEIGHT 12

const int gridWidth = _GRID_WIDTH;
const int gridHeight = _GRID_HEIGHT;

const int screenWidth = 800; 
const int screenHeight = 600;

int mouseGridX = -1; 
int mouseGridY = -1; 

int grid[_GRID_WIDTH][_GRID_HEIGHT];

Rectangle scaledScreen;

void drawGrid(void) {
    for(int x = 0; x < gridWidth; ++x) {
        for(int y = 0; y < gridHeight; ++y) {
            Color outline = (x == mouseGridX && y == mouseGridY) ? RED : BLACK;
            Color fill = (grid[x][y] == 1) ? GREEN : WHITE; 

            DrawRectangle(x * 50, y * 50, 50, 50, outline); 
            DrawRectangle(x * 50 + 2, y * 50 + 2, 46, 46, fill);
        }
    }
}

void init(void) {
    for(int x = 0; x < gridWidth; ++x) {
        for(int y = 0; y < gridHeight; ++y) {
            grid[x][y] = 1; 
        }
    }

    scaledScreen = (Rectangle) {0, 0, gridWidth, gridHeight}; 
    SetMouseScale(0.02, 0.02);
}

void handleInputs(void) {
    mouseGridX = (int) GetMouseX(); 
    mouseGridY = (int) GetMouseY(); 

    if (CheckCollisionPointRec(GetMousePosition(), scaledScreen)) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            grid[mouseGridX][mouseGridY] = 0; 
        }
    }
}

int main(void) {
    InitWindow(screenWidth, screenHeight, "pstalcup test"); 
    SetTargetFPS(60); 
    init(); 

    while(!WindowShouldClose()) {

        BeginDrawing();
            ClearBackground(RAYWHITE);
            drawGrid(); 
        EndDrawing();
    } 
    CloseWindow();
    return 0; 
}

#include <stdio.h>

#define _GRID_WIDTH 16
#define _GRID_HEIGHT 12

int mouseGridX = -1; 
int mouseGridY = -1; 

const int gridWidth = _GRID_WIDTH;
const int gridHeight = _GRID_HEIGHT;
const int gridSize = gridWidth * gridHeight;

int grid[_GRID_WIDTH * _GRID_HEIGHT];

int distance[_GRID_WIDTH * _GRID_HEIGHT];
int visited[_GRID_WIDTH * _GRID_HEIGHT]; 
int path[_GRID_WIDTH * _GRID_HEIGHT]; 

int pathX[_GRID_WIDTH * _GRID_HEIGHT]; 
int pathY[_GRID_WIDTH * _GRID_HEIGHT]; 

void clearGridForVal(int val) {
    for(int i = 0; i < _GRID_WIDTH * _GRID_HEIGHT; ++i) {
        if(grid[i] == val || val == -1) {
            grid[i] = 1; 
        }
    }
}

void clearGrid(void) {
    clearGridForVal(-1);
}

int gridCell(int x, int y) {
    return grid[y * gridWidth + x]; 
}

void setGridCell(int x, int y, int val) {
    grid[y * gridWidth + x] = val; 
}

void tryIndex(int index, int nextIndex, int computedDistance) {
    if(grid[index] == 1 && index < gridSize && index > 0 && visited[index] < 0 && (distance[index] == -1 || distance[index] > computedDistance)) {
        distance[index] = computedDistance; 
        path[index] = nextIndex; 
    }
}

void pathFind(int startX, int startY, int endX, int endY) {
    clearGridForVal(2);
    int startIndex = startY * gridWidth + startX;
    int endIndex = endY * gridWidth + endX; 

    for(int i = 0;i < gridSize; ++i) {
        distance[i] = -1; 
        visited[i] = -1; 
        path[i] = -1; 
    }
    distance[startIndex] = 0;
    visited[startIndex] = 0;  
    path[startIndex] = -1; 
    
    int nextIndex = startIndex; 
    while(nextIndex != -1 && distance[endIndex] < 0) {
        int computedDistance = distance[nextIndex] + 1;
        visited[nextIndex] = 1; 

        int downIndex = nextIndex + gridWidth; 
        int upIndex = nextIndex - gridWidth; 
        int leftIndex = nextIndex % gridWidth == 0 ? -1 : nextIndex - 1;
        int rightIndex = nextIndex % gridWidth == gridWidth - 1 ? -1 : nextIndex + 1; 
        
        tryIndex(downIndex, nextIndex, computedDistance);
        tryIndex(upIndex, nextIndex, computedDistance);
        tryIndex(leftIndex, nextIndex, computedDistance);
        tryIndex(rightIndex, nextIndex, computedDistance);

        nextIndex = -1; 
        for(int i = 0; i < gridSize; ++i) {
            if(visited[i] < 0 && distance[i] != -1) {
                if(nextIndex < 0 || distance[i] < distance[nextIndex]) {
                    nextIndex = i;
                }
            }
        }
    }

    nextIndex = endIndex; 
    if(path[nextIndex] == -1) {
        grid[startIndex] = 2; 
        grid[endIndex] = grid[endIndex] == 1 ? 2 : grid[endIndex]; 
    }
    do {
        grid[nextIndex] = 2; 
        nextIndex = path[nextIndex]; 
    } while (nextIndex != -1);
    
}
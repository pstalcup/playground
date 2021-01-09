extern int mouseGridX;
extern int mouseGridY;

extern const int gridWidth;
extern const int gridHeight;

extern int grid[];

void clearGrid(void);
int gridCell(int x, int y); 
void setGridCell(int x, int y, int val); 
void pathFind(int startX, int startY, int endX, int endY); 
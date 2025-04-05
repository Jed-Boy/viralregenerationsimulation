#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROWS 15
#define COLS 30
#define GENERATIONS 50
#define ALIVE '1'
#define DEAD  '.'


void initializeGrid(char grid[ROWS][COLS]);
void displayGrid(char grid[ROWS][COLS]);
int countLiveNeighbors(char grid[ROWS][COLS], int x, int y);
void nextGeneration(char current[ROWS][COLS], char next[ROWS][COLS]);

int main() {
    char grid[ROWS][COLS];
    char newGrid[ROWS][COLS];

    initializeGrid(grid);

    for (int gen = 0; gen < GENERATIONS; gen++) {
        system("clear"); 
        printf("New Generation %d\n", gen + 1);
        displayGrid(grid);
        nextGeneration(grid, newGrid);

        
        for (int i = 0; i < ROWS; i++)
            for (int j = 0; j < COLS; j++)
                grid[i][j] = newGrid[i][j];

        usleep(400000); 
    }

    return 0;
}

void initializeGrid(char grid[ROWS][COLS]) {
    
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            grid[i][j] = (rand() % 4 == 0) ? ALIVE : DEAD;
}

void displayGrid(char grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            putchar(grid[i][j]);
        putchar('\n');
    }
}

int countLiveNeighbors(char grid[ROWS][COLS], int x, int y) {
    int liveCount = 0;
    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS)
                if (grid[nx][ny] == ALIVE)
                    liveCount++;
        }
    return liveCount;
}

void nextGeneration(char current[ROWS][COLS], char next[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++) {
            int liveNeighbors = countLiveNeighbors(current, i, j);
            if (current[i][j] == ALIVE) {
                if (liveNeighbors < 2 || liveNeighbors > 3)
                    next[i][j] = DEAD;
                else
                    next[i][j] = ALIVE;
            } else {
                if (liveNeighbors == 3)
                    next[i][j] = ALIVE;
                else
                    next[i][j] = DEAD;
            }
        }
}
    
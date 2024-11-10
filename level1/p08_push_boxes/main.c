#include <stdio.h>
#include <stdlib.h>

#define MAX_LEVELS 3
#define MAX_MAP_SIZE 20

#define PLAYER '@'
#define BOX '$'
#define STORAGE '*'
#define EMPTY ' '

int playerX=1;
int playerY=1;

char map[MAX_MAP_SIZE][MAX_MAP_SIZE];
int rows=6, cols=15;

int steps = 0;
int score = 0;

void displayMap() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

void move(int dx, int dy) {
    int newX = playerX + dx;
    int newY = playerY + dy;
    if (map[newX][newY] == BOX) {
        int boxNewX = newX + dx;
        int boxNewY = newY + dy;
        if (boxNewX >= 0 && boxNewX < rows && boxNewY >= 0 && boxNewY < cols && map[boxNewX][boxNewY] == EMPTY) {
            map[boxNewX][boxNewY] = BOX;
            map[newX][newY] = PLAYER;
            map[playerX][playerY] = EMPTY;
            playerX = newX;
            playerY = newY;
        }
    } else if (map[newX][newY] == EMPTY||map[newX][newY]==STORAGE) {
        map[newX][newY] = PLAYER;
        map[playerX][playerY] = EMPTY;
        playerX = newX;
        playerY = newY;
    }
    steps++;
}

int isGameOver() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (map[i][j] == BOX && map[i][j] != STORAGE) {
                return 0;
            }
        }
    }
    return 1;
}

void loadLevel(int level) {
    char filename[20];
    sprintf(filename, "maze%d.txt", level);
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open level file.\n");
        exit(1);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fscanf(file,"%c",map[i][j]);
        }
        fscanf(file,"\n");//在这里加入一个读取换行符的操作
    }
    fclose(file);
}

void saveScore(int level, int score) {
    char filename[20];
    sprintf(filename, "scores.txt");
    FILE *file = fopen(filename, "a");
    if (!file) {
        printf("Failed to open scores file.\n");
        exit(1);
    }
    fprintf(file, "Level %d: %d steps\n", level, score);
    fclose(file);
}

int main() {
    char command;
    int level = 1;
    while (level <= MAX_LEVELS) {
        loadLevel(level);
        steps = 0;
        while (!isGameOver()) {
            displayMap();
            printf("Move with W (up), A (left), S (down), D (right), Q (quit): ");
            scanf(" %c", &command);
            switch (command) {
                case 'w': move(-1, 0); break;
                case 'a': move(0, -1); break;
                case 's': move(1, 0); break;
                case 'd': move(0, 1); break;
                case 'q': exit(0);
                default: printf("Invalid command.\n"); break;
            }
        }
        score=steps;
        printf("Congratulations, you've won!\n");
        saveScore(level, score);
        level++;
    }
    return 0;
}

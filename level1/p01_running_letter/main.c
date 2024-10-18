#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>
void presentation();
int x_num, y_num;
char location[10][20];
char letter;
int main() {

    printf("ÇëÊäÈëÒ»¸ö×ÖÄ¸£º");
    scanf_s("%c", &letter);
    system("cls");
    Sleep(100);
    presentation();
}
void new_map() {
    for (int i = 0; i <= 9; i++) {
        if (i == 0 || i == 9) {
            for (int j = 0; j <= 19; j++) {
                location[i][j] = '*';
            }
        }
        else {
            for (int j = 0; j <= 19; j++) {
                if (j == 0 || j == 19) {
                    location[i][j] = '*';
                }
                else {
                    location[i][j] = ' ';
                }
            }
        }
        printf("\n");
    }
    x_num = 1, y_num = 1;
    location[1][1] = letter;
}
void move() {
    location[x_num][y_num] = ' ';
    if (y_num == 18) {
        x_num++;
        y_num = 1;
    }
    else {
        y_num++;
    }
    location[x_num][y_num] = letter;
}
void display() {
    system("cls");
    Sleep(1000);
    for (int i = 0; i <= 9; i++) {
        for (int j = 0; j <= 19; j++) {
            printf("%c",location[i][j]);
        }
        printf("\n");
    }
}
void presentation() {
    new_map();
    while (true) {
        move();
        display();
        Sleep(100);
        if(x_num==8&&y_num==18){
            break;
        }
    }
}
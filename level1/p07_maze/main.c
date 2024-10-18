#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

char a[6][11] = {
        {'@', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#'},
        {'#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' '}
};
int x_position=0;
int y_position=0;
int x_exit_position=10;
int y_exit_position=5;

void display(char x[6][11]){
    system("cls");
    for(int i=0;i<6;i++){
        for(int j=0;j<11;j++){
            printf("%c",x[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void move(char x[6][11]){
    while(true){
        char op=getchar();
        if(op=='d'&&x_position<11){
            x_position++;
        }else if(op=='a'&&x_position>=0){
            x_position--;
        }else if(op=='w'&&y_position<11){
            y_position++;
        }else{
            y_position--;
        }
        if(x_position==x_exit_position&&y_position==y_exit_position){
            printf("you win the game!");
            break;
        }
        x[x_position][y_position]='@';
        display(x);
        x[x_position][y_position]=' ';
        Sleep(1000);
    }
}

int main(){
    display(a);
    move(a);
    return 0;
}






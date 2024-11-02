#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char maze[10][10];
char people_position;
char box_position;

void load(int value){
    char name[100];
    sprintf(name,"maze%d.txt",value);
    FILE*file=fopen("name","r");
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            fscanf(file,"%c",&maze[i][j]);
            //用scanf给数组赋值时，还是要加取地址符的，原因是给数组赋值，
            //如果只涉及数组，那其实数组的单个元素就可以看成是一个单独的int型变量
            //自然用scanf时要用取地址运算符，printf时用数组即可
            //数组名代笔数组首个元素的地址，通过对数组名自增就能实现对数组的初始化
            //然后打印时只需要用解引用运算符即可
        }
    }
    fclose(file);
}

void display(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            printf("%c",maze[i][j]);
        }
        printf("\n");
    }
}

void move(char ch){
    switch(ch){
        case 'w':
    }
}

void check(){

}

int main(){

}


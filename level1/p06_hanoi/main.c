#include <stdio.h>
void solution(int n,char source,char target,char help);
int main(){
    solution(4,'A','C','B');
}
void solution(int n,char source,char target,char help) {
    if (n == 1) {
        printf("%c->%c\n",source,target);
    }
    else{
        solution(n-1,source,help,target);
        printf("%c->%c\n",source,target);
        solution(n-1,help,target,source);
    }
}

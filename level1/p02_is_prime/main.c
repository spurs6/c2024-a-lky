#include <stdio.h>

int main() {
    int n=0,count=1;
    scanf("%d",&n);
    for(int i=2;i<n;i++){
        if(n%i==0){
            count=0;
            break;
        }
    }
    if(count==1){
        printf("%d������",n);
    }
    else{
        printf("%d��������",n);
    }


    return 0;
}
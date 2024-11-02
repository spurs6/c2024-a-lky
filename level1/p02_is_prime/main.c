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
        printf("%d is prime number!",n);
    }
    else{
        printf("%d is not prime number!",n);
    }


    return 0;
}
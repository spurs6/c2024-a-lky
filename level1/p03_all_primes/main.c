#include <stdio.h>
#include <time.h>
#include <math.h>
int main() {
    time_t start=time(NULL);
    clock_t start1=clock();
    for(int i=2;i<=1000;i++){
        int count=1;
        int x=(int) sqrt((double) i);
        for(int j=2;j<=x;j++){
            if(i%j==0) {
                count = 0;
                break;
            }
        }
        if(count==1){
            printf("%d\n",i);
        }
    }
    clock_t end1=clock();
    time_t end=time(NULL);
    double time_used=difftime(end,start);
    printf("%ld\n",(long)time_used);
    double cpu_time_used=(double) (end1-start1)/CLOCKS_PER_SEC;
    printf("%f\n",cpu_time_used);
    return 0;
}

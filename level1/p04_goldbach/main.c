#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int prime(int n);
int main() {
    int x;
    scanf_s("%d", &x);//任何大于2的偶数都能拆解成两个素数
    for (int i = 1; i <= x / 2; i += 2) {
        if (prime(i) && prime(x - i)) {
            printf("%d %d\n", i, x - i);
        }
    }
    system("pause");
}
int prime(int n) {
    int x = (int) sqrt(n);
    for (int i = 2; i <= x; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}


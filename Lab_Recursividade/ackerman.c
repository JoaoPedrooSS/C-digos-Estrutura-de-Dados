#include <stdio.h>

int ackerman(int, int);

int main(){
    printf("Insira dois numeros: ");
    int a, b;
    scanf("%d", &a);
     scanf("%d", &b);
     int res = ackerman(a, b);

     printf("o resultado eh %d", res);

     return 0;
}
int ackerman(int a, int b){
    if(a == 0){
        return b + 1;
    }else if(b == 0 && a > 0){
        return ackerman(a - 1, 1);
    }else if (a > 0 && b > 0){
        return ackerman(a - 1, ackerman(a, b-1));
    }
}
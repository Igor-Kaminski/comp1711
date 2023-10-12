#include <stdio.h>

int main(){
    int num1;
    int num2;
    int total;
    printf("WRITE 2 INTEGERS, FIRST ONE THEN ANOTHER\n");
    scanf("%d", &num1);
    scanf("%d", &num2);
    total = num1+ num2;
    printf ("The sum of adding %d and %d is %d\n", num1 , num2, total);
    return 0;

}
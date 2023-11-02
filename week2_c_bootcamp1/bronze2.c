#include <stdio.h>

int main(){

    int num;
    printf("Please enter a number\n");
    scanf("%d",&num);

    if (num%4==0 && num%5==0)
    {
        printf("The num %d is divisble by 4 and 5\n", num);
    }
    else if (num%4==0)
    {
        printf("The num %d is divisble only by 4\n", num);

    }
    else if (num%5==0)
    {
        printf("The num %d is divisble only by 5\n", num);

    }
    else
    {
        printf("The num %d is not divisble by 4 or 5\n", num);

    }
    return 0;
}
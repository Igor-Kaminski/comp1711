#include <stdio.h>

int main(){
    int num;
    printf("Enter a number:\n");
    scanf("%d",&num);
    if (num==0)
    {
        printf("The number %d is zero\n", num);
    }
    else if (num>0)
    {
        printf("The number %d is postive\n",num);
    }
    else
    {
        printf("The number %d is negative\n", num);
    }
    return 0;
}
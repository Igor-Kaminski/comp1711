#include <stdio.h>

int main(){
    int temp;
    printf("Please enter a temp\n");
    scanf("%d",&temp);

    if (temp>=-10 && temp<=40)
    {
        printf("The temp of %d is within the range\n", temp);
    }
    else
    {
        printf("The temp of %d is not within the range\n", temp);

    }
    
    return 0;
}
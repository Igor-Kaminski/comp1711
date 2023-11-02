#include <stdio.h>

int main(){
    int array[5] = {1,2,3,4,5};
    int a;
    int sum=0;

    for (a=0; a<5;a++)
    {
        sum += array[a];
    }
    printf("The total sum of the array is %d\n",sum);
    return 0;
}
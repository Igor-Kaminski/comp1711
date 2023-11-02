#include <stdio.h>

int main(){
    int mark;
    printf("Please enter a mark\n");
    scanf("%d",&mark);

    if (mark>=50 && mark<70)
    {
        printf("The mark of %d is a pass mark\n", mark);
    }
    else if (mark>=70)
    {
        printf("The mark of %d is a distinction\n", mark);

    }
    else
    {
        printf("The mark of %d is a fail\n", mark);
    }
    return 0;
}
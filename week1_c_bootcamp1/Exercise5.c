#include <stdio.h>

int main(){
    float a,b,temp;
    printf("Input two numbers and they will swap.");
    scanf("%f",&a);
    scanf("%f",&b);
    temp = a;
    a=b;
    b=temp;
    
   
    printf("The variables swapped are now in order %f and %f", a,b);

    return 0;



}
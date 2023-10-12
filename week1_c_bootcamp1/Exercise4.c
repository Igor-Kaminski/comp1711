#include <stdio.h>

int main(){
    float pi,area,radius;
    printf("Input radius of circle to get area.");
    scanf("%f",&radius);
    pi = 3.14;
    area = radius * radius * pi;

    printf("The area of the circle is: %.2f\n", area);

    return 0;



}
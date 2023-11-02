#include <stdio.h>
int main() {
    float side1;
    float side2;
    float area;
    printf("Hello, please enter side 1 of rectangle: ");
    scanf("%f", &side1);
    printf("Hello, please enter side 2 length of rectnagle:");
    scanf("%f", &side2);
    area=side1*side2;
    printf ("The area of rectnagle with sides %f and %f is %2.f\n", side1 , side2, area);
    return 0;
}
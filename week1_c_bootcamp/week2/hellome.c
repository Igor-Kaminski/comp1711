#include <stdio.h>
int main() {
    char name[2000];
    printf("Hello, please enter your name:");
    scanf("%s", name);
    printf("Your name is %s\n", name);
    return 0;
}
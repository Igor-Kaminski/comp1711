#include <stdio.h> <string.h>
int main() {
    char word[100];
    
    printf("GIVE STRING");
    scanf("%s",&word);
    printf("REVERSE OF STRING IS =%s",strrev(word));
    return 0;
}
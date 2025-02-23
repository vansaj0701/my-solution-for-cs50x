#include <stdio.h>

int main(void)
{
    char name[25];
    printf("What's your name? ");
    scanf("%s", name);

    printf("hello, %s\n", name);
}

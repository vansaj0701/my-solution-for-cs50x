#include <cs50.h>
#include <stdio.h>

void block(int height);

int main(void)
{
    int height;
    do
    {
        printf("Height: ");
        scanf("%d", &height);
    }
    while (height <= 0 || height > 8);
    block(height);
}

void block(int height)
{
    for (int i = 0; i <= height - 1; i++)
    {
        for (int j = 2; j <= height - i; j++)
        {
            printf(" ");
        }

        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}

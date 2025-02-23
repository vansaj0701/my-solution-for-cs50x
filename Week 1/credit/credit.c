#include <stdio.h>
#include <string.h>

int validity(char number[], int length);
int checkCards(char number[], int length);

int main()
{
    char number[20];

    printf("Number: ");
    scanf("%s", number);

    int length = strlen(number);

    if (validity(number, length) == 0)
    {
        checkCards(number, length);
    }

    else
    {
        printf("INVALID\n");
    }
}

int checkCards(char number[], int length)
{
    if (strncmp(number, "34", 2) == 0 || strncmp(number, "37", 2) == 0)
    {
        if (length == 15)
        {
            printf("AMEX\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }

    if (number[0] == '5')
    {
        if (length == 16)
        {

            for (int i = 1; i <= 5; i++)
            {
                if (number[1] == ((char) i + '0'))
                {
                    printf("MASTERCARD\n");
                    return 0;
                }
                else
                {
                    continue;
                }
            }
        }

        else
        {
            printf("INVALID\n");
            return 0;
        }
    }

    if (number[0] == '4')
    {
        if (length == 13 || length == 16)
        {
            printf("VISA\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }

    else
    {
        printf("INVALID\n");
        return 0;
    }

    return 0;
}

int validity(char number[], int length)
{
    int digit, sum = 0;
    for (int i = length - 2; i >= 0; i = i - 2)
    {
        digit = (number[i] - '0') * 2;

        if (digit >= 10)
        {
            while (digit != 0)
            {
                int remainder = digit % 10;
                sum += remainder;
                digit = digit / 10;
            }
        }

        else
        {
            sum += digit;
        }
    }

    for (int j = length - 1; j >= 0; j = j - 2)
    {
        int digit2 = (number[j] - '0');
        sum += digit2;
    }

    if (sum % 10 == 0)
    {
        return 0;
    }

    return 1;
}

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int encrypt(char plainText[], char key[]);
int validation(char text[]);

int main(int argc, char *argv[])
{
    char plainText[100];

    if (argc != 2)
    {
        printf("Exactly one command-line argument is required\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must have 26 characters\n");
        return 1;
    }

    int validate = validation(argv[1]);

    if (validate != 0)
    {
        return 1;
    }
    else
    {
        printf("Plain Text: ");
        fgets(plainText, sizeof(plainText), stdin);
        plainText[strcspn(plainText, "\n")] = '\0';

        encrypt(plainText, argv[1]);
    }
}

int validation(char text[])
{
    char temp[26];

    for (int alpha = 0; alpha < 26; alpha++)
    {
        if (isalpha(text[alpha]) == 0)
        {
            printf("Key must contain letters only\n");
            return 1;
        }
        for (int dup = 0; dup < 26; dup++)
        {
            if (tolower(text[alpha]) == temp[dup])
            {
                printf("Key must not contain duplicate letters\n");
                return 1;
            }
        }

        temp[alpha] = tolower(text[alpha]);
    }
    return 0;
}

int encrypt(char plainText[], char key[])
{
    char cipherText[strlen(plainText) + 1];
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0, n = strlen(plainText); i < n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (isalpha(plainText[i]) != 0)
            {
                if (isspace(plainText[i]) != 0)
                {
                    cipherText[i] = ' ';
                }

                else if (tolower(plainText[i]) == alphabet[j])
                {

                    if (islower(plainText[i]) != 0)
                    {

                        cipherText[i] = tolower(key[j]);
                    }

                    else
                    {
                        cipherText[i] = toupper(key[j]);
                    }
                }
            }
            else
            {
                cipherText[i] = plainText[i];
            }
        }
        cipherText[strlen(plainText)] = '\0';
    }
    printf("ciphertext: %s\n", cipherText);

    return 0;
}

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calculatePlayer1Score(char p1[]);
int calculatePlayer2Score(char p2[]);

struct Scrabble
{
    char alphabet;
    int points;
};

struct Scrabble scrabble[26] = {
    {'A', 1}, {'B', 3}, {'C', 3}, {'D', 2}, {'E', 1}, {'F', 4}, {'G', 2}, {'H', 4},  {'I', 1},
    {'J', 8}, {'K', 5}, {'L', 1}, {'M', 3}, {'N', 1}, {'O', 1}, {'P', 3}, {'Q', 10}, {'R', 1},
    {'S', 1}, {'T', 1}, {'U', 1}, {'V', 4}, {'W', 4}, {'X', 8}, {'Y', 4}, {'Z', 10}};

int main(void)
{
    char player1[50], player2[50];

    printf("Player 1: ");
    scanf("%s", player1);

    printf("Player 2: ");
    scanf("%s", player2);

    int player1Score = calculatePlayer1Score(player1);
    int player2Score = calculatePlayer2Score(player2);

    if (player1Score > player2Score)
    {
        printf("Player 1 wins!\n");
    }

    else if (player1Score < player2Score)
    {
        printf("Player 2 wins!\n");
    }

    else
    {
        printf("Tie!\n");
    }
}

int calculatePlayer1Score(char p1[])
{
    int player1Score = 0;

    for (int i = 0; i < strlen(p1); i++)
    {
        char upper = toupper(p1[i]);

        for (int j = 0; j <= 26; j++)
        {
            if (upper == scrabble[j].alphabet)
            {
                player1Score += scrabble[j].points;
            }
        }
    }
    return player1Score;
}

int calculatePlayer2Score(char p2[])
{
    int player2Score = 0;

    for (int m = 0; m < strlen(p2); m++)
    {
        char upper = toupper(p2[m]);

        for (int n = 0; n <= 26; n++)
        {
            if (upper == scrabble[n].alphabet)
            {
                player2Score += scrabble[n].points;
            }
        }
    }

    return player2Score;
}

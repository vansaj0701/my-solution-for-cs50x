#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int gradeLevel(int wc, int lc, int sc);

int main(void)
{
    string s = get_string("Text: ");

    int letterCount = 0, wordCount = 0, sentenceCount = 0, count = 0;

    while (count < strlen(s))
    {

        if (isalpha(s[count]) != 0)
        {
            letterCount++;
        }

        if (s[count] == ' ')
        {
            wordCount++;
        }

        if (s[count] == '.' || s[count] == '!' || s[count] == '?')
        {
            sentenceCount++;
        }

        count++;
    }
    wordCount += 1;

    int grade = gradeLevel(wordCount, letterCount, sentenceCount);

    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }

    else if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %d\n", grade);
    }
}

int gradeLevel(int wc, int lc, int sc)
{
    float L = (lc / (float) wc) * 100;
    float S = (sc / (float) wc) * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    return index;
}

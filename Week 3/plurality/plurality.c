#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int count = 0; count < candidate_count; count++)
    {
        if (strcmp(candidates[count].name, name) == 0)
        {
            candidates[count].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max = 0, i = 0;
    string winner[MAX];

    for (int vote_count = 0; vote_count < candidate_count; vote_count++)
    {
        if (candidates[vote_count].votes > max)
        {
            max = candidates[vote_count].votes;
            winner[i] = candidates[vote_count].name;
        }

        else if (candidates[vote_count].votes == max)
        {
            i++;
            winner[i] = candidates[vote_count].name;
        }
    }

    for (int win = 0; win <= i; win++)
    {
        printf("%s\n", winner[win]);
    }
    return;
}

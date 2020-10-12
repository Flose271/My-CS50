#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];
pair sorted_pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int voter_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void show_pairs(void);
void preferences_table(void);
void locked_table(void);
bool rowcycle(bool matrix[][MAX], int row);
bool cycle(bool matrix[][MAX]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    preferences_table();

    add_pairs();

    show_pairs();

    sort_pairs();

    show_pairs();

    lock_pairs();

    locked_table();

    print_winner();
    return 0;

}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if(i != j)
            {
                for (int k = 0; k < candidate_count; k++)
                {
                    if(ranks[k] == i)
                    {
                        preferences[i][j] += 1;
                        break;
                    }
                    if(ranks[k] == j)
                    {
                        break;
                    }

                }
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair new_pair;
                new_pair.winner = i;
                new_pair.loser = j;
                pairs[pair_count] = new_pair;
                pair_count += 1;
            }
            if (preferences[j][i] > preferences[i][j])
            {
                pair new_pair;
                new_pair.winner = j;
                new_pair.loser = i;
                pairs[pair_count] = new_pair;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int sorted_pairs_added = 0;
    for (int i = voter_count; i > 0; i += -1)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] == i)
            {
                sorted_pairs[sorted_pairs_added] = pairs[j];
                sorted_pairs_added += 1;
            }
        }
    }

    for (int i = 0; i < pair_count; i++)
    {
        pairs[i] = sorted_pairs[i];
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[sorted_pairs[i].winner][sorted_pairs[i].loser] = true;

        if(cycle(locked))
        {
            locked[sorted_pairs[i].winner][sorted_pairs[i].loser] = false;
        }

    }
    return;
}

// Print the winner of the election
void print_winner(void)
{

    for(int col = 0; col < candidate_count; col++)
    {
        bool noarrows = true;
        for (int row = 0; row < candidate_count; row++ )
        {
            if(locked[row][col] == true)
            {
                noarrows = false;
            }
        }
        if(noarrows)
        {
            printf("%s\n", candidates[col]);
        }
    }
    return;

}

bool rowcycle(bool matrix[][MAX], int row)
{
    bool access[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        access[i] = matrix[row][i];
    }

    for (int n = 0; n < candidate_count; n++)
    {
        for (int col = 0; col < candidate_count; col++)
        {
            if (access[col] == true)
            {
                for (int j = 0; j < candidate_count; j++)
                {
                    if (matrix[col][j] == true)
                    {
                        access[j] = true;
                    }
                }
            }
        }
    }

    return access[row];
}

bool cycle(bool matrix[][MAX])
{
    for (int row = 0; row < candidate_count; row++)
    {
        if(rowcycle(matrix,row) == true)
        {
            return true;
        }
    }
    return false;
}

void show_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        printf("Pair Winner: %i\n", pairs[i].winner);
        printf("Pair Loser: %i\n", pairs[i].loser);
    }
    printf("----------\n");
    return;
}

void preferences_table(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i\n", preferences[i][j]);
        }
    }
    printf("----------\n");
    return;
}

void locked_table(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%i", locked[i][j]);
        }
        printf("\n");
    }
    printf("----------\n");
    return;
}
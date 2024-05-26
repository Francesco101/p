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
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

bool forming_cycle(bool check, int current_candidate, int recursion_count); // added by me


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
    int voter_count = get_int("Number of voters: ");

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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // If the vote matches the name of the candidate (case-sensitive)
        if (strcmp(name, candidates[i]) == 0)
        {
            // Update ranks[rank] equals to the index corresponding to the candidate voted
            ranks[rank] = i;
            return true;
        }
    }

    // If the vote is invalid
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}


// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Implementation of bubble sort method
    pair memo[0];
    int swap_count = -1;
    while (swap_count != 0)
    {
        swap_count = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            int strenght1 = preferences[pairs[i].winner][pairs[i].loser];
            int strenght2 = preferences[pairs[i + 1].winner][pairs[i + 1].loser];
            // If they're not in decreasing order
            if (strenght1 < strenght2)
            {
                // swap them
                memo[0] = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = memo[0];
                swap_count++;
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        // If locking would create a cycle
        if (forming_cycle(false, pairs[i].winner, 0) == true)
        {
            // Reset lock to false
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // For each candidate (i)
    for (int i = 0; i < candidate_count; i++)
    {
        // Reset is_winner to true
        bool is_winner = true;
        // For eack candiate (j)
        for (int j = 0; j < candidate_count; j++)
        {
            // If the (candidate = j) is locked into (candidate = i)
            if (locked[j][i] == true)
            {
                // Then (candidate = i) cannot be the winner, because somebody wins over him.
                is_winner = false;
            }
        }
        if (is_winner)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

// Added by me
// returns false if locking would create a cycle.
bool forming_cycle(bool check, int current_candidate, int recursion_count)
{
    // If (check is true OR the recursion_count is grater than the candidat_count meaning that a cycle has formed.)
    if (check == true || recursion_count > candidate_count)
    {
        return true;
    }

    // For each pair
    for (int i = 0; i < pair_count; i++)
    {
        // If the current_candidate matches any of the pairs[].winners
        if (pairs[i].winner == current_candidate)
        {
            for (int j = 0; j < candidate_count; j++)
            {
                // If there the current candidate is locked into another (candidate = j)
                if (locked[current_candidate][j] == true)
                {
                    // If a cycle is formed
                    if (forming_cycle(false, j, recursion_count + 1) == true)
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

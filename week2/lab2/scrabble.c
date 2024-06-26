#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
        return 0;
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
        return 0;
    }
    printf("Tie!\n");
    return 0;
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int score = 0;
    int lenght = strlen(word);
    for (int i = 0; i < lenght; i++)
    {
        // If the charcter word[i] is in the alphabet.
        if (isalpha(word[i]))
        {
            word[i] = toupper(word[i]);
            // Initializes n = index of the char in the alphabet.
            // 65 being the decimal corresponding to A in the aplhabet.
            // So that n of char A will be 0
            int n = word[i] - 65;
            score += POINTS[n];
        }
    }
    return score;
}

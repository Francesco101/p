#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

float count_words(string txt);
float count_letters(string txt);
float count_sentences(string txt);
// Function grade_formula returns a negative int whenever the grade calculated is lower than 1;
// and returns 0 whenever the grade calculated is higher than 16;
// if the grade is in between 1 and 16 then the grade itslef is returned (positive int).
int grade_formula(float wc, float lc, float sc);

int main(void)
{
    // Ask the user to input the text
    string text = get_string("Text: ");


    int textgrade = grade_formula(count_words(text), count_letters(text), count_sentences(text));

    switch (textgrade)
    {
        case -1:
            printf("Before Grade 1\n");
            break;
        case 0:
            printf("Grade 16+\n");
            break;
        default:
            printf("Grade %i\n", textgrade);
            break;
    }

    return 0;
}

float count_words(string txt)
// spaces separate words
{
    unsigned int wordscount = 0;
    unsigned int len = strlen(txt);
    // Excluding the first and the last character of the string
    for (int i = 1; i < len - 1; i++)
    {
        // ASCII for ' ' = dec32
        if (txt[i] == 32)
        {
            if (txt[i - 1] != 32)
            {
                wordscount++;
            }
        }
    }
    // Returns wordscount + 1 beacause counting the number of spaces is equale to the
    // number of words - 1.
    return wordscount + 1;
}

float count_letters(string txt)
{
    unsigned int letterscount = 0;
    unsigned int len = strlen(txt);

    for (int i = 0; i < len; i++)
    {
        // Counts the numbers of letters in the text
        if (isalpha(txt[i]))
        {
            letterscount++;
        }
    }

    return letterscount;
}

float count_sentences(string txt)
// {'.'; '!'; '?'} separate sentences
{
    unsigned int sentscount = 0;
    unsigned int len = strlen(txt);
    //ignores the first character
    for (int i = 1; i < len; i++)
    {
        // ASCII for: '.' = dec46; '!' = dec33; '?' = 63.
        if (txt[i] == 46 || txt[i] == 33 || txt[i] == 63)
        {
            if (txt[i - 1] != 46 && txt[i - 1] != 33 && txt[i - 1] != 63)
            {
                sentscount++;
            }
        }
    }

    return sentscount;
}



int grade_formula(float wc, float lc, float sc)
// wc = words count
// lc = letters count
// sc = sentences count
// FORMULA: [ index = 0.0588 * lavg - 0.296 * savg - 15.8 ]
// lavg is the average number of letters per 100 words
// savg is the average number of sentences per 100 words in the text
{
    float lavg = lc * 100 / wc;
    float savg = sc * 100 / wc;
    // Formula:
    float grade = 0.0588 * lavg - 0.296 * savg - 15.8;

    if (grade < 1)
    {
        return -1;
    }
    // 16 is the highest grade in USA.
    else if (grade > 16)
    {
        return 0;
    }

    return round(grade);
}

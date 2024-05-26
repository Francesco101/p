#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int check_key(int count, string *arg);
unsigned int get_key(string arg);
string text_to_cipher(unsigned int key, string ptext);

int main(int argc, string argv[])
{
    // checks that argument is valid.
    if (check_key(argc, argv))
    {
        return 1;
    }

    // initialize (unsigned int) key
    unsigned int key = get_key(argv[1]);
    // initialize plaintext from user input
    string plaintext = get_string("plaintext: ");
    // initialize ciphertext
    string ciphertext = text_to_cipher(key, plaintext);
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}


int check_key(int count, string *arg)
{
    // checks that there are two arguments
    if (count == 2)
    {
        // loop to inspect each caracter of key
        for (int i = 0, l = strlen(arg[1]); i < l; i++)
        {
            if (!(isdigit(arg[1][i])))
            {
                // If key is not made of digits only, return error.
                printf("Usage: ./ceasar key\n***Error: unexpected char, key accepts digits only***\n");
                return 1;
            }
        }
        return 0;
    }
    // if there is only one argv or there are more than 2 return Error.
    printf("usage: ./caesar key\n***Error: *caesar accepts only one argument: key***\n");
    return 1;
}

unsigned int get_key(string arg)
{
    unsigned int k = 0;
    for (int i = 0, pw = strlen(arg) - 1; i <= pw; i++)
    {
        // 48 is the decimal value of '0' in ASCII chart
        k += (arg[i] - 48) * pow(10, pw - i);
    }
    return k;
}

string text_to_cipher(unsigned int key, string ptext)
{
    string cpt = ptext;
    //
    for (int i = 0, l = strlen(ptext); i < l; i++)
    {
        if (isalpha(ptext[i]))
        {
            if (isupper(ptext[i]))
            {
                // 26 is the number of letter in the alphabet
                // 65 is the decimal value for 'A' in ASCII chart
                cpt[i] = (ptext[i] + key - 65) % 26 + 65;
            }
            else
            {
                // 97 is the decimal value for 'a' in ASCII chart
                cpt[i] = (ptext[i] + key - 97) % 26 + 97;
            }
        }
        cpt[i] = ptext[i];
    }
    return cpt;
}

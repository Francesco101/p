#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LETTERSINALPHA 26

int check_argc(int c);
int check_key_lenght(short int l);
int check_no_repetitions(string arg);
int key_is_valid(int count, string k);
string turn_into_ciphertext(string key, string txt, string ciphtxt);

int main(int argc, string argv[])
{
    // Returns error message if failed.
    if (key_is_valid(argc, argv[1]))
    {
        return 1;
    }
    // Get plaintext from user input
    string plaintext = get_string("plaintext: ");
    string ciphertext = plaintext;
    // Print ciphertext
    printf("ciphertext: %s\n", turn_into_ciphertext(argv[1], plaintext, ciphertext));

    return 0;
}


int check_argc(int c)
{
    if (c == 2)
    {
        return 0;
    }
    return 1;
}

int check_key_lenght(short int l)
{
    if (l == LETTERSINALPHA)
    {
        return 0;
    }
    return 1;
}

int check_no_repetitions(string arg)
{
    for (int i = 0; i < LETTERSINALPHA; i++)
    {
        for (int j = i + 1; j < LETTERSINALPHA - 1; j++)
        {
            if (arg[i] == arg[j])
            {
                return 1;
            }
        }
    }
    return 0;
}

int key_is_valid(int count, string k)
{
    if (check_argc(count))
    {
        // Error message
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (check_key_lenght(strlen(k)))
    {
        // Error message
        printf("key must contain %i characters.\n", LETTERSINALPHA);
        return 1;
    }
    else if (check_no_repetitions(k))
    {
        // Error message
        printf("key must not containt repeated characters.\n");
        return 1;
    }
    for (int i = 0; i < LETTERSINALPHA; i++)
    {
        if (!(isalpha(k[i])))
        {
            // Error message
            printf("key must contain alphabet letters only.\n");
            return 1;
        }
    }
    // Then key is valid:
    return 0;
}
// Returns a string containing the cipher text
string turn_into_ciphertext(string key, string txt, string ciphtxt)
{
    int len = strlen(txt);
    for (int i = 0; i < len; i++)
    {
        if isalpha(txt[i])
        {
            if islower(txt[i])
            {
                // In ASCII chart lower case 'a' is in place dec97.
                short int n = txt[i] - 97;
                ciphtxt[i] = tolower(key[n]);
            }
            else
            {
                // in ASCII chart upper case 'A' is in place dec65.
                short int n = txt[i] - 65;
                ciphtxt[i] = toupper(key[n]);
            }

        }
        else
        {
            // The characters is copied as it is (because it is not an alphabet letter)
            ciphtxt[i] = txt[i];
        }
    }

    return ciphtxt;
}

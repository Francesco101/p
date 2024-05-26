#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get the name of the user (function found in <cs50.h>)
    string name = get_string("What's your name? ");
    printf("Hello, %s!\n", name);
}
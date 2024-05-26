#include <cs50.h>
#include <stdio.h>

//A pyramid is made of two sides (sx and dx) which have a gap made of a 'double space' in between.

int main(void)
{
    int number = 0;
    while (number < 1 || number > 8) //checks that the number is between 1 and 8, both included.
    {
        number = get_int("Height: "); //if imput is different than int the function is called again.
    }
    for (int row = 0; row < number; row++) //for each row.
    {
        for (int s = 0; s < number; s++) //sx side of the pyramid.
        {
            if (s + 1 < number - row)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }

        }
        printf("  "); //prints a double space --> gap in between the two sides of the pyramid.
        for (int s = 0; s < number; s++) //dx side of the pyramid.
        {
            if (s < row + 1)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int get_lenght(const long n);
bool luhns_algorithm_passed(const long n, int len);
bool print_card_type(const long number, const int lenght);

int main(void)
{
    long credit_card_number = get_long("Number: ");
    int number_lenght = get_lenght(credit_card_number);
    if (number_lenght != 0 && luhns_algorithm_passed(credit_card_number, number_lenght))
    {
        print_card_type(credit_card_number, number_lenght); //return true if credit card number is invalid
    }
    else
    {
        printf("INVALID\n");
    }
}

int get_lenght(const long n)  // * ANY 0s IN FRONT OF n WILL NOT BE TAKEN INTO ACCOUNT
//the returning value 0 will mean the credit number is not valid.
{
    if (n <= 0) //doesn't allow any n <= 0.
    {
        return 0;
    }
//give the lenght of the number; e. g. to get the lenght of 1000:
//log(1000)/log(10) + 1 = log10(1000) + 1 = 3 + 1 = 4.
    int l = floor(log(n) / log(10) + 1); // * the operation ignores any 0s in front of n!
    if (l > 16)
    {
        return 0;
    }
    else
    {
        return l;
    }
}

bool luhns_algorithm_passed(const long n, int len)
{
    int sum = 0;
    long z = n;
    for (int i = len; i > 0; i --)
    {
        int last_digit = z % 10;
        if ((len - i) % 2 == 0) //add the last digit to sum.
        {
            sum += last_digit;
        }
        else //add the sum of the digits of the double of the last digit.
        {
            if (last_digit < 5)
            {
                sum += 2 * last_digit;
            }
            else //adds app the digits of a number if its double was composed by two digits.
            {
                sum += floor((last_digit * 2) / 10) + (last_digit * 2) % 10;
            }
        }
        z = floor(z / 10); //removes the last digit from n.
    }
    //check if card does respect luhn's algorithm
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool print_card_type(const long number, const int lenght) //returns true if card number is invalid
{
    //get first two digits:
    int first_two_dig = floor(number / pow(10, (lenght - 2)));
    //get first digit:
    int first_dig = floor(number / pow(10, lenght - 1));

    if (lenght == 15)
    {
        if (first_two_dig == 34 || first_two_dig == 37)
        {
            printf("AMEX\n");
            return false;
        }
        printf("INVALID\n");
        return true;
    }
    else if (lenght == 13 && first_dig == 4)
    {
        printf("VISA\n");
        return false;
    }
    else if (lenght == 16)
    {
        if (first_dig == 4)
        {
            printf("VISA\n");
            return false;
        }
        else if (50 < first_two_dig && first_two_dig < 56)
        {
            printf("MASTERCARD\n");
            return false;
        }
        printf("INVALID\n");
        return true;
    }
    else
    {
        printf("INVALID\n");
        return true;
    }
}

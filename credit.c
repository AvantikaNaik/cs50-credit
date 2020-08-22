#include <math.h>
#include <string.h>
#include <stdio.h>
#include <cs50.h>


long int ipow(int base, int exp);

int main(void)
{
    //Get valid credit card number

    long cardnumber;

    do
    {
        cardnumber = get_long("Number:");
    }
    while (cardnumber < 0);

    // Find length of credit card number
    long dummyccnum = cardnumber;
    int counter = 0;

    while (dummyccnum > 0)
    {
        dummyccnum = dummyccnum / 10;
        counter++;
    }

    // Validify length of card number
    if (counter != 13 && counter != 15 && counter != 16)
    {
        printf("INVALID\n");
        return 0;
    }

    // First stage of checksum: second-to-last number and every other number then times 2
    int total = 0;
    long int digit;

    for (int n = 1; n < counter; n += 2)
    {
        long int ipown = ipow(10, n);
        digit = cardnumber / ipown;
        digit = digit % 10;
        digit = digit * 2;
        if (digit > 9)
        {
            digit = (digit % 10) + (digit / 10);
        }

        total = total + digit;
    }

    // Second stage of checksum
    int secondary = 0;
    long int digit2;

    for (int n = 0; n < counter; n += 2)
    {
        digit2 = (cardnumber / ipow(10, n)) % 10;
        secondary = secondary + digit2;
    }

    // Find final checksum

    int finalchecksum = total + secondary;

    // Passes through only checksum valid numbers
    if ((finalchecksum % 10) != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    // Sort into type - AMEX
    
    if ((counter == 15) && (cardnumber / ipow(10, 14) == 3) && (((cardnumber / ipow(10, 13) % 10) == 4)
            || ((cardnumber / ipow(10, 13) % 10) == 7)))
    {
        printf("AMEX\n");
    }

    // Sort into type - MASTERCARD

    else if ((counter == 16) && (cardnumber / ipow(10, 15) == 5) && (((cardnumber / ipow(10, 14) % 10) == 1)
             || ((cardnumber / ipow(10, 14) % 10) == 2) || ((cardnumber / ipow(10, 14) % 10) == 3) || ((cardnumber / ipow(10, 14) % 10) == 4)
             || ((cardnumber / ipow(10, 14) % 10) == 5)))
    {
        printf("MASTERCARD\n");
    }

    // Sort into type - VISA, two step process
    else if ((counter == 13) && (cardnumber / ipow(10, 12) == 4))
    {
        printf("VISA\n");
    }

    //VISA PART 2
    else if ((counter == 16) && ((cardnumber / ipow(10, 15) % 10) == 4))
    {
        printf("VISA\n");
    }

    //Catch Alls
    else
    {
        printf("INVALID\n");
    }

}

long ipow(int base, int exp)

{
    long result = 1;
    for (;;)
    {
        if (exp & 1)
        {
            result *= base;
        }
        exp >>= 1;
        if (!exp)
        {
            break;
        }
        base *= base;
    }

    return result;
}

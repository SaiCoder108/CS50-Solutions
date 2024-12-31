#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Input
    long long answer;
    answer = get_long("Number: ");

    // Long to String Conversion
    char length[20];
    sprintf(length, "%lld", answer);
    long checksum = 0;

    // Loop Counters
    int j;

    // Check for AMEX
    if (strlen(length) == 15 &&
        (((answer / 10000000000000) == 34) || (answer / 10000000000000) == 37))
    {
        for (j = 14; j >= 0; j--)
        {
            if ((j + 1) % 2 == 0)
            {
                int num = (answer / (pow(10, j)));
                int num1 = 0;
                num1 = num * 2;
                if (num1 > 9)
                {
                    checksum += num1 / 10 + num1 % 10;
                }

                else
                {
                    checksum += num1;
                }

                answer = answer - (num * (pow(10, j)));
            }
            else
            {
                int num = (answer / (pow(10, j)));
                checksum += num;

                answer = answer - (num * (pow(10, j)));
            }
        }
        if (checksum % 10 == 0)
        {
            printf("AMEX\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    // Check for MasterCard
    else if (strlen(length) == 16 &&
             (((answer / 100000000000000) >= 51) && (answer / 100000000000000) <= 55))
    {
        for (j = 15; j >= 0; j--)
        {
            if ((j + 1) % 2 == 0)
            {
                int num = (answer / (pow(10, j)));
                int num1 = 0;
                num1 = num * 2;
                if (num1 > 9)
                {
                    checksum += num1 / 10 + num1 % 10;
                }

                else
                {
                    checksum += num1;
                }

                answer = answer - (num * (pow(10, j)));
            }
            else
            {
                int num = (answer / (pow(10, j)));
                checksum += num;

                answer = answer - (num * (pow(10, j)));
            }
        }
        if (checksum % 10 == 0)
        {
            printf("MASTERCARD\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    // Check for Visa
    else if ((strlen(length) == 16 || strlen(length) == 13) &&
             ((((answer / 1000000000000000) == 4)) || ((answer / 1000000000000) == 4)))
    {

        if (strlen(length) == 16)
        {
            for (j = 15; j >= 0; j--)
            {
                if ((j + 1) % 2 == 0)
                {
                    int num = (answer / (pow(10, j)));
                    int num1 = 0;
                    num1 = num * 2;
                    if (num1 > 9)
                    {
                        checksum += num1 / 10 + num1 % 10;
                    }

                    else
                    {
                        checksum += num1;
                    }

                    answer = answer - (num * (pow(10, j)));
                }
                else
                {
                    int num = (answer / (pow(10, j)));
                    checksum += num;

                    answer = answer - (num * (pow(10, j)));
                }
            }
        }
        else
        {
            for (j = 12; j >= 0; j--)
            {
                if ((j + 1) % 2 == 0)
                {
                    int num = (answer / (pow(10, j)));
                    int num1 = 0;
                    num1 = num * 2;
                    if (num1 > 9)
                    {
                        checksum += num1 / 10 + num1 % 10;
                    }

                    else
                    {
                        checksum += num1;
                    }

                    answer = answer - (num * (pow(10, j)));
                }
                else
                {
                    int num = (answer / (pow(10, j)));
                    checksum += num;

                    answer = answer - (num * (pow(10, j)));
                }
            }
        }

        if (checksum % 10 == 0)
        {
            printf("VISA\n");
        }

        else

        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

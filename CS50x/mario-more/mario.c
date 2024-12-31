#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Input
    int answer;

    do
    {
        answer = get_int("How high should the pyramids be?: ");
    }
    while (answer < 1);

    // Defining the parts of the pyramid
    string space = " ";
    string space1 = "";
    string hashtag = "#";

    // Counters
    int count = answer;
    int counter = 0;
    int counter1 = 1;

    // Loop Counter
    int i = answer;
    int j = count;
    int h = count;
    int k = count;

    // Loop
    for (i = answer; i > 0; i--)
    {
        count--;
        for (j = count; j > 0; j--)
        {
            printf(" ");
        }

        for (h = counter; h < counter1; h++)
        {
            printf("#");
        }

        printf("  ");

        for (k = counter; k < counter1; k++)
        {
            printf("#");
        }
        printf("\n");
        counter1++;
    }
}

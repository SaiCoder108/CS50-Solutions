#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Player 1 Input
    string player1;
    player1 = get_string("Player 1: ");

    // Convert to lowercase (Player 1)
    int a = 0;
    for (a = 0; player1[a]; a++)
    {
        player1[a] = tolower(player1[a]);
    }

    // Player 2 Input
    string player2;
    player2 = get_string("Player 2: ");

    // Convert to lowercase (Player 2)
    int b = 0;
    for (b = 0; player2[b]; b++)
    {
        player2[b] = tolower(player2[b]);
    }

    // Letter Ranking
    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int values[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    // Point Counters
    int P1points = 0;
    int P2points = 0;

    // Loop Counters
    int h = 0; // Player 1 Counter
    int i = 0; // Player 1 word len
    int j = 0; // Player 2 Counter
    int k = 0; // Player 2 word len

    // Check Player 1's Points
    for (i = 0; i <= strlen(player1) - 1; i++)
    {
        for (h = 0; h <= 26; h++)
        {
            if (player1[i] == letters[h])
            {
                P1points += values[h];
            }
        }
    }

    // Check Player 2's Points
    for (k = 0; k <= strlen(player2) - 1; k++)
    {
        for (j = 0; j <= 26; j++)
        {
            if (player2[k] == letters[j])
            {
                P2points += values[j];
            }
        }
    }

    // Check who wins

    if (P1points > P2points)
    {
        printf("Player 1 wins!\n");
    }

    else if (P1points < P2points)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

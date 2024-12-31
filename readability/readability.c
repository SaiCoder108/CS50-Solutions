#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Text Input
    string text;
    text = get_string("Text: ");

    // Convert to lowercase
    int a = 0;
    for (a = 0; text[a]; a++)
    {
        text[a] = tolower(text[a]);
    }

    // Letters
    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    // Counters
    int Letters = 0;
    int Words = 1;
    int Sentences = 0;

    // Loop Counters
    int h = 0; // Letters List
    int i = 0; // Text (For Letters)
    int j = 0; // Text (For Words)
    int k = 0; // Text (For Sentences)

    // Check Number of Words

    for (j = 0; j <= strlen(text) - 1; j++)
    {
        for (h = 0; h <= 26; h++)
        {
            if (text[j] == letters[h])
            {
                Letters += 1;
            }
        }

        if (text[j] == '.' || text[j] == '!' || text[j] == '?')
        {
            Sentences += 1;
        }

        if (text[j] == ' ')
        {
            Words += 1;
        }
    }

    // Readability Score Calculation

    float score1 = 0;
    float L = (float) Letters / Words * 100;
    float S = (float) Sentences / Words * 100;
    score1 = 0.0588 * L - 0.296 * S - 15.8;

    // Rounding to Nearest Whole Number
    score1 = round(score1);
    int score = (int) score1;

    // Checking the Grade Level
    string fscore;

    if (score > 16)
    {
        fscore = "Grade 16+\n";
        printf("%s", fscore);
    }

    else if (score < 1)
    {
        fscore = "Before Grade 1\n";
        printf("%s", fscore);
    }

    else
    {
        printf("Grade %d\n", score);
    }
}

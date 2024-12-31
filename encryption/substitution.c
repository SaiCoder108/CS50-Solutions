#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Main Function
int main(int argc, string argv[])
{

    // Check if User enters one commnd line argument

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if the key is a string of only letters

    string key = argv[1];
    for (int i = 0; i < strlen(key); i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    // Check that the key contains 26 characters

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Make sure that each letter in the key is only used once
    string keycheck = key;
    int counter = 0;
    for (int k = 0; k < strlen(key); k++)
    {
        counter = 0;
        for (int l = 0; l < strlen(key); l++)
        {
            if (key[k] == keycheck[l])
            {
                counter += 1;
                if (counter >= 2)
                {
                    printf("Key must not contain duplicate values!\n");
                    return 1;
                }
            }
        }
    }

    // Prompt the user for plaintext
    string plaintext = get_string("plaintext: ");
    string ciphertext = plaintext;

    // Encrpyt the plaintext

    char letterslow[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                           'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char lettersup[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                          'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    for (int x = 0; x < strlen(plaintext); x++)
    {
        for (int y = 0; y < strlen(key); y++)
        {
            if (isupper(plaintext[x]))
            {
                if (plaintext[x] == lettersup[y])
                {
                    ciphertext[x] = toupper(key[y]); // Ensure ciphertext is uppercase
                    break;
                }
            }
            else
            {
                if (plaintext[x] == letterslow[y])
                {
                    ciphertext[x] = tolower(key[y]); // Ensure ciphertext is lowercase
                    break;
                }
            }
        }
    }

    // Display Encrypted Text

    printf("ciphertext: %s\n", plaintext);
}

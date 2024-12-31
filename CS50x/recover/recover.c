#include <stdint.h>   // Includes the standard integer types library
#include <stdio.h>    // Includes the standard input/output library
#include <stdlib.h>   // Includes the standard library for memory allocation and other utilities
typedef uint8_t BYTE; // Defines BYTE as an alias for the 8-bit unsigned integer type

int main(int argc, char *argv[])
{
    // Check if the program is executed with exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n"); // Print usage message if the argument count is incorrect
        return 1;                          // Exit with error code 1
    }

    // Open the memory card file for reading
    FILE *input_file = fopen(argv[1], "r");

    // Check if the input file was successfully opened
    if (input_file == NULL)
    {
        printf("Could not open file\n"); // Print an error message if the file couldn't be opened
        return 2;                        // Exit with error code 2
    }

    // Create a buffer (array) to store 512 bytes of data
    unsigned char buffer[512];

    // Declare a pointer for the output file, initialized to NULL
    FILE *output_file = NULL;

    // Allocate memory for storing the filename of the JPEGs, 8 characters including the null
    // terminator
    char *filename = malloc(8 * sizeof(char));

    // Check if memory allocation for the filename was successful
    if (filename == NULL)
    {
        printf("Memory allocation failed\n");
        fclose(input_file); // Close input file before exiting
        return 3;           // Exit with error code 3
    }

    // Initialize a counter to track the number of JPEG files found
    int count = 0;

    // Read 512 bytes from the input file until the end of the file is reached
    while (fread(buffer, 1, 512, input_file) == 512)
    {
        // Check if the start of a new JPEG file is found by checking for JPEG signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If an output file is already open, close it
            if (output_file != NULL)
            {
                fclose(output_file);
            }

            // Create a new filename using the counter
            sprintf(filename, "%03i.jpg", count);

            // Open a new output file to write the JPEG data
            output_file = fopen(filename, "w");

            // Check if the output file was successfully opened
            if (output_file == NULL)
            {
                printf("Could not create output file %s\n", filename);
                free(filename);     // Free allocated memory before exiting
                fclose(input_file); // Close input file before exiting
                return 4;           // Exit with error code 4
            }

            // Increment the counter for the next JPEG file
            count++;
        }

        // If an output file is open, write the current buffer to it (writing 512 bytes at a time)
        if (output_file != NULL)
        {
            fwrite(buffer, sizeof(char), 512, output_file);
        }
    }

    // Free the memory allocated for the filename string
    free(filename);

    // Close the last output file, if it's open
    if (output_file != NULL)
    {
        fclose(output_file);
    }

    // Close the input file
    fclose(input_file);

    return 0; // Return 0 indicating the program executed successfully
}

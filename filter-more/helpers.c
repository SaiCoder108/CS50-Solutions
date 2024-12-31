#include "helpers.h"
#include "math.h"
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Checks each row
    for (int i = 0; i < height; i++)
    {
        // Checks each column
        for (int j = 0; j < width; j++)
        {
            // Convert to Float
            float Red = image[i][j].rgbtRed;
            float Green = image[i][j].rgbtGreen;
            float Blue = image[i][j].rgbtBlue;

            // Find the average of the RGB
            int average = round((Red + Green + Blue) / 3);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Checks each row
    for (int i = 0; i < height; i++)
    {
        // Checks each column
        for (int j = 0; j < (width / 2); j++)
        {
            // Store pixel
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image so that you do change the image blurring
    RGBTRIPLE temp[height][width];

    // Checks each row
    for (int i = 0; i < height; i++)
    {
        // Checks each column
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Counters for the RGB values
    int red, blue, green, valid;

    // Checks each row
    for (int i = 0; i < height; i++)
    {
        // Checks each column
        for (int j = 0; j < width; j++)
        {
            red = 0;
            blue = 0;
            green = 0;
            valid = 0;

            // Check Surrounding Pixels
            for (int x = -1; x <= 1; x++) // Checks Row
            {
                for (int y = -1; y <= 1; y++) // Checks column
                {
                    if (i + x < 0 || i + x >= height || j + y < 0 ||
                        j + y >= width) // Checks borders (Invalid pixels)
                    {
                        continue;
                    }

                    // Accumulate values
                    red += image[i + x][j + y].rgbtRed;
                    blue += image[i + x][j + y].rgbtBlue;
                    green += image[i + x][j + y].rgbtGreen;
                    valid++;
                }
            }

            // Assign New Avg Values after looping through all surrounding pixels
            temp[i][j].rgbtRed = round((float) red / valid);
            temp[i][j].rgbtBlue = round((float) blue / valid);
            temp[i][j].rgbtGreen = round((float) green / valid);
        }
    }

    // Copy the temp file to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the image so that you do change the image blurring
    RGBTRIPLE temp[height][width];

    // Checks each row
    for (int i = 0; i < height; i++)
    {
        // Checks each column
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // 2-D Array for the Gx and Gy
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Checks each row
    for (int i = 0; i < height; i++)
    {
        // Checks each column
        for (int j = 0; j < width; j++)
        {
            // Counters for Gx
            int redX = 0;
            int blueX = 0;
            int greenX = 0;

            // Counters for Gy
            int redY = 0;
            int blueY = 0;
            int greenY = 0;

            // Check Surrounding Pixels
            for (int x = -1; x <= 1; x++) // Checks Row
            {
                for (int y = -1; y <= 1; y++) // Checks column
                {
                    if (i + x < 0 || i + x >= height || j + y < 0 ||
                        j + y >= width) // Checks if pixels are valid (Invalid pixels are skipped)
                    {
                        continue;
                    }

                    // Calculate Gx value for colors
                    redX += image[i + x][j + y].rgbtRed * Gx[x + 1][y + 1];
                    blueX += image[i + x][j + y].rgbtBlue * Gx[x + 1][y + 1];
                    greenX += image[i + x][j + y].rgbtGreen * Gx[x + 1][y + 1];

                    // Calculate Gy value for colors
                    redY += image[i + x][j + y].rgbtRed * Gy[x + 1][y + 1];
                    blueY += image[i + x][j + y].rgbtBlue * Gy[x + 1][y + 1];
                    greenY += image[i + x][j + y].rgbtGreen * Gy[x + 1][y + 1];
                }
            }

            // Calculate Gx^2 and Gy^2
            int red = round(sqrt((redX * redX) + (redY * redY)));
            int blue = round(sqrt((blueX * blueX) + (blueY * blueY)));
            int green = round(sqrt((greenX * greenX) + (greenY * greenY)));

            // Cap the values as 255
            if (red > 255)
            {
                red = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }

            // Record new values to Temp
            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtBlue = blue;
            temp[i][j].rgbtGreen = green;
        }
    }

    // Copy the temp file to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}

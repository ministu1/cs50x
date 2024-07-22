#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Get the average of Red, Green and Blue.
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int rgbAvg = round((originalRed + originalGreen + originalBlue) / 3.0);

            // Update pixels to new colour values.
            // EXTERNAL SOURCE: Used shorthand found at
            // https://stackoverflow.com/questions/27967286/can-i-assign-same-value-to-multiple-variables-in-c
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = rgbAvg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            // Update pixel with sepia values
            // EXTERNAL SOURCE: Looked for the existence of the ternary operator as I know it from JS.
            // Found the answer here: https://www.freecodecamp.org/news/c-ternary-operator/
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all rows.
    for (int i = 0; i < height; i++)
    {
        // Swap the j-th pixel in the i-th row from the front
        // with the j-th pixel in the i-th row from the back.
        for (int j = 0; j < (width / 2); j++)
            {
                RGBTRIPLE buffer[height][width];
                buffer[i][j] = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = buffer[i][j];
            }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy the image to leave the original unaltered.
    RGBTRIPLE copy[height][width];

    // Loop all rows.
    for (int i = 0; i < height; i++)
    {
        // Loop columns.
        for (int j = 0; j < width; j++)
        {
            // Store the sums of all colours of the adjacent pixels and the amount of adjacent pixels.
            float red, green, blue, pixels;
            red = green = blue = pixels = 0;

            // Loop adjacent rows of the i-th row.
            for (int row = -1; row < 2; row++)
            {
                // Loop adjacent columns.
                for (int col = -1; col < 2; col++)
                {
                    // If the adjacent pixels of the i-th row and j-th column are within the borders
                    // of the picture, add their color values to the sum of colours.
                    if ((i + row) >= 0 && (i + row) < height && (j + col) >= 0 && (j + col) < height)
                    {
                        red += image[i + row][j + col].rgbtRed;
                        green += image[i + row][j + col].rgbtGreen;
                        blue += image[i + row][j + col].rgbtBlue;
                        pixels++;
                    }
                }
            }
             // Assign the values to the copy of the image.
            copy[i][j].rgbtRed = round(red / pixels);
            copy[i][j].rgbtGreen = round(green / pixels);
            copy[i][j].rgbtBlue = round(blue / pixels);
        }
    }
    // Replace pixels of the original picture with the newly generated values in the copy.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}

#include "helpers.h"
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float r = image[i][j].rgbtRed; // Make colors easy to use

            float g = image[i][j].rgbtGreen;

            float b = image[i][j].rgbtBlue;

            float pixelaverage = (r + g + b) / 3.0; // takes average of each

            // Then add to the image output

            image[i][j].rgbtRed = round(pixelaverage);

            image[i][j].rgbtGreen = round(pixelaverage);

            image[i][j].rgbtBlue = round(pixelaverage);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float r = image[i][j].rgbtRed; // Make colors easy to use

            float g = image[i][j].rgbtGreen;

            float b = image[i][j].rgbtBlue;
            // Uses the equation
            float sepiared = 0.393 * r + 0.769 * g + 0.189 * b;

            float sepiagreen = 0.349 * r + 0.686 * g + 0.168 * b;

            float sepiablue = 0.272 * r + 0.534 * g + 0.131 * b;

            // Check if any result is greater than 255, and make it 255

            if (sepiared > 255)
            {
                sepiared = 255;
            }
            if (sepiagreen > 255)
            {
                sepiagreen = 255;
            }
            if (sepiablue > 255)
            {
                sepiablue = 255;
            }
            image[i][j].rgbtRed = round(sepiared);

            image[i][j].rgbtGreen = round(sepiagreen);

            image[i][j].rgbtBlue = round(sepiablue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        if (width % 2 == 0)
        {
            for (int j = 0; j < width / 2; j++) // if odd use all
            {
                RGBTRIPLE temp[height][width]; // makes a temp image

                temp[i][j] = image[i][j];

                image[i][j] = image[i][width - (j + 1)]; // gets the last to first pixel

                image[i][width - (j + 1)] = temp[i][j]; // swap last to first

            }
        }
        else
        {
            for (int j = 0; j < (width - 1) / 2; j++) // If not odd not use last
            {
                RGBTRIPLE temp[height][width];

                temp[i][j] = image[i][j];

                image[i][j] = image[i][width - (j + 1)];

                image[i][width - (j + 1)] = temp[i][j];

            }
        }
    }

    return;
}

// Blur image
/*
if [0] [0] = upper-left & top
if [0] [width]= upper-right & top
if [height][0]= bottom-left & bottom
if [height][width]= bottom-right & bottom
if [height][j] & [0][j] = bottom & top
if [i][width] & [i][0] = right & left
*/
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    memcpy(temp, image, sizeof(temp)); //memcpy - copy string to another

    int boxsize = 3;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;
            int count = 0;

            for (int k = -boxsize / 2; k <= boxsize / 2; k++)
            {
                for (int l = -boxsize / 2; l <= boxsize / 2; l++)
                {
                    int row = i + k;
                    int col = j + l;
                    if (row >= 0 && row < height && col >= 0 && col < width)
                    {
                        sum_red += temp[row][col].rgbtRed;
                        sum_green += temp[row][col].rgbtGreen;
                        sum_blue += temp[row][col].rgbtBlue;
                        count++;
                    }
                }
            }

            image[i][j].rgbtRed = round((float)sum_red / count);
            image[i][j].rgbtGreen = round((float)sum_green / count);
            image[i][j].rgbtBlue = round((float)sum_blue / count);
        }
    }
}
#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int avg = round((image[row][column].rgbtRed + image[row][column].rgbtGreen +
                             image[row][column].rgbtBlue) /
                            3.0);

            image[row][column].rgbtRed = avg;
            image[row][column].rgbtGreen = avg;
            image[row][column].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width / 2; column++)
        {
            RGBTRIPLE temp = image[row][column];
            image[row][column] = image[row][width - (column + 1)];
            image[row][width - (column + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            float sumRed = 0, sumGreen = 0, sumBlue = 0, count = 0;

            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (column + j > width - 1 || column + j < 0)
                    {
                        continue;
                    }
                    if (row + i > height - 1 || row + i < 0)
                    {
                        continue;
                    }
                    sumRed += image[row + i][column + j].rgbtRed;
                    sumBlue += image[row + i][column + j].rgbtBlue;
                    sumGreen += image[row + i][column + j].rgbtGreen;
                    count++;
                }
            }

            temp[row][column].rgbtRed = round(sumRed / count);
            temp[row][column].rgbtGreen = round(sumGreen / count);
            temp[row][column].rgbtBlue = round(sumBlue / count);
        }
    }

    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            image[k][l].rgbtRed = temp[k][l].rgbtRed;
            image[k][l].rgbtGreen = temp[k][l].rgbtGreen;
            image[k][l].rgbtBlue = temp[k][l].rgbtBlue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    int x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    int xRed, xGreen, xBlue, yRed, yGreen, yBlue;

    int redColor, greenColor, blueColor;

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            xRed = xGreen = xBlue = yRed = yGreen = yBlue = 0;

            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    if (column + j > width - 1 || column + j < 0)
                    {
                        continue;
                    }
                    if (row + i > height - 1 || row + i < 0)
                    {
                        continue;
                    }
                    xRed += image[row + i][column + j].rgbtRed * x[i + 1][j + 1];
                    xGreen += image[row + i][column + j].rgbtGreen * x[i + 1][j + 1];
                    xBlue += image[row + i][column + j].rgbtBlue * x[i + 1][j + 1];
                    yRed += image[row + i][column + j].rgbtRed * y[i + 1][j + 1];
                    yGreen += image[row + i][column + j].rgbtGreen * y[i + 1][j + 1];
                    yBlue += image[row + i][column + j].rgbtBlue * y[i + 1][j + 1];
                }
            }
            redColor = round(sqrt(pow(xRed, 2) + pow(yRed, 2)));
            greenColor = round(sqrt(pow(xGreen, 2) + pow(yGreen, 2)));
            blueColor = round(sqrt(pow(xBlue, 2) + pow(yBlue, 2)));

            if (redColor > 255)
            {
                temp[row][column].rgbtRed = 255;
            }
            else
            {
                temp[row][column].rgbtRed = redColor;
            }

            if (greenColor > 255)
            {
                temp[row][column].rgbtGreen = 255;
            }
            else
            {
                temp[row][column].rgbtGreen = greenColor;
            }

            if (blueColor > 255)
            {
                temp[row][column].rgbtBlue = 255;
            }
            else
            {
                temp[row][column].rgbtBlue = blueColor;
            }
        }
    }

    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            image[k][l].rgbtRed = temp[k][l].rgbtRed;
            image[k][l].rgbtGreen = temp[k][l].rgbtGreen;
            image[k][l].rgbtBlue = temp[k][l].rgbtBlue;
        }
    }
    return;
}

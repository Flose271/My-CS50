#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int red = image[row][col].rgbtRed;
            int green = image[row][col].rgbtGreen;
            int blue = image[row][col].rgbtBlue;
            int grey = round((red+green+blue)/3.0);
            image[row][col].rgbtRed = grey;
            image[row][col].rgbtGreen = grey;
            image[row][col].rgbtBlue = grey;
        }
    }
    
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            int red = image[row][col].rgbtRed;
            int green = image[row][col].rgbtGreen;
            int blue = image[row][col].rgbtBlue;
            
            image[row][col].rgbtRed = image[row][width-1-col].rgbtRed;
            image[row][col].rgbtGreen = image[row][width-1-col].rgbtGreen;
            image[row][col].rgbtBlue = image[row][width-1-col].rgbtBlue;
            
            image[row][width-1-col].rgbtRed = red;
            image[row][width-1-col].rgbtGreen = green;
            image[row][width-1-col].rgbtBlue = blue;
        }
    }
    
    
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

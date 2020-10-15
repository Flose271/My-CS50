#include "helpers.h"
#include <math.h>
#include <stdlib.h>

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
    
    //Make a copy of the original image
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            copy[row][col] = image[row][col];
        }
    }
    
    //Find a pixel
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            //Now working on level of individual pixel
            //xd is x delta, yd is y delta (from pixel)
            
            int redsum = 0;
            int greensum = 0;
            int bluesum = 0;
            int total = 0;
            
            for (int xd = -1; xd < 2; xd++)
            {
                for (int yd = -1; yd < 2; yd++)
                {
                    //If this reffered to pixel is valid, add its sum to total
                    if(col + xd >= 0 && col + xd < width && row + yd >= 0 && row + yd < height)
                    {
                        redsum += copy[row+yd][col+xd].rgbtRed;
                        greensum += copy[row+yd][col+xd].rgbtGreen;
                        bluesum += copy[row+yd][col+xd].rgbtBlue;
                        total += 1;
                    }
                }
            }
            
            //Now change corresponding pixel in original image to the average value
            image[row][col].rgbtRed = round((float) redsum/total);
            image[row][col].rgbtGreen = round((float) greensum/total);
            image[row][col].rgbtBlue = round((float) bluesum/total);

        }
    }
    
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Make a copy of the original image
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            copy[row][col] = image[row][col];
        }
    }
    
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            //Set up X kernel
            int xred = 0;
            int xgreen = 0;
            int xblue = 0;
            
            //Set up Y kernel
            int yred = 0;
            int ygreen = 0;
            int yblue = 0;
            
            //Working on level of individual pixel
            for (int xd = -1; xd < 2; xd++)
            {
                for (int yd = -1; yd < 2; yd++)
                {
                    //If this reffered to pixel is valid
                    if(col + xd >= 0 && col + xd < width && row + yd >= 0 && row + yd < height)
                    {
                        xred += (xd)*(2-abs(yd))*copy[row+yd][col+xd].rgbtRed;
                        xgreen += (xd)*(2-abs(yd))*copy[row+yd][col+xd].rgbtGreen;
                        xblue += (xd)*(2-abs(yd))*copy[row+yd][col+xd].rgbtBlue;
                        
                        yred += (yd)*(2-abs(xd))*copy[row+yd][col+xd].rgbtRed;
                        ygreen += (yd)*(2-abs(xd))*copy[row+yd][col+xd].rgbtGreen;
                        yblue += (yd)*(2-abs(xd))*copy[row+yd][col+xd].rgbtBlue;
                        
                        int red = round(sqrt(pow(xred,2) + pow(yred,2)));
                        if(red > 255)
                        {
                            red = 255;
                        }
                        
                        int green = round(sqrt(pow(xgreen,2) + pow(ygreen,2)));
                        if(green > 255)
                        {
                            green = 255;
                        }
                        
                        int blue = round(sqrt(pow(xblue,2) + pow(yblue,2)));
                        if(blue > 255)
                        {
                            blue = 255;
                        }
                        
                        image[row][col].rgbtRed = red;
                        image[row][col].rgbtGreen = green;
                        image[row][col].rgbtBlue = blue;
                        
                    }
                }
            }
        }
    }
    
    return;
}
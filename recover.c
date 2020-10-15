#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }
    
    //This file is for the given card.raw
    FILE *inptr = fopen(argv[1], "r");
    
    //If the file doesn't work
    if (inptr == NULL)
    {
        printf("Couldn't open %s\n", argv[1]);
        return 2;
    }
    
    //This file will be used to write the images to
    FILE *outptr = NULL;
    
    //buffer stores our 512 bytes of data
    unsigned char buffer[512];
    //memory for the image name
    char image_name[8];
    //Need a counter for number of files found for naming and for checking if first file
    int files_found = 0;
    
    //Read through what is at inptr in blocks of 512 one at a time
    while(fread(buffer, 512, 1, inptr) == 1)
    {
        //If the block starts with first 4 bytes representing jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            //If this isn't our first file, close outptr from previous file
            if(files_found != 0)
            {
                fclose(outptr);
            }
            //Naming the image
            sprintf(image_name, "%03d.jpg", files_found);
            
            //We get ready to write to image_name.
            outptr = fopen(image_name, "w");
            //If outptr is null, a problem has occured.
            if(outptr == NULL)
            {
                printf("Couldn't make image %s.\n", image_name);
                return 3;
            }
            //File counter is incremented by one.
            files_found += 1;
        }

        if (outptr != NULL)
        {
            fwrite(buffer, 512, 1, outptr);
        }
    }
    
    //Close the outpointer and inpointer
    fclose(outptr);
    fclose(inptr);
    
    return 0;
    
}
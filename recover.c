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
    
    //file is the pointer for card.raw
    char *file = argv[1];
    
    //Store contents of file at inptr
    FILE *inptr = fopen(file, "r");
    //If the file doesn't work
    if (inptr == NULL)
    {
        printf("Couldn't open %s.\n", file);
        return 2;
    }
    
    FILE *outptr = NULL;
    
    unsigned char buffer[512];
    char image_name[8];
    int files_found = 0;
    
    while(fread(buffer, 512, 1, inptr) == 1)
    {
        //If inptr is at the beginning of a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            //If this isn't our first file
            if(files_found != 0)
            {
                fclose(outptr);
            }
            //Naming the image
            sprintf(image_name, "%03d.jpg", files_found);
            //Write what is at outptr to image.
            
            outptr = fopen(image_name, "w");
            if(outptr == NULL)
            {
                printf("Couldn't make image %s.\n", image_name);
            }
            files_found += 1;
        }
        
        if (outptr != NULL)
        {
            //We write 
            fwrite(buffer, 512, 1, outptr);
        }
    }
    //we close the outpointer and inpointer
    fclose(outptr);
    fclose(inptr);
    return 0;
    
}
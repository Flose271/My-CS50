#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    
    FILE *write_pointer = NULL;
    FILE *read_pointer = fopen(argv[1], "r");
    if (read_pointer == NULL)
    {
        printf("Unable to open: %s\n", argv[1]);
        return 1;
    }
    
    int files_found = 0;
    bool jpg_currently_open = false;
    unsigned char buffer[512];
    
    while(fread(&buffer, 512, 1, read_pointer) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (jpg_currently_open)
            {
                fclose(write_pointer);
            }
            else
            {
                char filename[8];
                sprintf(filename, "%03i.jpg", files_found);
                write_pointer = fopen(filename, "w");
                files_found += 1;
            }
        }

        if (jpg_currently_open)//once new JPEGS are found
        {
            //copy over the blocks from buffer into new file
            fwrite(&buffer, 512, 1, write_pointer);
        }

    }
    
    if (write_pointer == NULL)
    {
        fclose(write_pointer);
    }
    if (read_pointer == NULL)
    {
        fclose(read_pointer);
    }
    return 0;
    
}
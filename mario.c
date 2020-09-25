#include <stdio.h>
#include <cs50.h>

void air(int n);

void blocks(int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1 || n > 8);
    for (int i = 0; i < n; i++)
    {
        //Number of 'air' before the blocks
        int air_value = n - i - 1;
        //Number of 'blocks' on each side
        int blocks_value = i + 1;
        
        //Prints the air before the blocks
        air(air_value);
        //Prints the blocks on the left
        blocks(blocks_value);
        //Prints the gap between the blocks
        printf("  ");
        //Prints the blocks on the right
        blocks(blocks_value);
        //New line
        printf("\n");
    }
}

void air(int n)
{
    //prints " " n times
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}

void blocks(int n)
{
    //prints "#" n times
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}